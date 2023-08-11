/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:01:57 by druina            #+#    #+#             */
/*   Updated: 2023/08/11 15:49:25 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	if (get_current_time() - philo->last_meal >= time_to_die
		&& philo->eating == 0)
		return (1);
	return (0);
}

void	*philo_routine(void *pointer)
{
	t_program	*program;

	program = (t_program *)pointer;
	while (program->dead == 0)
	{
	}
	return (pointer);
}

void print_messages(char *str, t_program *program, int id)
{
  size_t time;

  pthread_mutex_lock(&program->write);
  time = get_current_time() - program->start_time;
  printf("%zu %d %s\n", time, id, str);
  pthread_mutex_unlock(&program->write);
}

void	*monitor(void *pointer)
{
	t_program	*program;
	int			i;

	program = (t_program *)pointer;
	i = 0;
	while (program->dead == 0)
	{
		while (i < program->num_of_philos)
		{
			pthread_mutex_lock(&program->philos[i].lock);
			if (philosopher_dead(&program->philos[i], program->time_to_die))
			{
				program->dead = 1;
        pthread_mutex_unlock(&program->philos[i].lock);
        print_messages("died", program, program->philos[i].id);
        break; 
			}
        pthread_mutex_unlock(&program->philos[i].lock);
			i++;
		}
	}
	return (pointer);
}

int	thread_create(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &monitor, &program) != 0)
		destory_all("Thread creation error", program, forks);
	i = 0;
	while (i < program->num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philo_routine,
				&program->philos[i]) != 0)
			destory_all("Thread creation error", program, forks);
		i++;
	}
	i = 0;
	while (i < program->num_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			destory_all("Thread join error", program, forks);
		i++;
	}
	if (pthread_join(observer, NULL) != 0)
		destory_all("Thread join error", program, forks);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:22:47 by druina            #+#    #+#             */
/*   Updated: 2023/08/13 22:53:41 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *str, t_program *program, int id)
{
	size_t	time;

	pthread_mutex_lock(&program->write);
	time = get_current_time() - program->start_time;
	printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(&program->write);
}

int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	if (get_current_time() - philo->last_meal >= time_to_die
		&& philo->eating == 0)
		return (1);
	return (0);
}

int	check_if_dead(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		pthread_mutex_lock(&program->philos[i].lock);
		if (philosopher_dead(&program->philos[i], program->time_to_die))
		{
			program->dead = 1;
			pthread_mutex_unlock(&program->philos[i].lock);
			print_message("died", program, program->philos[i].id);
			return (1);
		}
		pthread_mutex_unlock(&program->philos[i].lock);
		i++;
	}
	return (0);
}

int	check_if_all_ate(t_program *program)
{
	int	i;

	i = 0;
	program->finished_eating = 0;
	if (program->num_times_to_eat == -1)
		return (0);
	while (i < program->num_of_philos)
	{
		pthread_mutex_lock(&program->philos[i].lock);
		if (program->philos[i].meals_eaten >= program->num_times_to_eat)
			program->finished_eating++;
		pthread_mutex_unlock(&program->philos[i].lock);
		i++;
	}
	if (program->finished_eating == program->num_of_philos)
	{
		program->dead = 1;
		return (1);
	}
	return (0);
}

void	*monitor(void *pointer)
{
	t_program *program;

	program = (t_program *)pointer;
	while (program->dead == 0)
		if (check_if_dead(program) == 1 || check_if_all_ate(program) == 1)
			break ;
	return (pointer);
}
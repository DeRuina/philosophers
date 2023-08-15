/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:01:57 by druina            #+#    #+#             */
/*   Updated: 2023/08/15 10:49:48 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void think (t_philo *philo)
{
  print_message("is thinking", philo, philo->id);
}

void dream(t_philo *philo)
{
  print_message("is sleeping", philo, philo->id);
  ft_usleep(philo->time_to_sleep);
}

void eat(t_philo *philo)
{
  pthread_mutex_lock(philo->r_fork);
  print_message("has taken a fork", philo, philo->id);
  pthread_mutex_lock(philo->l_fork);
  print_message("has taken a fork", philo, philo->id);
//   pthread_mutex_lock(philo->lock);
  philo->eating = 1;
  philo->last_meal = get_current_time();
  print_message("is eating", philo, philo->id);
  philo->meals_eaten++;
  ft_usleep(philo->time_to_eat);
  philo->eating = 0;
//   pthread_mutex_unlock(philo->lock);
  pthread_mutex_unlock(philo->l_fork);
  pthread_mutex_unlock(philo->r_fork);
}

void	*philo_routine(void *pointer)
{
	t_philo *philo;

	philo = (t_philo *)pointer;
	while (*philo->dead == 0)
  {
    eat(philo);
    dream(philo);
    think(philo);
  }
	return (pointer);
}

int	thread_create(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &monitor, program->philos) != 0)
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
	if (pthread_join(observer, NULL) != 0)
		destory_all("Thread join error", program, forks);
	while (i < program->num_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			destory_all("Thread join error", program, forks);
		i++;
	}
	return (0);
}

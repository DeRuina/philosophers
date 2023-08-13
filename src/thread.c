/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:01:57 by druina            #+#    #+#             */
/*   Updated: 2023/08/13 23:06:40 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void think (t_philo *philo)
{

}

void dream(t_philo *philo)
{

}

void eat(t_philo *philo)
{


}

void actions(t_philo *philo)
{
  eat(philo);
  dream(philo);
  think(philo);
}

void	*philo_routine(void *pointer)
{
	t_philo *philo;

	philo = (t_philo *)pointer;
	while (philo->dead == 0)
    actions(philo);
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

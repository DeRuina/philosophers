/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:22:47 by druina            #+#    #+#             */
/*   Updated: 2023/08/15 10:26:01 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write);
	time = get_current_time() - philo->start_time;
	printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write);
}

int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	if (get_current_time() - philo->last_meal >= time_to_die
		&& philo->eating == 0)
		return (1);
	return (0);
}

int	check_if_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		// pthread_mutex_lock(&program->philos[i].lock);
		// if (philosopher_dead(&program->philos[i], program->time_to_die))
		// {
		// 	program->dead = 1;
		// 	pthread_mutex_unlock(&program->philos[i].lock);
		// 	print_message("died", &program->philos[i], program->philos[i].id);
		// 	return (1);
		// }
		// pthread_mutex_unlock(&program->philos[i].lock);
		i++;
	}
	return (0);
}

int	check_if_all_ate(t_philo *philos)
{
	int	i;
	int finished_eating;

	i = 0;
	finished_eating = 0;
	if (philos[0].num_times_to_eat == -1)
		return (0);
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[i].lock);
		if (philos[i].meals_eaten >= philos[i].num_times_to_eat)
			finished_eating++;
		pthread_mutex_unlock(philos[i].lock);
		i++;
	}
	if (finished_eating == philos[0].num_of_philos)
	{
		*philos[0].dead = 1;
		return (1);
	}
	return (0);
}

void	*monitor(void *pointer)
{
	t_philo *philos;

	philos = (t_philo *)pointer;
	while (1)
		if (check_if_dead(philos) == 1 || check_if_all_ate(philos) == 1)
			break ;
	return (pointer);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:22:47 by druina            #+#    #+#             */
/*   Updated: 2023/08/16 16:06:03 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Print message funtion

void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write);
	time = get_current_time() - philo->start_time;
	if (*philo->dead == 0)
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write);
}

// Checks if the philosopher is dead

int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	if (get_current_time() - philo->last_meal >= time_to_die
		&& philo->eating == 0)
		return (1);
	return (0);
}

// Check if any philo died

int	check_if_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		if (philosopher_dead(&philos[i], philos[i].time_to_die))
		{
			print_message("died", &philos[i], philos[i].id);
			// pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			// pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

// Checks if all the philos ate the num_of_meals

int	check_if_all_ate(t_philo *philos)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philos[0].num_times_to_eat == -1)
		return (0);
	while (i < philos[0].num_of_philos)
	{
		if (philos[i].meals_eaten >= philos[i].num_times_to_eat)
			finished_eating++;
		i++;
	}
	if (finished_eating == philos[0].num_of_philos)
	{
		// pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		// pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

// Monitor thread routine

void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
		if (check_if_dead(philos) == 1 || check_if_all_ate(philos) == 1)
			break ;
	return (pointer);
}

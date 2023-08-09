/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:05:40 by druina            #+#    #+#             */
/*   Updated: 2023/08/09 12:30:41 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_mutex (pthread_mutex_t *forks, pthread_mutex_t dead_lock, int philo_num)
{
  int i;

  i = 0;
  while (i < philo_num)
  {
    pthread_mutex_init(&forks[i], NULL);
    i++;
  }
  pthread_mutex_init(&dead_lock, NULL);
}

void	init_input(t_input *input, char **argv)
{
	input->start_time = get_current_time();
	input->num_of_philos = ft_atoi(argv[1]);
	input->time_to_die = ft_atoi(argv[2]);
	input->time_to_eat = ft_atoi(argv[3]);
	input->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		input->num_times_to_eat = ft_atoi(argv[5]);
	else
		input->num_times_to_eat = -1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:23:28 by druina            #+#    #+#             */
/*   Updated: 2023/08/11 13:43:44 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg_content(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_valid_args(char **argv)
{
	if (ft_atoi(argv[1]) > PHILO_MAX || ft_atoi(argv[1]) <= 0
		|| check_arg_content(argv[1]) == 1)
		return (write(2, "Invalid philosophers number\n", 29), 1);
	if (ft_atoi(argv[2]) <= 0 || check_arg_content(argv[2]) == 1)
		return (write(2, "Invalid time to die\n", 21), 1);
	if (ft_atoi(argv[3]) <= 0 || check_arg_content(argv[3]) == 1)
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (ft_atoi(argv[4]) <= 0 || check_arg_content(argv[4]) == 1)
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (argv[5] && (ft_atoi(argv[5]) < 0 || check_arg_content(argv[5]) == 1))
		return (write(2, "Invalid number of times each philosopher must eat\n",
				51), 1);
	return (0);
}
void	destory_all(char *str, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&philos[0].program->lock);
	pthread_mutex_destroy(&philos[0].program->write);
	while (i < philos->program->num_of_philos)
	{
		pthread_mutex_destroy(&philos[i].lock);
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	
	return (philo);
}

int	thread_create(t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < philos[0].program->num_of_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, &philo_routine,
				&philos[i]) != 0)
			destory_all("Thread creation error", philos, forks);
		i++;
	}
	i = 0;
	while (i < philos[0].program->num_of_philos)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			destory_all("Thread join error", philos, forks);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_program program;
	t_philo philos[PHILO_MAX];
	pthread_mutex_t forks[PHILO_MAX];

	if (argc != 5 && argc != 6)
		return (write(2, "Wrong argument count\n", 22), 1);
	if (check_valid_args(argv) == 1)
		return (1);
	init_program(&program, argv);
	init_forks(forks, program.num_of_philos);
	init_philos(philos, &program, forks);
	thread_create(philos, forks);
  destory_all(NULL, philos, forks);

	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:20:06 by druina            #+#    #+#             */
/*   Updated: 2023/08/09 11:26:14 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 300

typedef struct s_input
{
	int		num_of_philos;
	size_t	start_time;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int		num_times_to_eat;
}			t_input;

typedef struct s_philo
{
}			t_philo;

int			ft_atoi(char *str);
int			check_valid_args(char **argv);
int			check_arg_content(char *arg);
size_t		get_current_time(void);
void		init_input(t_input *input, char **argv);

#endif
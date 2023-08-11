/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:20:06 by druina            #+#    #+#             */
/*   Updated: 2023/08/11 15:46:55 by druina           ###   ########.fr       */
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

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	lock;
}					t_philo;

typedef struct s_program
{
	int				num_of_philos;
	size_t			start_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_times_to_eat;
	int				finished_eating;
	int				dead;
	pthread_mutex_t	write;
	pthread_mutex_t	lock;
	t_philo			*philos;
}					t_program;

int					ft_atoi(char *str);
int					check_valid_args(char **argv);
int					check_arg_content(char *arg);
size_t				get_current_time(void);
void				init_program(t_program *program, t_philo *philos,
						char **argv);
void				init_forks(pthread_mutex_t *forks, int philo_num);
void				init_philos(t_philo *philos, t_program *program,
						pthread_mutex_t *forks);
int					ft_usleep(size_t microseconds);
int					ft_strlen(char *str);
void				*philo_routine(void *pointer);
void				destory_all(char *str, t_program *program,
						pthread_mutex_t *forks);
int					philosopher_dead(t_philo *philo, size_t time_to_die);
int					thread_create(t_program *program, pthread_mutex_t *forks);
void				print_messages(char *str, t_program *program, int id);
#endif
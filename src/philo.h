/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:20:06 by druina            #+#    #+#             */
/*   Updated: 2023/08/16 10:01:54 by druina           ###   ########.fr       */
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
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write;
}					t_philo;
typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	write;
	t_philo			*philos;
}					t_program;

int					ft_atoi(char *str);
int					check_valid_args(char **argv);
int					check_arg_content(char *arg);
size_t				get_current_time(void);
void				init_program(t_program *program, t_philo *philos);
void				init_forks(pthread_mutex_t *forks, int philo_num);
void				init_philos(t_philo *philos, t_program *program,
						pthread_mutex_t *forks, char **argv);
int					ft_usleep(size_t microseconds);
int					ft_strlen(char *str);
void				*philo_routine(void *pointer);
void				*monitor(void *pointer);
void				destory_all(char *str, t_program *program,
						pthread_mutex_t *forks);
int					philosopher_dead(t_philo *philo, size_t time_to_die);
int					thread_create(t_program *program, pthread_mutex_t *forks);
void				print_message(char *str, t_philo *philo, int id);
int					check_if_dead(t_philo *philos);
int					check_if_all_ate(t_philo *philos);
void				eat(t_philo *philo);
void				dream(t_philo *philo);
void				think(t_philo *philo);

#endif

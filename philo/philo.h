/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:14:16 by zsalih            #+#    #+#             */
/*   Updated: 2025/08/17 11:12:34 by zsalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_config
{
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_meals;
}					t_config;

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
	int				available;
	int				prev_owner;
}					t_fork;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	int				meals_eaten;
	long			last_meal_time;
	t_fork			*left_fork;
	t_fork			*right_fork;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	t_config		config;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	state_mutex;
	int				stop_simulation;
	long			start_time;
}					t_data;

int					parse_args(int ac, char **av, t_config *config);
void				*monitor_routine(void *arg);
void				*philo_routine(void *arg);
int					init_data(t_data *data, t_config *config);
void				init_philos(t_data *data);
long				get_time_ms(void);
long				elapsed_time(long start_ms);
void				ft_usleep(long duration_ms, t_data *data);
void				print_action(t_philo *philo, const char *action);
void				take_forks(t_philo *philo);
void				eating(t_philo *philo);
void				release_forks(t_philo *philo);
void				sleeping(t_philo *philo);
void				thinking(t_philo *philo);

#endif
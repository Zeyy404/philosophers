/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:14:16 by zsalih            #+#    #+#             */
/*   Updated: 2025/09/04 10:56:34 by zsalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_config
{
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_meals;
}					t_config;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	t_config		config;
	int				*pids;
	long			start_time;
	sem_t			*sem_forks;
	sem_t			*sem_print;
	sem_t			*sem_death;
	sem_t			*sem_full;
}					t_data;

int					parse_args(int ac, char **av, t_config *config);
int					init_data(t_data *data, t_config *config);
int					init_philos(t_data *data);
void				philo_routine(t_data *data, int id);
long				get_time_ms(void);
long				elapsed_time(long start_ms);
void				ft_usleep(long duration_ms);
void				print_action(t_philo *philo, const char *action);
void				take_forks(t_philo *philo);
void				eating(t_philo *philo);
void				release_forks(t_philo *philo);
void				sleeping(t_philo *philo);
void				thinking(t_philo *philo);
void				cleanup_data(t_data *data);

#endif
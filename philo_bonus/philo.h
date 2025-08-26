/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:14:16 by zsalih            #+#    #+#             */
/*   Updated: 2025/08/26 09:29:36 by zsalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_config
{
	int		nbr_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nbr_meals;
}			t_config;

typedef struct s_data
{
	int		*pids;
	sem_t	*sem_forks;
	sem_t	*sem_print;
	sem_t	*sem_death;
	sem_t	*sem_full;
}			t_data;

int			parse_args(int ac, char **av, t_config *config);
int			init_data(t_data *data, t_config *config);
int			init_philos(t_data *data, t_config *config);

#endif
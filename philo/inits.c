/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 15:52:34 by zsalih            #+#    #+#             */
/*   Updated: 2025/09/15 10:34:35 by zsalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_mutexes(t_data *data, t_config *config)
{
	int	i;

	i = 0;
	while (i < config->nbr_philos)
	{
		pthread_mutex_init(&data->forks[i].fork_mutex, NULL);
		data->forks[i].available = 1;
		data->forks[i].prev_owner = 0;
		i++;
	}
	pthread_mutex_init(&data->state_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
}

int	init_data(t_data *data, t_config *config)
{
	if (!data || !config)
		return (0);
	data->config = *config;
	data->stop_simulation = 0;
	data->start_time = get_time_ms();
	data->forks = malloc(sizeof(t_fork) * config->nbr_philos);
	if (!data->forks)
		return (0);
	init_mutexes(data, config);
	data->philos = malloc(sizeof(t_philo) * config->nbr_philos);
	if (!data->philos)
	{
		free(data->forks);
		return (0);
	}
	return (1);
}

void	init_philos(t_data *data)
{
	int		i;
	t_philo	*ph;

	i = 0;
	while (i < data->config.nbr_philos)
	{
		ph = &data->philos[i];
		ph->id = i + 1;
		ph->meals_eaten = 0;
		ph->last_meal_time = data->start_time;
		ph->left_fork = &data->forks[i];
		ph->right_fork = &data->forks[(i + 1) % data->config.nbr_philos];
		ph->data = data;
		i++;
	}
}

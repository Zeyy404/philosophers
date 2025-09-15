/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 18:08:42 by zsalih            #+#    #+#             */
/*   Updated: 2025/09/15 11:00:30 by zsalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_data *data, t_philo *philo, long current_time)
{
	long	last_meal;

	pthread_mutex_lock(&data->state_mutex);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&data->state_mutex);
	if ((current_time - last_meal) > data->config.time_to_die)
	{
		pthread_mutex_lock(&data->state_mutex);
		data->stop_simulation = 1;
		pthread_mutex_unlock(&data->state_mutex);
		pthread_mutex_lock(&data->print_mutex);
		printf("%ld %d died\n", current_time, philo->id);
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	return (0);
}

static int	check_full(t_data *data)
{
	int	i;
	int	full;

	full = 1;
	i = 0;
	while (i < data->config.nbr_philos)
	{
		pthread_mutex_lock(&data->state_mutex);
		if (data->philos[i].meals_eaten < data->config.nbr_meals)
			full = 0;
		pthread_mutex_unlock(&data->state_mutex);
		i++;
	}
	return (full);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	long	current_time;

	data = (t_data *)arg;
	while (1)
	{
		usleep(1000);
		i = 0;
		while (i < data->config.nbr_philos)
		{
			current_time = elapsed_time(data->start_time);
			if (check_death(data, &data->philos[i], current_time))
				return (NULL);
			i++;
		}
		if (data->config.nbr_meals > 0 && check_full(data))
		{
			pthread_mutex_lock(&data->state_mutex);
			data->stop_simulation = 1;
			pthread_mutex_unlock(&data->state_mutex);
			break ;
		}
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		pthread_mutex_lock(&data->state_mutex);
		if (data->stop_simulation)
		{
			pthread_mutex_unlock(&data->state_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->state_mutex);
		take_forks(philo);
		eating(philo);
		release_forks(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

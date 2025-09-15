/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:54:17 by zsalih            #+#    #+#             */
/*   Updated: 2025/09/15 10:12:09 by zsalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->state_mutex);
	philo->last_meal_time = elapsed_time(philo->data->start_time);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->state_mutex);
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->stop_simulation)
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->state_mutex);
	ft_usleep(philo->data->config.time_to_eat, philo->data);
}

void	sleeping(t_philo *philo)
{
	print_action(philo, "is sleeping");
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->stop_simulation)
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->state_mutex);
	ft_usleep(philo->data->config.time_to_sleep, philo->data);
}

void	thinking(t_philo *philo)
{
	print_action(philo, "is thinking");
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->stop_simulation)
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->state_mutex);
}

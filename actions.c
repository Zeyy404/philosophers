/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:54:17 by zsalih            #+#    #+#             */
/*   Updated: 2025/08/11 13:43:24 by zsalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->state_mutex);
    philo->last_meal_time = elapsed_time(philo->data->start_time);
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->data->state_mutex);
    pthread_mutex_lock(&philo->data->print_mutex);
    if (!philo->data->stop_simulation)
        printf("%lld %d is eating\n", elapsed_time(philo->data->start_time), philo->id);
    pthread_mutex_unlock(&philo->data->print_mutex);
    ft_usleep(philo->data->config.time_to_eat, philo->data);
}

void	sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
    if (!philo->data->stop_simulation)
        printf("%lld %d is sleeping\n", elapsed_time(philo->data->start_time), philo->id);
    pthread_mutex_unlock(&philo->data->print_mutex);
    ft_usleep(philo->data->config.time_to_sleep, philo->data);
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
    if (!philo->data->stop_simulation)
        printf("%lld %d is thinking\n", elapsed_time(philo->data->start_time), philo->id);
    pthread_mutex_unlock(&philo->data->print_mutex);
}
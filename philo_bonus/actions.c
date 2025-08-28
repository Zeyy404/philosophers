/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:54:17 by zsalih            #+#    #+#             */
/*   Updated: 2025/08/28 09:09:18 by zsalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->sem_forks);
	sem_wait(philo->data->sem_forks);
	print_action(philo, "has taken a fork");
	print_action(philo, "has taken a fork");
}

void	release_forks(t_philo *philo)
{
	sem_post(philo->data->sem_forks);
	sem_post(philo->data->sem_forks);
}

void	eating(t_philo *philo)
{
	philo->last_meal_time = elapsed_time(philo->data->start_time);
	philo->meals_eaten++;
	print_action(philo, "is eating");
	ft_usleep(philo->data->config.time_to_eat);
}

void	sleeping(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->data->config.time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_action(philo, "is thinking");
}

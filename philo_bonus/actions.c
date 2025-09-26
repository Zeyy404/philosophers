/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:54:17 by zsalih            #+#    #+#             */
/*   Updated: 2025/09/26 18:35:33 by zsalih           ###   ########.fr       */
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
	check_death(philo);
	philo->last_meal_time = elapsed_time(philo->data->start_time);
	philo->meals_eaten++;
	print_action(philo, "is eating");
	ft_usleep(philo->data->config.time_to_eat, philo);
	if (philo->data->config.nbr_meals > 0
		&& philo->meals_eaten >= philo->data->config.nbr_meals)
	{
		sem_post(philo->data->sem_full);
		return ;
	}
}

void	sleeping(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->data->config.time_to_sleep, philo);
}

void	thinking(t_philo *philo)
{
	print_action(philo, "is thinking");
}

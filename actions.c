/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:54:17 by zsalih            #+#    #+#             */
/*   Updated: 2025/08/17 11:30:55 by zsalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	t_fork	*first_fork;
	t_fork	*second_fork;
	int		prev_owner;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	else
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	while (1)
	{
		pthread_mutex_lock(&philo->data->state_mutex);
		if (philo->data->stop_simulation)
		{
			pthread_mutex_unlock(&philo->data->state_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->state_mutex);
		pthread_mutex_lock(&first_fork->fork_mutex);
		if (first_fork->available == 1 && first_fork->prev_owner != philo->id)
		{
			first_fork->available = 0;
			prev_owner = first_fork->prev_owner;
			first_fork->prev_owner = philo->id;
			pthread_mutex_unlock(&first_fork->fork_mutex);
			pthread_mutex_lock(&second_fork->fork_mutex);
			if (second_fork->available == 1 && second_fork->prev_owner != philo->id)
			{
				second_fork->available = 0;
				second_fork->prev_owner = philo->id;
				pthread_mutex_unlock(&second_fork->fork_mutex);
				print_action(philo, "has taken a fork");
				print_action(philo, "has taken a fork");
				return ;
			}
			pthread_mutex_unlock(&second_fork->fork_mutex);
			pthread_mutex_lock(&first_fork->fork_mutex);
			first_fork->available = 1;
			first_fork->prev_owner = prev_owner;
			pthread_mutex_unlock(&first_fork->fork_mutex);
			usleep(1000);
		}
		else
		{
			pthread_mutex_unlock(&first_fork->fork_mutex);
			usleep(1000);
		}
	}
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	philo->left_fork->available = 1;
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	philo->right_fork->available = 1;
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
}

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

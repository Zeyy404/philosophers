/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:11:34 by zsalih            #+#    #+#             */
/*   Updated: 2025/09/15 10:31:05 by zsalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	fork_order(t_philo *philo, t_fork **first, t_fork **second)
{
	if (philo->id % 2 == 0)
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
	else
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
}

static int	try_first_fork(t_philo *philo, t_fork *first, int *prev_owner)
{
	int	success;

	success = 0;
	pthread_mutex_lock(&first->fork_mutex);
	if (first->available && first->prev_owner != philo->id)
	{
		*prev_owner = first->prev_owner;
		first->available = 0;
		first->prev_owner = philo->id;
		success = 1;
	}
	pthread_mutex_unlock(&first->fork_mutex);
	return (success);
}

static int	try_second_fork(t_philo *philo, t_fork *first, t_fork *second,
		int prev_owner)
{
	int	success;

	success = 0;
	pthread_mutex_lock(&second->fork_mutex);
	if (second->available && second->prev_owner != philo->id)
	{
		second->available = 0;
		second->prev_owner = philo->id;
		success = 1;
	}
	pthread_mutex_unlock(&second->fork_mutex);
	if (!success)
	{
		pthread_mutex_lock(&first->fork_mutex);
		first->available = 1;
		first->prev_owner = prev_owner;
		pthread_mutex_unlock(&first->fork_mutex);
	}
	return (success);
}

void	take_forks(t_philo *philo)
{
	t_fork	*first_fork;
	t_fork	*second_fork;
	int		prev_owner;

	fork_order(philo, &first_fork, &second_fork);
	while (1)
	{
		pthread_mutex_lock(&philo->data->state_mutex);
		if (philo->data->stop_simulation)
		{
			pthread_mutex_unlock(&philo->data->state_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->state_mutex);
		if (try_first_fork(philo, first_fork, &prev_owner)
			&& try_second_fork(philo, first_fork, second_fork, prev_owner))
		{
			print_action(philo, "has taken a fork");
			print_action(philo, "has taken a fork");
			return ;
		}
		usleep(1000);
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

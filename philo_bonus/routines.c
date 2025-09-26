/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 08:14:41 by zsalih            #+#    #+#             */
/*   Updated: 2025/09/26 18:33:18 by zsalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void check_death(t_philo *philo)
{
	long current_time;
	
	current_time = elapsed_time(philo->data->start_time);
	if ((current_time
		- philo->last_meal_time) > philo->data->config.time_to_die)
	{
		sem_wait(philo->data->sem_print);
		printf("%ld %d died\n", current_time, philo->id);
		sem_post(philo->data->sem_death);
		cleanup_data(philo->data);
		exit(1);
	}
}

void	philo_routine(t_data *data, int id)
{
	t_philo		philo;

	philo.id = id;
	philo.meals_eaten = 0;
	philo.last_meal_time = get_time_ms();
	philo.data = data;
	while (1)
	{
		check_death(&philo);
		take_forks(&philo);
		eating(&philo);
		release_forks(&philo);
		sleeping(&philo);
		thinking(&philo);
		if (data->config.nbr_meals > 0
			&& philo.meals_eaten >= data->config.nbr_meals)
			break ;
	}
	cleanup_data(data);
	exit(0);
}

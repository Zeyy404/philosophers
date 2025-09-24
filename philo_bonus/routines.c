/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 08:14:41 by zsalih            #+#    #+#             */
/*   Updated: 2025/09/24 23:07:31 by zsalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_routine(t_data *data, int id)
{
	t_philo		philo;

	philo.id = id;
	philo.meals_eaten = 0;
	philo.last_meal_time = get_time_ms();
	philo.data = data;
	while (1)
	{
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 08:14:41 by zsalih            #+#    #+#             */
/*   Updated: 2025/08/28 11:11:45 by zsalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*monitor_routine(void *arg)
{
	t_philo	*philo;
	long	current_time;
	int		full;

	philo = arg;
	while (1)
	{
		usleep(1000);
		full = 1;
		current_time = elapsed_time(philo->data->start_time);
		if ((current_time
				- philo->last_meal_time) > philo->data->config.time_to_die)
		{
			sem_wait(philo->data->sem_print);
			printf("%ld %d died\n", current_time, philo->id);
			sem_post(philo->data->sem_death);
			exit(1);
		}
		if (philo->data->config.nbr_meals > 0
			&& philo->meals_eaten < philo->data->config.nbr_meals)
			full = 0;
		if (full && philo->data->config.nbr_meals > 0)
		{
			sem_post(philo->data->sem_full);
			exit(0);
		}
	}
	return (NULL);
}

void	philo_routine(t_data *data, int id)
{
	pthread_t mointor;
	t_philo philo;

	philo.id = id;
	philo.meals_eaten = 0;
	philo.last_meal_time = get_time_ms();
	philo.data = data;
	pthread_create(&mointor, NULL, monitor_routine, &philo);
	while (1)
	{
		take_forks(&philo);
		eating(&philo);
		release_forks(&philo);
		sleeping(&philo);
		thinking(&philo);
		if (data->config.nbr_meals > 0 && philo.meals_eaten >= data->config.nbr_meals)
			break ;
	}
	pthread_join(mointor, NULL);
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 08:14:41 by zsalih            #+#    #+#             */
/*   Updated: 2025/08/27 17:17:09 by zsalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void *mointor_routine(t_philo *philo)
{
	long	current_time;
	int		full;
	long	last_meal;

	while (1)
	{
		usleep(1000);
		full = 1;
        current_time = elapsed_time(philo->data->start_time);
		if ((current_time - philo->last_meal_time) > philo->data->config.time_to_die)
		{
			sem_wait(philo->data->sem_print);
			printf("%ld %d died\n", current_time, philo->data);
			sem_post(philo->data->sem_print);
			exit(1);
		}
		if (philo->data->config.nbr_meals > 0 && philo->meals_eaten < philo->data->config.nbr_meals)
			full = 0;
		if (full && philo->data->config.nbr_meals > 0)
		{
			sem_post(philo->data->sem_full);
			break ;
		}
	}
}

void	philo_routine(t_data *data, int id)
{
	pthread_t mointor;
	t_philo	philo;
	
	philo.id = id;
	philo.meals_eaten = 0;
	philo.last_meal_time = get_time_ms();
	philo.data = data;
	pthread_create(&mointor, NULL, mointor_routine, &philo);
	while(1)
	{
		take_forks(&philo);
		eating(&philo);
		release_forks(&philo);
		sleeping(&philo);
		thinking(&philo);
	}
	pthread_join(&mointor, NULL);
}
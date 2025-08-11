/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:17:52 by zsalih            #+#    #+#             */
/*   Updated: 2025/08/11 12:52:00 by zsalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	elapsed_time(long start_ms)
{
	return (get_time_ms() - start_ms);
}

void	ft_usleep(long duration_ms, t_data *data)
{
	long	start;

	start = get_time_ms();
	while (1)
	{
		pthread_mutex_lock(&data->state_mutex);
		if (data->stop_simulation)
		{
			pthread_mutex_unlock(&data->state_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->state_mutex);
		if (elapsed_time(start) >= duration_ms)
			break ;
		usleep(500);
	}
}

void print_action(t_philo *philo, const char *action)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    if (!philo->data->stop_simulation)
        printf("%lld %d %s\n", get_timestamp(), philo->id, action);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

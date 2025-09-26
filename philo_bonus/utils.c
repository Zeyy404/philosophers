/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:17:52 by zsalih            #+#    #+#             */
/*   Updated: 2025/09/26 18:32:20 by zsalih           ###   ########.fr       */
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

void	ft_usleep(long duration_ms, t_philo *philo)
{
	long	start;

	start = get_time_ms();
	while (1)
	{
		check_death(philo);
		if (elapsed_time(start) >= duration_ms)
			break ;
		usleep(1000);
	}
}

void	print_action(t_philo *philo, const char *action)
{
	sem_wait(philo->data->sem_print);
	printf("%ld %d %s\n", elapsed_time(philo->data->start_time), philo->id,
		action);
	sem_post(philo->data->sem_print);
}

void	cleanup_data(t_data *data)
{
	sem_close(data->sem_forks);
	sem_close(data->sem_full);
	sem_close(data->sem_death);
	sem_close(data->sem_print);
	sem_unlink("/sem_forks");
	sem_unlink("/sem_print");
	sem_unlink("/sem_death");
	sem_unlink("/sem_full");
	free(data->pids);
}

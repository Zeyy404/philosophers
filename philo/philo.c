/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:13:36 by zsalih            #+#    #+#             */
/*   Updated: 2025/09/15 10:39:48 by zsalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_threads(t_data *data, pthread_t monitor)
{
	int	i;

	i = 0;
	while (i < data->config.nbr_philos)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}

int	main(int ac, char **av)
{
	t_config	config;
	t_data		data;
	pthread_t	monitor;
	int			i;

	if (!parse_args(ac, av, &config))
		return (1);
	if (!init_data(&data, &config))
		return (1);
	init_philos(&data);
	i = 0;
	while (i < data.config.nbr_philos)
	{
		if (pthread_create(&data.philos[i].thread_id, NULL, philo_routine,
				&data.philos[i]) != 0)
			perror("pthread_create failed");
		i++;
	}
	pthread_create(&monitor, NULL, monitor_routine, &data);
	join_threads(&data, monitor);
	cleanup_data(&data);
	return (0);
}

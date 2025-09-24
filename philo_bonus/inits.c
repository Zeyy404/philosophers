/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 08:19:27 by zsalih            #+#    #+#             */
/*   Updated: 2025/09/24 22:56:28 by zsalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, t_config *config)
{
	if (!config)
		return (0);
	data->config = *config;
	data->pids = malloc(sizeof(int) * config->nbr_philos);
	if (!data->pids)
		return (0);
	data->start_time = get_time_ms();
	sem_unlink("/sem_forks");
	sem_unlink("/sem_print");
	sem_unlink("/sem_death");
	sem_unlink("/sem_full");
	data->sem_forks = sem_open("/sem_forks", O_CREAT, 0644, config->nbr_philos);
	data->sem_print = sem_open("/sem_print", O_CREAT, 0644, 1);
	data->sem_death = sem_open("/sem_death", O_CREAT, 0644, 0);
	data->sem_full = sem_open("/sem_full", O_CREAT, 0644, 0);
	if (data->sem_forks == SEM_FAILED || data->sem_print == SEM_FAILED
		|| data->sem_death == SEM_FAILED || data->sem_full == SEM_FAILED)
	{
		perror("sem_open");
		cleanup_data(data);
		return (0);
	}
	return (1);
}

int	init_philos(t_data *data)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i < data->config.nbr_philos)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return (0);
		}
		if (pid == 0)
		{
			philo_routine(data, (i + 1));
			exit(0);
		}
		else
			data->pids[i] = pid;
		i++;
	}
	return (1);
}

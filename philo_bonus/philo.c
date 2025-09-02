/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:13:36 by zsalih            #+#    #+#             */
/*   Updated: 2025/09/02 09:16:56 by zsalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void kill_philos(t_data *data)
{
	int i;

	i = 0;
	while (i < data->config.nbr_philos)
	{
		kill(data->pids[i], SIGKILL);
		i++;
	}
}

void *mointor_death(void *arg)
{
	t_data *data;
	
	data = arg;
	sem_wait(data->sem_death);
	return (NULL);
}

void *mointor_full(void *arg)
{
	t_data *data;
	int i;

	data = arg;
	i = 0;
	while (i < data->config.nbr_philos)
	{
		sem_wait(data->sem_full);
		i++;
	}
	sem_post(data->sem_death);
	return (NULL);
}

void monitor_philos(t_data *data)
{
	pthread_t death;
	pthread_t full;

	if (data->config.nbr_meals > 0)
	{
		pthread_create(&full, NULL, mointor_full, data);
		pthread_join(full, NULL);
	}
	pthread_create(&death, NULL, mointor_death, data);
	pthread_join(death, NULL);
	kill_philos(data);
}

int	main(int ac, char **av)
{
	t_config	config;
	t_data		data;
	int			i;

	if (!parse_args(ac, av, &config))
		return (1);
	if (!init_data(&data, &config))
		return (1);
	if (!init_philos(&data))
		return (1);
	monitor_philos(&data);
	i = 0;
	while (i < config.nbr_philos)
	{
		waitpid(data.pids[i], NULL, 0);
		i++;
	}
	cleanup_data(&data);
	return (0);
}

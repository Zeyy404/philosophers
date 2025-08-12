/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih < zsalih@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:13:36 by zsalih            #+#    #+#             */
/*   Updated: 2025/08/13 00:21:29 by zsalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_config config;
    t_data   data;
	pthread_t monitor;

    if (!parse_args(ac, av, &config))
        return (1);
    if (!init_data(&data, &config))
        return (1);
    init_philos(&data);
    for (int i = 0; i < data.config.nbr_philos; i++) {
        if (pthread_create(&data.philos[i].thread_id, NULL, philo_routine, &data.philos[i]) != 0)
            perror("pthread_create failed"); 
    }
	pthread_create(&monitor, NULL, monitor_routine, &data);
    for (int i = 0; i < data.config.nbr_philos; i++) {
        pthread_join(data.philos[i].thread_id, NULL); }
    pthread_join(monitor, NULL);
    // cleanup_data(&data);
    return (0);
}


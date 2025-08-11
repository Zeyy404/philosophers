/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih < zsalih@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:13:36 by zsalih            #+#    #+#             */
/*   Updated: 2025/08/11 10:13:19 by zsalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_config config;
    t_data   data;
	pthread_t monitor;

    // Step 1: Parse & validate args
    memset(&config, -1, sizeof(t_config));
    if (parse_args(ac, av, &config))
        return (1);

    // Step 2: Init data
    if (init_data(&data, &config))
        return (1);

    // Step 3: Init philosophers
    init_philos(&data);

    // Step 4: Create philosopher threads
    for (int i = 0; i < data.config.nbr_philos; i++)
        pthread_create(&data.philos[i].thread_id, NULL, philo_routine, &data.philos[i]);

	// Step 4.1: Create monitor thread
	pthread_create(&monitor, NULL, monitor_routine, &data);

    // Step 5: Join philosopher threads (temporary for now)
    for (int i = 0; i < data.config.nbr_philos; i++)
        pthread_join(data.philos[i].thread_id, NULL);

    // Step 6: Cleanup
    cleanup_data(&data);
    return (0);
}


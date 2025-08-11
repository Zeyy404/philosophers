/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 18:08:42 by zsalih            #+#    #+#             */
/*   Updated: 2025/08/11 13:37:39 by zsalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;
    int     i;
    long    current_time;
    int     all_full;

    while (1)
    {
        usleep(1000);
        pthread_mutex_lock(&data->state_mutex);
        if (data->stop_simulation)
        {
            pthread_mutex_unlock(&data->state_mutex);
            break;
        }
        pthread_mutex_unlock(&data->state_mutex);

        all_full = 1;
        current_time = elapsed_time(data->start_time);
        i = 0;
        while (i < data->config.nbr_philos)
        {
            pthread_mutex_lock(&data->state_mutex);
            long last_meal = data->philos[i].last_meal_time;
            int  meals     = data->philos[i].meals_eaten;
            pthread_mutex_unlock(&data->state_mutex);
            if ((current_time - last_meal) > data->config.time_to_die)
            {
                pthread_mutex_lock(&data->state_mutex);
                data->stop_simulation = 1;
                pthread_mutex_unlock(&data->state_mutex);

                pthread_mutex_lock(&data->print_mutex);
                printf("%ld %d died\n", current_time, data->philos[i].id);
                pthread_mutex_unlock(&data->print_mutex);

                return NULL;
            }
            if (data->config.nbr_meals > 0 && meals < data->config.nbr_meals)
                all_full = 0;
            i++;
        }
        if (all_full && data->config.nbr_meals > 0)
        {
            pthread_mutex_lock(&data->state_mutex);
            data->stop_simulation = 1;
            pthread_mutex_unlock(&data->state_mutex);
            break;
        }
    }
    return NULL;
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_data  *data = philo->data;

    while (1)
    {
        pthread_mutex_lock(&data->state_mutex);
        if (data->stop_simulation)
        {
            pthread_mutex_unlock(&data->state_mutex);
            break;
        }
        pthread_mutex_unlock(&data->state_mutex);
        take_forks(philo);
        eat(philo);
        release_forks(philo);
        pthread_mutex_lock(&data->print_mutex);
        printf("%ld %d is sleeping\n", elapsed_time(data->start_time), philo->id);
        pthread_mutex_unlock(&data->print_mutex);
        ft_usleep(data->config.time_to_sleep, data);
        pthread_mutex_lock(&data->print_mutex);
        printf("%ld %d is thinking\n", elapsed_time(data->start_time), philo->id);
        pthread_mutex_unlock(&data->print_mutex);
    }
    return NULL;
}

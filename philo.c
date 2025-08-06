/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:13:36 by zsalih            #+#    #+#             */
/*   Updated: 2025/08/06 17:11:35 by zsalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo_config info;

	memset(&info, -1, sizeof(t_philo_config));
	if (ac < 5 || ac > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	else
	{
		info.nbr_philos = ft_atoi(av[1]);
		info.time_to_die = ft_atoi(av[2]);
		info.time_to_eat = ft_atoi(av[3]);
		info.time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			info.nbr_meals = ft_atoi(av[5]);
	}
	// check if the nbr_philos or time_to_die,eat,sleep is 0 or negative => throw an error and exit!
	return (0);
}

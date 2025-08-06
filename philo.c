/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:13:36 by zsalih            #+#    #+#             */
/*   Updated: 2025/08/06 20:15:32 by zsalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handle_overflow(long result, int sign, int *error)
{
	if (result == INT_MAX)
		return (result * sign);
	if (result > INT_MAX)
	{
		if (sign == -1)
		{
			if (result == 2147483648)
				return (-2147483648);
			return (*error = 1, 0);
		}
		return (*error = 1, -1);
	}
	return (result * sign);
}

static int	ft_atoi(const char *nptr, int *error)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + ((*nptr) - '0');
		nptr++;
	}
	if (*nptr != '\0' && (*nptr < '0' || *nptr > '9'))
		return (*error = 1, 0);
	return (handle_overflow(result, sign, error));
}

int	main(int ac, char **av)
{
	t_philo_config	info;
	int				error;

	memset(&info, -1, sizeof(t_philo_config));
	error = 0;
	if (ac < 5 || ac > 6)
	{
		printf("Usage: ./philo <nbr_of_philosophers> <time_to_die> "
			"<time_to_eat> <time_to_sleep> [nbr_of_meals]\n");
		return (1);
	}
	else
	{
		info.nbr_philos = ft_atoi(av[1], &error);
		info.time_to_die = ft_atoi(av[2], &error);
		info.time_to_eat = ft_atoi(av[3], &error);
		info.time_to_sleep = ft_atoi(av[4], &error);
		if (ac == 6)
			info.nbr_meals = ft_atoi(av[5], &error);
	}
	if (error || info.nbr_philos <= 0 || info.time_to_die <= 0 || info.time_to_eat <= 0
		|| info.time_to_sleep <= 0 || (ac == 6 && info.nbr_meals <= 0))
	{
		printf("Error: invalid argument(s)\n");
		return (1);
	}
	return (0);
}

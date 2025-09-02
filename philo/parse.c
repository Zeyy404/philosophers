/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:33:02 by zsalih            #+#    #+#             */
/*   Updated: 2025/09/02 09:45:44 by zsalih           ###   ########.fr       */
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

int	parse_args(int ac, char **av, t_config *config)
{
	int	error;

	error = 0;
	if (ac < 5 || ac > 6)
	{
		printf("Usage: ./philo <nbr_of_philosophers> <time_to_die> "
				"<time_to_eat> <time_to_sleep> [nbr_of_meals]\n");
		return (0);
	}
	config->nbr_philos = ft_atoi(av[1], &error);
	config->time_to_die = ft_atoi(av[2], &error);
	config->time_to_eat = ft_atoi(av[3], &error);
	config->time_to_sleep = ft_atoi(av[4], &error);
	if (ac == 6)
		config->nbr_meals = ft_atoi(av[5], &error);
	else
		config->nbr_meals = -1;
	if (config->nbr_philos <= 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(config->time_to_die * 1000);
		printf("%d 1 died\n", config->time_to_die);
		return (0);
	}
	if (error || config->nbr_philos <= 0 || config->time_to_die <= 0
		|| config->time_to_eat <= 0 || config->time_to_sleep <= 0 || (ac == 6
			&& config->nbr_meals <= 0))
	{
		printf("Error: Invalid arguments.\n");
		return (0);
	}
	return (1);
}

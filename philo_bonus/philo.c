/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsalih <zsalih@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:13:36 by zsalih            #+#    #+#             */
/*   Updated: 2025/08/26 09:02:34 by zsalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_config	config;
	t_data		data;

	if (!parse_args(ac, av, &config))
		return (1);
	if (!init_data(&data, &config))
		return (1);
	// cleanup_data(&data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:24:01 by lsileoni          #+#    #+#             */
/*   Updated: 2023/07/28 22:37:43 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stddef.h>

int	main(int argc, char **argv)
{
	const t_args	args = parse_args(argc, argv);
	size_t			simulation_state;
	size_t			simulation_start;

	if (!args.set)
		return (printf("Issue in parsing arguments!\n"));
	if (!init_simulation(args, &simulation_state, &simulation_start))
		return (printf("Issue in initializing simulation!\n"));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:14:00 by lsileoni          #+#    #+#             */
/*   Updated: 2023/07/03 15:12:14 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stddef.h>

static int	assign_philo_value(size_t *value, char *arg)
{
	int	tmp;

	tmp = ft_atoi(arg);
	if (tmp < 1)
		return (0);
	*value = tmp;
	return (1);
}

static int	assign_values(t_args *args, char **argv, int argc)
{
	int		i;

	i = 0;
	while (i < argc - 1)
	{
		if (!assign_philo_value(&(&(args->philo_count))[i], argv[i + 1]))
			return (0);
		i++;
	}
	return (1);
}

t_args	parse_args(int argc, char **argv)
{
	t_args	args;

	ft_bzero(&args, sizeof(args));
	if (argc == 5 || argc == 6)
	{
		args.set = 1;
		if (!assign_values(&args, argv, argc))
			args.set = 0;
		// printf("args->philo_count: %zu\n", args.philo_count);
		// printf("args->eating_times: %zu\n", args.eating_times);
		// printf("args->set: %zu\n", args.set);
		// printf("args->ttd: %zu\n", args.ttd);
		// printf("args->tte: %zu\n", args.tte);
		// printf("args->tts: %zu\n", args.tts);
	}
	return (args);
}

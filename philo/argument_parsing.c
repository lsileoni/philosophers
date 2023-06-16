/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:14:00 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/16 14:20:11 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	assign_philo_value(size_t *value, char *arg)
{
	*value = ft_atoi(arg);
	if (*value <= 0)
		return (0);
	return (1);
}

static int	assign_values(t_args *args, char **argv, int argc)
{
	if (!assign_philo_value(&args->philo_count, argv[1]))
		return (0);
	if (!assign_philo_value(&args->ttd, argv[2]))
		return (0);
	if (!assign_philo_value(&args->tte, argv[3]))
		return (0);
	if (!assign_philo_value(&args->tts, argv[4]))
		return (0);
	if (argc == 6)
		if (!assign_philo_value(&args->eating_times, argv[5]))
			return (0);
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
	}
	return (args);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:14:00 by lsileoni          #+#    #+#             */
/*   Updated: 2023/07/17 15:56:14 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit(unsigned char c)
{
	if (c > 39 && c < 58)
		return (1);
	return (0);
}

static int	valid_number(const char *arg)
{
	size_t	len;

	len = 0;
	while (arg[len])
		len++;
	if (len > 6)
		return (0);
	if (*arg == '+')
		arg++;
	while (*arg)
	{
		if (!is_digit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

static int	assign_philo_value(size_t *value, char *arg)
{
	int	tmp;

	if (!valid_number(arg))
		return (0);
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
		if (!i && (&(args->philo_count))[i] > MAX_THREAD)
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
	}
	if (argc == 6)
		args.eating_set = 1;
	else
		args.eating_set = 0;
	return (args);
}

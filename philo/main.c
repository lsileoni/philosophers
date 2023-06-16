/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:24:01 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/13 15:39:40 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stddef.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

typedef struct s_args
{
	size_t	philo_count;
	size_t	tts;
	size_t	ttd;
	size_t	tte;
	size_t	eating_times;
	size_t	set;
} t_args;

// int	init_mutexes(int num)
// {
// 	
// 	return (1);
// }

t_args	parse_args(int argc, char **argv)
{
	t_args args;

	(void) argv;
	ft_bzero(&args, sizeof(args));
	if (argc == 4 || argc == 5)
		args.set = 1;
	return (args);
}

int	main(int argc, char **argv)
{
	const t_args	args = parse_args(argc, argv);

	if (!args.set)
		ft_printf("SEIS");
	else
		ft_printf("GOOD\n");
	return (0);
}

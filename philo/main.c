/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:24:01 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/16 19:29:06 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stddef.h>
#include <errno.h>

int	lock_forks(t_philo *philos, size_t philo_count)
{
	size_t	i;
	int		rval;

	i = 0;
	while (i < philo_count - 1)
	{
		//printf("Left fork is %p\tRight fork is %p\n", philos[i].left_fork, philos[i].right_fork);
		rval = pthread_mutex_lock(philos[i].left_fork);
		if (rval != 0)
		{
			perror("");
			return (0);
		}
		rval = pthread_mutex_lock(philos[i].right_fork);
		if (rval != 0)
		{
			perror("");
			return (0);
		}
		philos[i].state = P_EATING;
		i += 2;
	}
	return (1);
}

int	begin_simulation(t_philo *philo, t_args args)
{
	
}

int	main(int argc, char **argv)
{
	const t_args	args = parse_args(argc, argv);
	t_philo			*philos;
	// size_t			i;

	if (!args.set)
		return (printf("Issue in parsing arguments!\n"));
	if (!init_philos(&philos, &args))
		return (printf("Issue in initializing philosophers!\n"));
	if (!lock_forks(philos, args.philo_count))
		return (printf("Issue in locking forks!\n"));
	if (!begin_simulation(philos, args))
		return (printf("Issue in beginning the simulation!\n"));
	// i = 0;
	// while (i < args.philo_count)
	// {
	// 	ft_printf("philos[%d]->state: %d\n", i, philos[i].state);
	// 	ft_printf("philos[%d]->left_fork: %p\n", i, philos[i].left_fork);
	// 	ft_printf("philos[%d]->right_fork: %p\n", i, philos[i].right_fork);
	// 	i++;
	// }
	return (0);
}

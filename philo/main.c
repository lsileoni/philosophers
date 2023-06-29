/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:24:01 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/29 14:14:19 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stddef.h>
#include <errno.h>
#include <sys/_pthread/_pthread_t.h>
#include <time.h>
#include <stdio.h>

int	lock_forks(t_philo *philos, size_t philo_count)
{
	size_t	i;
	int		rval;

	i = 0;
	while (i < philo_count - 1)
	{
		rval = pthread_mutex_lock(philos[i].left_fork);
		if (rval != 0)
			return (0);
		rval = pthread_mutex_lock(philos[i].right_fork);
		if (rval != 0)
			return (0);
		philos[i].state = P_EATING;
		i += 2;
	}
	return (1);
}

void	*philosopher_simulation(void *arg)
{
	(void)arg;

	while (1)
	{
		printf("Hi I am philosopher\n");
		sleep(1);
	}
	return (NULL);
}

int	begin_simulation(t_philo *philos, t_args args)
{
	size_t			i;
	pthread_t		*threads;

	threads = malloc(sizeof(pthread_t) * args.philo_count);
	i = 0;
	while (i < args.philo_count)
	{
		pthread_create(&threads[i], NULL, philosopher_simulation, &philos[i]);
		i++;
	}
	i = 0;
	while (i < args.philo_count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	const t_args	args = parse_args(argc, argv);
	t_philo			*philos;

	if (!args.set)
		return (printf("Issue in parsing arguments!\n"));
	if (!init_philos(&philos, &args))
		return (printf("Issue in initializing philosophers!\n"));
	if (!lock_forks(philos, args.philo_count))
		return (printf("Issue in locking forks!\n"));
	if (!begin_simulation(philos, args))
		return (printf("Issue in beginning the simulation!\n"));
	return (0);
}

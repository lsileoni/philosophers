/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:24:01 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/30 17:51:22 by lsileoni         ###   ########.fr       */
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

void	sleep_one_ms(void)
{
	size_t	i;

	i = 0;
	while (i < 10)
	{
		usleep(100);
		i++;
	}
}

void	sleep_n_ms(size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		sleep_one_ms();
		i++;
	}
}

size_t	assign_bound(unsigned int state, t_args args)
{
	if (state == P_THINKING)
		return (args.ttd);
	if (state == P_SLEEPING)
		return (args.tts);
	if (state == P_EATING)
		return (args.tte);
	return (0);
}


void	*philosopher_simulation(void *arg)
{
	t_philo			*philo;
	int				contested;
	size_t			sleep_bound;

	contested = 1;
	philo = arg;
	sleep_bound = 0;
	printf("philo addr: %p\n", philo);
	while (1)
	{
		if (contested)
		{
			if (pthread_mutex_lock(philo->simulation) == 0)
			{
				if (pthread_mutex_unlock(philo->simulation) == 0)
					contested = 0;
			}
			usleep(300);
		}
		else
		{
			while (philo->state != P_DONE)
			{
				sleep_bound = assign_bound(philo->state, philo->params);
				while (1)
				{
					if (philo->state == P_UNINITIALIZED)
						philo->state = P_THINKING;
					if (philo->ms_state >= sleep_bound)
						break ;
					if (pthread_mutex_lock(philo->simulation) != 0)
						return (0);
					else
						pthread_mutex_unlock(philo->simulation);
					sleep_one_ms();
					philo->ms_state += 1;
				}
			}
		}
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
	pthread_mutex_unlock(philos[0].simulation);
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

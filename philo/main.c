/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:24:01 by lsileoni          #+#    #+#             */
/*   Updated: 2023/07/13 05:11:24 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stddef.h>
#include <errno.h>
#include <sys/_pthread/_pthread_t.h>
#include <time.h>
#include <stdio.h>
#include <sys/time.h>

int	unlock_forks(t_philo *philos, size_t philo_count)
{
	size_t	i;
	int		rval;

	i = 0;
	while (i < philo_count - 1)
	{
		rval = pthread_mutex_unlock(philos[i].left_fork);
		if (rval != 0)
			return (0);
		rval = pthread_mutex_unlock(philos[i].right_fork);
		if (rval != 0)
			return (0);
		i++;
	}
	return (1);
}

void	sleep_one_ms(void)
{
	size_t	i;

	i = 0;
	while (i < 100)
	{
		usleep(10);
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

int	try_print(t_philo *philo, const char *message)
{
	if (pthread_mutex_lock(philo->simulation) != 0)
		return (-1);
	else
	{
		if (*(philo->simulation_state) == S_DONE)
		{
			pthread_mutex_unlock(philo->simulation);
			return (0);
		}
		printf("%zu %d %s\n", *(philo->timestamp), philo->id, message);
		pthread_mutex_unlock(philo->simulation);
	}
	return (1);
}

int	try_lock(t_philo *philo, const char *message)
{
	if (pthread_mutex_lock(philo->simulation) != 0)
		return (0);
	else
	{
		if (*(philo->simulation_state) == S_DONE)
		{
			pthread_mutex_unlock(philo->simulation);
			return (0);
		}
		printf("%zu %d %s\n", *(philo->timestamp), philo->id, message);
		*(philo->simulation_state) = S_DONE;
		philo->state = P_DEAD;
		pthread_mutex_unlock(philo->simulation);
	}
	return (1);
}

int	try_thinking(t_philo *philo)
{
	if (!try_print(philo, "THINKING"))
		return (0);
	printf("%zu %d TAKING LEFT FORK\n", *(philo->timestamp), philo->id);
	if (pthread_mutex_lock(philo->left_fork) != 0)
		return (0);
	printf("%zu %d TOOK LEFT FORK\n", *(philo->timestamp), philo->id);
	if (philo->ms_state >= philo->params.ttd)
	{
		(void)try_lock(philo, "DIED");
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	if (try_print(philo, "TAKING RIGHT FORK") <= 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	if (pthread_mutex_lock(philo->right_fork) != 0)
		return (0);
	printf("%zu %d TOOK RIGHT FORK\n", *(philo->timestamp), philo->id);
	philo->state = P_EATING;
	return (1);
}

int	try_eating(t_philo *philo)
{
	if (try_print(philo, "EATING") <= 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	if (philo->ms_state >= philo->params.ttd)
	{
		(void)try_lock(philo, "DIED");
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	philo->ms_state = 0;
	sleep_n_ms(philo->params.tte);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->times_eaten++;
	philo->state = P_SLEEPING;
	return (1);
}

int	try_sleeping(t_philo *philo)
{
	if (try_print(philo, "SLEEPING") <= 0)
		return (0);
	sleep_n_ms(philo->params.tts);
	philo->state = P_THINKING;
	return (1);
}


void	*philosopher_simulation(void *arg)
{
	t_philo			*philo;

	philo = arg;
	while (*(philo->simulation_state) != S_STARTED)
		usleep(10);
	if (philo->id % 2)
		sleep_n_ms(5);
	philo->ms_state = 0;
	while (philo->state != P_DONE)
	{
		if (philo->state == P_THINKING)
		{
			if (!try_thinking(philo))
				return (NULL);
			if (!try_eating(philo))
				return (NULL);
			if (philo->params.eating_times != 0 && philo->times_eaten >= philo->params.eating_times)
			{
				philo->state = P_DONE;
				return (NULL);
			}
			if (!try_sleeping(philo))
				return (NULL);
		}
	}
	return (NULL);
}

int	begin_simulation(t_philo *philos, t_args args)
{
	size_t			i;
	size_t			philos_done;
	pthread_t		*threads;

	threads = malloc(sizeof(pthread_t) * args.philo_count);
	i = 0;
	pthread_mutex_unlock(philos[0].simulation);
	while (i < args.philo_count)
	{
		pthread_create(&threads[i], NULL, philosopher_simulation, &philos[i]);
		i++;
	}
	while (*(philos[0].simulation_state) != S_DONE)
	{
		i = 0;
		*(philos[0].simulation_state) = S_STARTED;
		while (i < args.philo_count)
		{
			philos[i].ms_state += 1;
			i++;
		}
		sleep_one_ms();
		(*(philos[0].timestamp))++;
		i = 0;
		philos_done = 0;
		while (i < args.philo_count)
		{
			if (philos[i].state == P_DONE)
				philos_done++;
			i++;
		}
		if (philos_done == args.philo_count)
			*(philos[0].simulation_state) = S_DONE;
	}
	i = 0;
	while (i < args.philo_count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	printf("SIMULATION END!\n");
	return (1);
}

int	main(int argc, char **argv)
{
	const t_args	args = parse_args(argc, argv);
	t_philo			*philos;

	if (!args.set)
		return (printf("Issue in parsing arguments!\n"));
	if (!init_philos(&philos, args))
		return (printf("Issue in initializing philosophers!\n"));
	if (!unlock_forks(philos, args.philo_count))
		return (printf("Issue in locking forks!\n"));
	if (!begin_simulation(philos, args))
		return (printf("Issue in beginning the simulation!\n"));
	return (0);
}

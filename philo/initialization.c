/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:27:39 by lsileoni          #+#    #+#             */
/*   Updated: 2023/07/13 23:13:22 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stddef.h>

static int	init_mutexes(pthread_mutex_t *forks, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

static int	assign_forks(pthread_mutex_t *forks, t_philo *philos, t_args args, size_t n)
{
	size_t			i;
	size_t			*timestamp;
	size_t			*simulation_state;
	size_t			*simulation_start;
	pthread_mutex_t	*simulation;
	pthread_mutex_t	*print;

	simulation_start = malloc(sizeof(size_t *));
	*simulation_start = 0;
	timestamp = malloc(sizeof(size_t *));
	*timestamp = 0;
	if (!timestamp)
		return (0);
	simulation_state = malloc(sizeof(size_t *));
	*simulation_state = S_UNINITIALIZED;
	if (!simulation_state)
	{
		free(timestamp);
		return (0);
	}
	simulation = malloc(sizeof(pthread_mutex_t));
	if (!simulation)
	{
		free(timestamp);
		free(simulation_state);
		return (0);
	}
	print = malloc(sizeof(pthread_mutex_t));
	if (!print)
	{
		free(timestamp);
		free(simulation);
		free(simulation_state);
		return (0);
	}
	if (!init_mutexes(forks, n))
	{
		free(print);
		free(timestamp);
		free(simulation);
		free(simulation_state);
		return (0);
	}
	pthread_mutex_init(simulation, NULL);
	pthread_mutex_init(print, NULL);
	pthread_mutex_lock(simulation);
	i = 0;
	while (i < n - 1)
	{
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[i + 1];
		philos[i].state = P_THINKING;
		philos[i].ms_state = 0;
		philos[i].simulation = simulation;
		philos[i].simulation_state = simulation_state;
		philos[i].simulation_start = simulation_start;
		philos[i].time_since_eating = 0;
		philos[i].print = print;
		philos[i].id = i + 1;
		philos[i].timestamp = timestamp;
		philos[i].params = args;
		philos[i].record = 1;
		i++;
	}
	philos[i].left_fork = &forks[i];
	philos[i].right_fork = &forks[0];
	philos[i].state = P_THINKING;
	philos[i].simulation = simulation;
	philos[i].simulation_state = simulation_state;
	philos[i].simulation_start = simulation_start;
	philos[i].time_since_eating = 0;
	philos[i].timestamp = timestamp;
	philos[i].print = print;
	philos[i].id = i + 1;
	philos[i].params = args;
	philos[i].ms_state = 0;
	philos[i].record = 1;
	return (1);
}

int	init_philos(t_philo **philos, const t_args args)
{
	pthread_mutex_t	*forks;

	*philos = ft_calloc(sizeof(t_philo), args.philo_count);
	if (!(*philos))
		return (0);
	forks = ft_calloc(sizeof(pthread_mutex_t), args.philo_count);
	if (!forks)
	{
		free(*philos);
		return (0);
	}
	if (!assign_forks(forks, *philos, args, args.philo_count))
	{
		free(*philos);
		free(forks);
		return (0);
	}
	return (1);
}

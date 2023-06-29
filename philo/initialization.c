/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:27:39 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/29 14:01:13 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

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

static int	assign_forks(pthread_mutex_t *forks, t_philo *philos, size_t n)
{
	size_t			i;
	pthread_mutex_t	*simulation;
	pthread_mutex_t	*print;

	simulation = malloc(sizeof(pthread_mutex_t));
	if (!simulation)
		return (0);
	print = malloc(sizeof(pthread_mutex_t));
	if (!print)
	{
		free(simulation);
		return (0);
	}
	if (!init_mutexes(forks, n))
		return (0);
	pthread_mutex_init(simulation, NULL);
	pthread_mutex_init(print, NULL);
	pthread_mutex_lock(simulation);
	i = 0;
	while (i < n - 1)
	{
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[i + 1];
		philos[i].state = P_UNINITIALIZED;
		philos[i].simulation = simulation;
		philos[i].print = print;
		// ft_printf("i: %d\n", i);
		// ft_printf("philos[%d]->state: %d\n", i, philos[i].state);
		i++;
	}
	philos[i].left_fork = (&forks)[i];
	philos[i].right_fork = (&forks)[0];
	philos[i].state = P_UNINITIALIZED;
	return (1);
}

int	init_philos(t_philo **philos, const t_args *args)
{
	pthread_mutex_t	*forks;

	*philos = ft_calloc(sizeof(t_philo), args->philo_count);
	if (!(*philos))
		return (0);
	forks = ft_calloc(sizeof(pthread_mutex_t), args->philo_count);
	if (!forks)
	{
		free(*philos);
		return (0);
	}
	if (!assign_forks(forks, *philos, args->philo_count))
	{
		free(*philos);
		free(forks);
		return (0);
	}
	return (1);
}

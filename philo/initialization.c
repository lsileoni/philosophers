/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:27:39 by lsileoni          #+#    #+#             */
/*   Updated: 2023/07/17 15:39:37 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_forks(int i, pthread_mutex_t *forks)
{
	while (--i != -1)
		(void)pthread_mutex_destroy(&forks[i]);
}

int	init_mutexes(pthread_mutex_t *forks,
			pthread_mutex_t *simulation, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			destroy_forks(i, forks);
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(simulation, NULL) != 0)
	{
		destroy_forks(i, forks);
		return (0);
	}
	return (1);
}

int	allocate_philo_vars(size_t **simulation_state,
		size_t **simulation_start, pthread_mutex_t **simulation)
{
	*simulation_start = malloc(sizeof(size_t *));
	if (!(*simulation_start))
		return (0);
	*(*simulation_start) = 0;
	*simulation_state = malloc(sizeof(size_t *));
	if (!(*simulation_state))
	{
		free(*simulation_start);
		return (0);
	}
	*(*simulation_state) = S_UNINITIALIZED;
	*simulation = malloc(sizeof(pthread_mutex_t));
	if (!(*(simulation)))
	{
		free(*simulation_state);
		free(*simulation_start);
		return (0);
	}
	return (1);
}

int	init_philos(t_philo **philos, const t_args args)
{
	pthread_mutex_t	*forks;

	*philos = malloc(sizeof(t_philo) * args.philo_count);
	if (!(*philos))
		return (0);
	forks = malloc(sizeof(pthread_mutex_t) * args.philo_count);
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

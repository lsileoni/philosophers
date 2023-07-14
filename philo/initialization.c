/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:27:39 by lsileoni          #+#    #+#             */
/*   Updated: 2023/07/14 10:37:46 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stddef.h>

static void	destroy_forks(int i, pthread_mutex_t *forks)
{
	while (--i != -1)
		pthread_mutex_destroy(&forks[i]);
}

static int	init_mutexes(pthread_mutex_t *forks, pthread_mutex_t *simulation, int n)
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

static void	assign_philo_forks(t_philo *philo, pthread_mutex_t *left_fork,
							pthread_mutex_t *right_fork)
{
	philo->left_fork = left_fork;
	philo->right_fork = right_fork;
}

static void	assign_philo_vars(t_philo *philo, size_t *simulation_state,
							size_t *simulation_start, pthread_mutex_t *simulation)
{
	philo->state = P_THINKING;
	philo->simulation = simulation;
	philo->simulation_state = simulation_state;
	philo->simulation_start = simulation_start;
	philo->time_since_eating = 0;
}

static int	allocate_philo_vars(size_t **simulation_state, size_t **simulation_start, pthread_mutex_t **simulation)
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

static int	assign_forks(pthread_mutex_t *forks, t_philo *philos, t_args args, size_t n)
{
	size_t			i;
	size_t			*simulation_state;
	size_t			*simulation_start;
	pthread_mutex_t	*simulation;

	if (!allocate_philo_vars(&simulation_state, &simulation_start, &simulation))
		return (0);
	if (!init_mutexes(forks, simulation, n))
	{
		free(simulation_state);
		free(simulation_start);
		free(simulation);
		return (0);
	}
	i = 0;
	while (i < n - 1)
	{
		assign_philo_forks(&philos[i], &forks[i], &forks[i + 1]);
		assign_philo_vars(&philos[i], simulation_state, simulation_start, simulation);
		philos[i].params = args;
		philos[i].id = i + 1;
		i++;
	}
	assign_philo_forks(&philos[i], &forks[i], &forks[0]);
	assign_philo_vars(&philos[i], simulation_state, simulation_start, simulation);
	philos[i].id = i + 1;
	philos[i].params = args;
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

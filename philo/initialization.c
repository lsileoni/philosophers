/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:27:39 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/16 19:28:04 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	size_t	i;

	if (!init_mutexes(forks, n))
		return (0);
	i = 0;
	while (i < n - 1)
	{
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[i + 1];
		philos[i].state = P_UNINITIALIZED;
		ft_printf("i: %d\n", i);
		ft_printf("philos[%d]->state: %d\n", i, philos[i].state);
		i++;
	}
	philos[i].left_fork = (&forks)[i];
	philos[i].right_fork = (&forks)[0];
	philos[i].state = P_UNINITIALIZED;
	return (1);
}

int	init_philos(t_philo **philos, const t_args *args)
{
	pthread_mutex_t *forks;

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

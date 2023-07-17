/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignments.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@gmail.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:47:57 by lsileoni          #+#    #+#             */
/*   Updated: 2023/07/17 16:12:31 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	free_vars(void *one, void *two, void *three)
{
	free(one);
	free(two);
	free(three);
	return (0);
}

static void	assign_philo_forks(t_philo *philo, pthread_mutex_t *left_fork,
							pthread_mutex_t *right_fork)
{
	philo->left_fork = left_fork;
	philo->right_fork = right_fork;
}

static void	assign_philo_vars(t_philo *philo, size_t *simulation_state,
							size_t *simulation_start,
							pthread_mutex_t *simulation)
{
	philo->state = P_UNINITIALIZED;
	philo->simulation = simulation;
	philo->simulation_state = simulation_state;
	philo->simulation_start = simulation_start;
	philo->time_since_eating = 0;
}

int	assign_forks(pthread_mutex_t *forks, t_philo *philos,
						t_args args, size_t n)
{
	size_t			i;
	size_t			*simulation_state;
	size_t			*simulation_start;
	pthread_mutex_t	*simulation;

	if (!allocate_philo_vars(&simulation_state, &simulation_start, &simulation))
		return (0);
	if (!init_mutexes(forks, simulation, n))
		return (free_vars(simulation_state, simulation_start, simulation));
	i = 0;
	while (i < n - 1)
	{
		assign_philo_forks(&philos[i], &forks[i], &forks[i + 1]);
		assign_philo_vars(&philos[i], simulation_state,
			simulation_start, simulation);
		philos[i].params = args;
		philos[i].id = i + 1;
		i++;
	}
	assign_philo_forks(&philos[i], &forks[i], &forks[0]);
	assign_philo_vars(&philos[i], simulation_state,
		simulation_start, simulation);
	philos[i].id = i + 1;
	philos[i].params = args;
	return (1);
}

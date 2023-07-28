/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignments.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:39:04 by lsileoni          #+#    #+#             */
/*   Updated: 2023/07/28 22:39:05 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_philo_vars(t_philo *philo, t_sim_vars *vars, t_mux_pair *left_fork, t_mux_pair *right_fork)
{
	philo->left_fork = left_fork;
	philo->right_fork = right_fork;
	philo->state = P_UNINITIALIZED;
	philo->time_since_eating = 0;
	philo->times_eaten = 0;
	philo->vars = vars;
}

static int	init_mutexes(t_mux_pair *forks,
			pthread_mutex_t *simulation, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&(forks[i].mux), NULL) != 0)
		{
			destroy_forks(forks, i);
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(simulation, NULL) != 0)
	{
		destroy_forks(forks, i - 1);
		return (0);
	}
	return (1);
}

int	assign_forks(t_mux_pair *forks, t_philo *philos,
						t_args args, t_sim_vars *vars)
{
	size_t	i;

	if (!init_mutexes(forks, vars->simulation, args.philo_count))
		return (0);
	i = 0;
	while (i < args.philo_count - 1)
	{
		assign_philo_vars(&philos[i], vars,
			&forks[i], &forks[i + 1]);
		philos[i].params = args;
		philos[i].id = i + 1;
		i++;
	}
	assign_philo_vars(&philos[i], vars,
		&forks[i], &forks[0]);
	philos[i].id = i + 1;
	philos[i].params = args;
	return (1);
}

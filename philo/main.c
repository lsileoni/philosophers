/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:24:01 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/01 07:30:43 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads(t_philo *philos, t_args args, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < (int)args.philo_count)
	{
		if (pthread_create(&threads[i], NULL,
				philosopher_thread, &philos[i]) != 0)
		{
			*(philos[0].vars->simulation_state) = S_FAILURE;
			(void)pthread_mutex_unlock(philos[0].vars->simulation);
			while (--i > -1)
				(void)pthread_detach(threads[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	begin_simulation(t_philo *philos, t_args args)
{
	pthread_t	threads[MAX_THREAD];
	size_t		i;

	if (pthread_mutex_lock(philos[0].vars->simulation) != 0)
		return (0);
	if (!create_threads(philos, args, threads))
		return (0);
	*(philos[0].vars->simulation_state) = S_STARTED;
	*(philos[0].vars->simulation_start) = get_current_ms();
	(void)pthread_mutex_unlock(philos[0].vars->simulation);
	i = 0;
	while (i < args.philo_count)
	{
		(void)pthread_join(threads[i], NULL);
		i++;
	}
	return (1);
}

static int	init_simulation(const t_args args, size_t *sim_state,
		size_t *sim_start)
{
	static t_philo			philos[MAX_THREAD];
	static t_mux_pair		forks[MAX_THREAD];
	static pthread_mutex_t	simulation;
	static t_sim_vars		vars = {&simulation, 0, 0};

	vars.simulation_state = sim_state;
	vars.simulation_start = sim_start;
	if (!assign_forks(forks, philos, args, &vars))
		return (0);
	if (!begin_simulation(philos, args))
	{
		destroy_forks(forks, args.philo_count);
		(void)pthread_mutex_destroy(&simulation);
		return (0);
	}
	destroy_forks(forks, args.philo_count);
	(void)pthread_mutex_destroy(&simulation);
	return (1);
}

int	main(int argc, char **argv)
{
	const t_args	args = parse_args(argc, argv);
	size_t			simulation_state;
	size_t			simulation_start;

	if (!args.set)
		return (printf("Issue in parsing arguments!\n"));
	if (!init_simulation(args, &simulation_state, &simulation_start))
		return (printf("Issue in initializing simulation!\n"));
	return (0);
}

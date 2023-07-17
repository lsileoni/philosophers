/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:24:01 by lsileoni          #+#    #+#             */
/*   Updated: 2023/07/17 15:41:08 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_forks(pthread_mutex_t *forks, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		(void)pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

static void	philo_cleanup(t_philo *philos)
{
	(void)pthread_mutex_destroy(philos->simulation);
	(void)destroy_forks(philos[0].left_fork, philos[0].params.philo_count);
	free(philos[0].simulation);
	free(philos[0].simulation_state);
	free(philos[0].simulation_start);
	free(philos[0].left_fork);
	free(&philos[0]);
	exit (0);
}

static void	create_threads(t_philo *philos, t_args args, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < (int)args.philo_count)
	{
		if (pthread_create(&threads[i], NULL,
				philosopher_thread, &philos[i]) != 0)
		{
			while (--i >= 0)
				(void)pthread_detach(threads[i]);
			philo_cleanup(philos);
		}
		i++;
	}
}

static int	begin_simulation(t_philo *philos, t_args args)
{
	size_t		i;
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * args.philo_count);
	if (!threads)
		philo_cleanup(philos);
	if (pthread_mutex_lock(philos[0].simulation) != 0)
		philo_cleanup(philos);
	create_threads(philos, args, threads);
	*(philos[0].simulation_state) = S_STARTED;
	*(philos[0].simulation_start) = get_current_ms();
	(void)pthread_mutex_unlock(philos[0].simulation);
	i = 0;
	while (i < args.philo_count)
	{
		(void)pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
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
	if (!begin_simulation(philos, args))
		return (printf("Issue in beginning the simulation!\n"));
	philo_cleanup(philos);
	return (0);
}

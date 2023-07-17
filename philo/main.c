/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:24:01 by lsileoni          #+#    #+#             */
/*   Updated: 2023/07/17 11:52:53 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_philo *philos, t_args args, pthread_t *threads)
{
	size_t	i;

	i = 0;
	while (i < args.philo_count)
	{
		if (pthread_create(&threads[i], NULL,
				philosopher_thread, &philos[i]) != 0)
		{
			while (--i >= 0)
				pthread_detach(threads[i]);
			philo_exit(philos);
		}
		i++;
	}
}

int	begin_simulation(t_philo *philos, t_args args)
{
	size_t		i;
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * args.philo_count);
	if (!threads)
		philo_exit(philos);
	pthread_mutex_lock(philos[0].simulation);
	create_threads(philos, args, threads);
	*(philos[0].simulation_state) = S_STARTED;
	*(philos[0].simulation_start) = get_current_ms();
	(void)pthread_mutex_unlock(philos[0].simulation);
	i = 0;
	while (i < args.philo_count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
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
	return (0);
}

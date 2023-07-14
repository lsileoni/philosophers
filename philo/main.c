/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:24:01 by lsileoni          #+#    #+#             */
/*   Updated: 2023/07/14 07:00:48 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stddef.h>
#include <errno.h>
#include <sys/_pthread/_pthread_t.h>
#include <time.h>
#include <stdio.h>
#include <sys/time.h>

int	unlock_forks(t_philo *philos, size_t philo_count)
{
	size_t	i;
	int		rval;

	i = 0;
	while (i < philo_count - 1)
	{
		rval = pthread_mutex_unlock(philos[i].left_fork);
		if (rval != 0)
			return (0);
		rval = pthread_mutex_unlock(philos[i].right_fork);
		if (rval != 0)
			return (0);
		i++;
	}
	return (1);
}

size_t	philo_get_timestamp(t_philo *philo)
{
	return (get_current_ms() - *(philo->simulation_start));
}

int	try_print(t_philo *philo, const char *message)
{
	printf("philo %d 1Locking %p\n", philo->id, philo->simulation);
	if (pthread_mutex_lock(philo->simulation) != 0)
	{
		printf("BAD\n");
		return (0);
	}
	else
	{
		if (*(philo->simulation_state) == S_DONE)
		{
			printf("philo %d 1Unlocking %p\n", philo->id, philo->simulation);
			pthread_mutex_unlock(philo->simulation);
			return (0);
		}
		printf("%zu %d %s\n", philo_get_timestamp(philo), philo->id, message);
		printf("philo %d 1Unlocking %p\n", philo->id, philo->simulation);
		pthread_mutex_unlock(philo->simulation);
	}
	return (1);
}

void	try_lock(t_philo *philo)
{
	printf("philo %d 2Locking %p\n", philo->id, philo->simulation);
	if (pthread_mutex_lock(philo->simulation) != 0)
	{
		printf("BAD\n");
		return ;
	}
	else
	{
		if (*(philo->simulation_state) == S_DONE)
		{
			printf("philo %d 2Unlocking %p\n", philo->id, philo->simulation);
			pthread_mutex_unlock(philo->simulation);
			return ;
		}
		*(philo->simulation_state) = S_DONE;
		philo->state = P_DEAD;
		printf("%zu %d %s\n", philo_get_timestamp(philo), philo->id, "died");
		printf("philo %d 2Unlocking %p\n", philo->id, philo->simulation);
		pthread_mutex_unlock(philo->simulation);
	}
}

int	philo_check_death(t_philo *philo)
{
	if ((get_current_ms() - philo->time_since_eating) >= philo->params.ttd)
	{
		philo->state = P_DEAD;
		return (1);
	}
	return (0);
}

int	try_thinking(t_philo *philo)
{
	if (!try_print(philo, "is thinking"))
		return (0);
	if (philo->id % 2)
	{
		printf("philo %d 3Locking %p\n", philo->id, philo->left_fork);
		if (pthread_mutex_lock(philo->left_fork) != 0)
		{
			printf("BAD\n");
			return (0);
		}
		if (try_print(philo, "has taken a fork") <= 0)
		{
			printf("philo %d 3Unlocking %p\n", philo->id, philo->left_fork);
			pthread_mutex_unlock(philo->left_fork);
			return (0);
		}
		if (philo_check_death(philo))
		{
			try_lock(philo);
			printf("philo %d 3Unlocking %p\n", philo->id, philo->left_fork);
			pthread_mutex_unlock(philo->left_fork);
			return (0);
		}
		printf("philo %d 4Locking %p\n", philo->id, philo->right_fork);
		if (pthread_mutex_lock(philo->right_fork) != 0)
		{
			printf("BAD\n");
			printf("philo %d 3Unlocking %p\n", philo->id, philo->left_fork);
			pthread_mutex_unlock(philo->left_fork);
			return (0);
		}
		if (try_print(philo, "has taken a fork") <= 0)
		{
			printf("philo %d 3Unlocking %p\n", philo->id, philo->right_fork);
			pthread_mutex_unlock(philo->right_fork);
			printf("philo %d 3Unlocking %p\n", philo->id, philo->left_fork);
			pthread_mutex_unlock(philo->left_fork);
			return (0);
		}
	}
	else
	{
		printf("philo %d 5Locking %p\n", philo->id, philo->right_fork);
		if (pthread_mutex_lock(philo->right_fork) != 0)
		{
			printf("BAD\n");
			return (0);
		}
		if (try_print(philo, "has taken a fork") <= 0)
		{
			printf("philo %d 3Unlocking %p\n", philo->id, philo->right_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
		if (philo_check_death(philo))
		{
			try_lock(philo);
			printf("philo %d 3Unlocking %p\n", philo->id, philo->right_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
		printf("philo %d 6Locking %p\n", philo->id, philo->left_fork);
		if (pthread_mutex_lock(philo->left_fork) != 0)
		{
			printf("BAD\n");
			printf("philo %d 3Unlocking %p\n", philo->id, philo->right_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
		if (try_print(philo, "has taken a fork") <= 0)
		{
			printf("philo %d 3Unlocking %p\n", philo->id, philo->right_fork);
			pthread_mutex_unlock(philo->right_fork);
			printf("philo %d 3Unlocking %p\n", philo->id, philo->left_fork);
			pthread_mutex_unlock(philo->left_fork);
			return (0);
		}
	}
	philo->state = P_EATING;
	return (1);
}

int	try_eating(t_philo *philo)
{
	if (try_print(philo, "is eating") <= 0)
	{
		printf("philo %d 4Unlocking %p\n", philo->id, philo->right_fork);
		pthread_mutex_unlock(philo->right_fork);
		printf("philo %d 4Unlocking %p\n", philo->id, philo->left_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	if (philo_check_death(philo))
	{
		try_lock(philo);
		printf("philo %d 4Unlocking %p\n", philo->id, philo->right_fork);
		pthread_mutex_unlock(philo->right_fork);
		printf("philo %d 4Unlocking %p\n", philo->id, philo->left_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	philo->time_since_eating = get_current_ms();
	synchronized_sleep(philo->params.tte);
	printf("philo %d 4Unlocking %p\n", philo->id, philo->left_fork);
	pthread_mutex_unlock(philo->left_fork);
	printf("philo %d 4Unlocking %p\n", philo->id, philo->right_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->times_eaten++;
	philo->state = P_SLEEPING;
	return (1);
}

int	try_sleeping(t_philo *philo)
{
	if (try_print(philo, "is sleeping") <= 0)
		return (0);
	synchronized_sleep(philo->params.tts);
	philo->state = P_THINKING;
	return (1);
}

void	*philosopher_simulation(void *arg)
{
	t_philo			*philo;
	unsigned char	first_iter;

	philo = arg;
	first_iter = 0;
	if (pthread_mutex_lock(philo->simulation) != 0)
	{
		printf("BAD\n");
		return (0);
	}
	else
		pthread_mutex_unlock(philo->simulation);
	if (philo->id % 2)
		synchronized_sleep(5);
	if (philo->params.philo_count == 1)
	{
		try_print(philo, "is thinking");
		try_print(philo, "has taken a fork");
		synchronized_sleep(philo->params.ttd);
		try_print(philo, "died");
		philo->state = P_DEAD;
		return (NULL);
	}
	philo->time_since_eating = get_current_ms();
	while (philo->state != P_DONE)
	{
		if (philo->state == P_THINKING)
		{
			if (philo->params.philo_count % 2 && first_iter)
				synchronized_sleep(philo->params.tte - 10);
			if (!try_thinking(philo))
				return (NULL);
			if (!try_eating(philo))
				return (NULL);
			if (philo->params.eating_times != 0 && philo->times_eaten >= philo->params.eating_times)
			{
				philo->state = P_DONE;
				return (NULL);
			}
			if (!try_sleeping(philo))
				return (NULL);
			first_iter = 1;
		}
	}
	return (NULL);
}

void	philo_exit(t_philo *philos)
{
	pthread_mutex_destroy(philos->simulation);
	exit (0);
}

int	begin_simulation(t_philo *philos, t_args args)
{
	size_t			i;
	size_t			philos_done;
	pthread_t		*threads;

	threads = malloc(sizeof(pthread_t) * args.philo_count);
	if (!threads)
	{
		philo_exit(philos);
	}
	pthread_mutex_lock(philos[0].simulation);
	i = 0;
	while (i < args.philo_count)
	{
		pthread_create(&threads[i], NULL, philosopher_simulation, &philos[i]);
		i++;
	}
	*(philos[0].simulation_state) = S_STARTED;
	*(philos[0].simulation_start) = get_current_ms();
	pthread_mutex_unlock(philos[0].simulation);
	printf("SIMULATION START\n");
	i = 0;
	while (i < args.philo_count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	while (1)
	{
		pthread_mutex_lock(philos[0].simulation);
		if (*(philos[0].simulation_state) == S_DONE)
			break ;
		pthread_mutex_unlock(philos[0].simulation);
		philos_done = 0;
		i = 0;
		while (i < args.philo_count)
		{
			if (philos[i].state == P_DONE)
				philos_done++;
			i++;
		}
		if (philos_done == args.philo_count)
		{
			if (pthread_mutex_lock(philos[0].simulation) != 0)
			{
				printf("BAD\n");
				break ;
			}
			else
			{
				*(philos[0].simulation_state) = S_DONE;
				pthread_mutex_unlock(philos[0].simulation);
			}
		}
	}
	printf("Done looping\n");
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
	if (!unlock_forks(philos, args.philo_count))
		return (printf("Issue in locking forks!\n"));
	if (!begin_simulation(philos, args))
		return (printf("Issue in beginning the simulation!\n"));
	return (0);
}

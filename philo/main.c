/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:24:01 by lsileoni          #+#    #+#             */
/*   Updated: 2023/07/03 20:11:59 by lsileoni         ###   ########.fr       */
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

void	sleep_one_ms(void)
{
	size_t	i;

	i = 0;
	while (i < 10)
	{
		usleep(100);
		i++;
	}
}

void	sleep_n_ms(size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		sleep_one_ms();
		i++;
	}
}

size_t	assign_bound(unsigned int state, t_args args)
{
	if (state == P_THINKING)
		return (args.ttd);
	if (state == P_SLEEPING)
		return (args.tts);
	if (state == P_EATING)
		return (args.tte);
	return (0);
}


void	*philosopher_simulation(void *arg)
{
	t_philo			*philo;
	// int				contested;
	struct timeval	current_time;
	struct timeval	new_time;

	// contested = 1;
	philo = arg;
	// printf("philo addr: %p\n", philo);
	// printf("philo id: %d\n", philo->id);
	// printf("philo[%d]->left_fork = %p\n", philo->id, philo->left_fork);
	// printf("philo[%d]->right_fork = %p\n", philo->id, philo->right_fork);
	// printf("philo[%d]->simulation = %p\n", philo->id, philo->simulation);
	// printf("philo[%d]->print = %p\n", philo->id, philo->print);
	// pthread_mutex_t	*left_fork;
	// pthread_mutex_t	*right_fork;
	// pthread_mutex_t	*simulation;
	// pthread_mutex_t	*print;
	// return (NULL);
	if (philo->id % 2 != 0)
		usleep(500);
	// sleep_n_ms(philo->id);
	while (1)
	{
		if (philo->state == P_UNINITIALIZED)
		{
			printf("%d THINKING\n", philo->id);
			philo->state = P_THINKING;
			philo->ms_state = 0;
		}
		if (philo->state == P_THINKING)
		{
			gettimeofday(&current_time, NULL);
			if (pthread_mutex_lock(philo->left_fork) != 0)
				return (NULL);
			gettimeofday(&new_time, NULL);
			philo->ms_state += (new_time.tv_usec - current_time.tv_usec) / 1000;
			printf("DIFF IS %u\n", new_time.tv_usec - current_time.tv_usec);
			if (philo->ms_state >= philo->params.ttd)
			{
				printf("%d DIED, TOOK TOO LONG TO TAKE LEFT FORK\n", philo->id);
				pthread_mutex_unlock(philo->left_fork);
				philo->state = P_DEAD;
				return (NULL);
			}
			gettimeofday(&current_time, NULL);
			if (pthread_mutex_lock(philo->right_fork) != 0)
				return (NULL);
			gettimeofday(&new_time, NULL);
			printf("DIFF IS %u\n", new_time.tv_usec - current_time.tv_usec);
			philo->ms_state += (new_time.tv_usec - current_time.tv_usec) / 1000;
			if (philo->ms_state >= philo->params.ttd) {
				printf("%d DIED, TOOK TOO LONG TO TAKE RIGHT FORK\n", philo->id);
				pthread_mutex_unlock(philo->left_fork);
				pthread_mutex_unlock(philo->right_fork);
				pthread_mutex_lock(philo->simulation);
				philo->state = P_DEAD;
				return (NULL);
			}
			philo->state = P_EATING;
			printf("%d EATING\n", philo->id);
			sleep_n_ms(philo->params.tte);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			philo->state = P_SLEEPING;
			printf("%d SLEEPING\n", philo->id);
			sleep_n_ms(philo->params.tts);
			philo->state = P_THINKING;
			philo->ms_state = 0;
		}
		// if (philo->ms_state >= sleep_bound)
		// {
		// 	if (philo->state == P_THINKING)
		// 	{
		// 		printf("%d DIED\n", philo->id);
		// 		philo->state = P_DEAD;
		// 		return (NULL);
		// 	}
		// 	else if (philo->state == P_EATING)
		// 	{
		// 		pthread_mutex_unlock(philo->left_fork);
		// 		pthread_mutex_unlock(philo->right_fork);
		// 		printf("%d SLEEPING\n", philo->id);
		// 		philo->state = P_THINKING;
		// 		sleep_n_ms(philo->params.tts);
		// 		philo->ms_state += philo->params.tts;
		// 		printf("%d THINKING\n", philo->id);
		// 		sleep_bound = assign_bound(philo->state, philo->params);
		// 	}
		// }
		if (pthread_mutex_lock(philo->simulation) != 0)
		{
			printf("SIMULATION LOCK FAILED\n");
			return (NULL);
		}
		else
			pthread_mutex_unlock(philo->simulation);
	}
	return (NULL);
}

int	begin_simulation(t_philo *philos, t_args args)
{
	size_t			i;
	pthread_t		*threads;
	int				simulation_done;
	// int				sleep_check;

	threads = malloc(sizeof(pthread_t) * args.philo_count);
	i = 0;
	simulation_done = 0;
	pthread_mutex_unlock(philos[0].simulation);
	while (i < args.philo_count)
	{
		pthread_create(&threads[i], NULL, philosopher_simulation, &philos[i]);
		i++;
	}
	// sleep_check = 0;
	while (!simulation_done)
	{
		// i = 0;
		// while (i < args.philo_count)
		// {
		// 	if (sleep_check == 10)
		// 	{
		// 		philos[i].ms_state += 1;
		// 	}
		// 	i++;
		// }
		// if (sleep_check == 10)
		// 	sleep_check = 0;
		// usleep(100);
		// sleep_check += 1;
		i = 0;
		while (i < args.philo_count)
		{
			if (philos[i].state == P_DEAD)
			{
				simulation_done = 1;
				break ;
			}
			i++;
		}
	}
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
	if (!unlock_forks(philos, args.philo_count))
		return (printf("Issue in locking forks!\n"));
	if (!begin_simulation(philos, args))
		return (printf("Issue in beginning the simulation!\n"));
	return (0);
}

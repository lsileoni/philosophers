/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@gmail.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 10:14:30 by lsileoni          #+#    #+#             */
/*   Updated: 2023/07/17 11:57:59 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*simulate_one_philo(t_philo *philo)
{
	try_print(philo, "is thinking");
	try_print(philo, "has taken a fork");
	(void)synchronized_sleep(philo, philo->params.ttd);
	try_print(philo, "died");
	return (NULL);
}

void	*simulate_multiple_philos(t_philo *philo)
{
	unsigned char	first_iter;

	first_iter = 0;
	philo->time_since_eating = get_current_ms();
	while (philo->state != P_DONE)
	{
		if (philo->params.philo_count % 2 && first_iter)
			if (!synchronized_sleep(philo, philo->params.tte - 10))
				return (NULL);
		if (!try_thinking(philo))
			return (NULL);
		if (!try_eating(philo))
			return (NULL);
		if (!try_sleeping(philo))
			return (NULL);
		first_iter = 1;
	}
	return (NULL);
}

void	*philosopher_thread(void *arg)
{
	t_philo			*philo;

	philo = arg;
	if (pthread_mutex_lock(philo->simulation) != 0)
		return (0);
	else
		(void)pthread_mutex_unlock(philo->simulation);
	if (philo->id % 2)
		if (!synchronized_sleep(philo, 5))
			return (NULL);
	if (philo->params.philo_count == 1)
		return (simulate_one_philo(philo));
	return (simulate_multiple_philos(philo));
}

void	philo_exit(t_philo *philos)
{
	pthread_mutex_destroy(philos->simulation);
	exit (0);
}

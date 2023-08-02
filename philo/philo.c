/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:40:03 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/01 07:28:06 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*simulate_philo(t_philo *philo)
{
	unsigned char	first_iter;

	first_iter = 0;
	philo->time_since_eating = get_current_ms();
	while (philo->state != P_DONE)
	{
		if (!try_thinking(philo, first_iter))
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
	if (pthread_mutex_lock(philo->vars->simulation) != 0)
		return (0);
	if (*(philo->vars->simulation_state) == S_FAILURE)
	{
		(void)pthread_mutex_unlock(philo->vars->simulation);
		return (NULL);
	}
	(void)pthread_mutex_unlock(philo->vars->simulation);
	if (!(philo->params.philo_count % 2) && philo->id % 2)
		if (!synchronized_sleep(philo, 5))
			return (NULL);
	return (simulate_philo(philo));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@gmail.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 10:02:40 by lsileoni          #+#    #+#             */
/*   Updated: 2023/07/14 10:12:16 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	odd_forks(t_philo *philo)
{
	if (pthread_mutex_lock(philo->left_fork) != 0)
		return (0);
	if (try_print(philo, "has taken a fork") <= 0)
	{
		(void)pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	if (philo_check_death(philo))
	{
		try_lock(philo);
		(void)pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	if (pthread_mutex_lock(philo->right_fork) != 0)
	{
		(void)pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	if (try_print(philo, "has taken a fork") <= 0)
	{
		(void)pthread_mutex_unlock(philo->right_fork);
		(void)pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	return (1);
}

int	even_forks(t_philo *philo)
{
	if (pthread_mutex_lock(philo->right_fork) != 0)
		return (0);
	if (try_print(philo, "has taken a fork") <= 0)
	{
		(void)pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	if (philo_check_death(philo))
	{
		try_lock(philo);
		(void)pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	if (pthread_mutex_lock(philo->left_fork) != 0)
	{
		(void)pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	if (try_print(philo, "has taken a fork") <= 0)
	{
		(void)pthread_mutex_unlock(philo->right_fork);
		(void)pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	return (1);
}

int	try_thinking(t_philo *philo)
{
	if (!try_print(philo, "is thinking"))
		return (0);
	if (philo->id % 2)
	{
		if (!odd_forks(philo))
			return (0);
	}
	else
	{
		if (!even_forks(philo))
			return (0);
	}
	philo->state = P_EATING;
	return (1);
}

int	try_eating(t_philo *philo)
{
	if (try_print(philo, "is eating") <= 0)
	{
		(void)pthread_mutex_unlock(philo->right_fork);
		(void)pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	if (philo_check_death(philo))
	{
		try_lock(philo);
		(void)pthread_mutex_unlock(philo->right_fork);
		(void)pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	philo->time_since_eating = get_current_ms();
	synchronized_sleep(philo->params.tte);
	(void)pthread_mutex_unlock(philo->left_fork);
	(void)pthread_mutex_unlock(philo->right_fork);
	philo->times_eaten++;
	if (philo->params.eating_times != 0 && philo->times_eaten >= philo->params.eating_times)
	{
		philo->state = P_DONE;
		return (0);
	}
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

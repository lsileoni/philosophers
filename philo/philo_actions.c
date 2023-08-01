/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:40:21 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/01 07:18:10 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	odd_forks(t_philo *philo)
{
	if (!take_fork(philo->left_fork, philo))
		return (0);
	if (!try_print(philo, "has taken a fork"))
	{
		put_fork_down(philo->left_fork);
		return (0);
	}
	if (!take_fork(philo->right_fork, philo))
	{
		put_fork_down(philo->left_fork);
		return (0);
	}
	if (!try_print(philo, "has taken a fork"))
	{
		put_fork_down(philo->left_fork);
		put_fork_down(philo->right_fork);
		return (0);
	}
	return (1);
}

static int	even_forks(t_philo *philo)
{
	if (!take_fork(philo->right_fork, philo))
		return (0);
	if (!try_print(philo, "has taken a fork"))
	{
		put_fork_down(philo->right_fork);
		return (0);
	}
	if (!take_fork(philo->left_fork, philo))
	{
		put_fork_down(philo->right_fork);
		return (0);
	}
	if (!try_print(philo, "has taken a fork"))
	{
		put_fork_down(philo->right_fork);
		put_fork_down(philo->left_fork);
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
	return (1);
}

int	try_eating(t_philo *philo)
{
	if (!try_print(philo, "is eating"))
	{
		put_fork_down(philo->right_fork);
		put_fork_down(philo->left_fork);
		return (0);
	}
	if (philo_check_death(philo))
	{
		try_lock(philo);
		put_fork_down(philo->right_fork);
		put_fork_down(philo->left_fork);
		return (0);
	}
	philo->time_since_eating = get_current_ms();
	if (!synchronized_sleep(philo, philo->params.tte))
	{
		put_fork_down(philo->right_fork);
		put_fork_down(philo->left_fork);
		return (0);
	}
	put_fork_down(philo->right_fork);
	put_fork_down(philo->left_fork);
	if (!philo_check_eating_times(philo))
		return (0);
	return (1);
}

int	try_sleeping(t_philo *philo)
{
	if (!try_print(philo, "is sleeping"))
		return (0);
	if (!synchronized_sleep(philo, philo->params.tts))
		return (0);
	return (1);
}

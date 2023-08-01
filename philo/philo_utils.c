/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:40:28 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/01 06:23:51 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	try_print(t_philo *philo, const char *message)
{
	if (pthread_mutex_lock(philo->vars->simulation) != 0)
		return (0);
	if (*(philo->vars->simulation_state) == S_DONE)
	{
		(void)pthread_mutex_unlock(philo->vars->simulation);
		return (0);
	}
	(void)printf("%zu %d %s\n", philo_get_timestamp(philo),
		philo->id, message);
	(void)pthread_mutex_unlock(philo->vars->simulation);
	return (1);
}

void	try_lock(t_philo *philo)
{
	if (pthread_mutex_lock(philo->vars->simulation) != 0)
		return ;
	if (*(philo->vars->simulation_state) == S_DONE)
	{
		(void)pthread_mutex_unlock(philo->vars->simulation);
		return ;
	}
	*(philo->vars->simulation_state) = S_DONE;
	(void)printf("%zu %d %s\n", philo_get_timestamp(philo),
		philo->id, "died");
	(void)pthread_mutex_unlock(philo->vars->simulation);
}

int	take_fork(t_mux_pair *fork, t_philo *philo)
{
	while (1)
	{
		if (philo_check_death(philo))
		{
			try_lock(philo);
			return (0);
		}
		if (pthread_mutex_lock(&fork->mux) != 0)
			return (0);
		if (fork->val == 0)
		{
			fork->val = 1;
			(void)pthread_mutex_unlock(&fork->mux);
			break ;
		}
		(void)pthread_mutex_unlock(&fork->mux);
		(void)usleep(300);
	}
	return (1);
}

int	put_fork_down(t_mux_pair *fork)
{
	if (pthread_mutex_lock(&fork->mux) != 0)
		return (0);
	fork->val = 0;
	(void)pthread_mutex_unlock(&fork->mux);
	return (1);
}

void	destroy_forks(t_mux_pair *forks, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		(void)pthread_mutex_destroy(&(forks[i].mux));
		i++;
	}
}

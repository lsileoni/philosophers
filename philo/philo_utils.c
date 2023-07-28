/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:40:28 by lsileoni          #+#    #+#             */
/*   Updated: 2023/07/28 22:40:29 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	philo_get_timestamp(t_philo *philo)
{
	return (get_current_ms() - *(philo->vars->simulation_start));
}

int	try_print(t_philo *philo, const char *message)
{
	if (pthread_mutex_lock(philo->vars->simulation) != 0)
		return (0);
	else
	{
		if (*(philo->vars->simulation_state) == S_DONE)
		{
			(void)pthread_mutex_unlock(philo->vars->simulation);
			return (0);
		}
		(void)printf("%zu %d %s\n", philo_get_timestamp(philo),
			philo->id, message);
		(void)pthread_mutex_unlock(philo->vars->simulation);
	}
	return (1);
}

void	try_lock(t_philo *philo)
{
	if (pthread_mutex_lock(philo->vars->simulation) != 0)
		return ;
	else
	{
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
}

int	philo_check_eating_times(t_philo *philo)
{
	philo->times_eaten++;
	if (philo->params.eating_times != 0 && \
		philo->times_eaten >= philo->params.eating_times)
	{
		philo->state = P_DONE;
		return (0);
	}
	return (1);
}

int	philo_check_death(t_philo *philo)
{
	if (philo->time_since_eating != 0 && \
		(get_current_ms() - philo->time_since_eating) >= philo->params.ttd)
		return (1);
	return (0);
}

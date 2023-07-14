/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@gmail.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:20:15 by lsileoni          #+#    #+#             */
/*   Updated: 2023/07/14 09:21:23 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	philo_get_timestamp(t_philo *philo)
{
	return (get_current_ms() - *(philo->simulation_start));
}

int	try_print(t_philo *philo, const char *message)
{
	
	if (pthread_mutex_lock(philo->simulation) != 0)
		return (0);
	else
	{
		if (*(philo->simulation_state) == S_DONE)
		{
			(void)pthread_mutex_unlock(philo->simulation);
			return (0);
		}
		(void)printf("%zu %d %s\n", philo_get_timestamp(philo), philo->id, message);
		(void)pthread_mutex_unlock(philo->simulation);
	}
	return (1);
}

void	try_lock(t_philo *philo)
{
	if (pthread_mutex_lock(philo->simulation) != 0)
		return ;
	else
	{
		if (*(philo->simulation_state) == S_DONE)
		{
			(void)pthread_mutex_unlock(philo->simulation);
			return ;
		}
		*(philo->simulation_state) = S_DONE;
		philo->state = P_DEAD;
		(void)printf("%zu %d %s\n", philo_get_timestamp(philo), philo->id, "died");
		(void)pthread_mutex_unlock(philo->simulation);
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

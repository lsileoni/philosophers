/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 06:06:41 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/01 06:07:35 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	philo_get_timestamp(t_philo *philo)
{
	return (get_current_ms() - *(philo->vars->simulation_start));
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

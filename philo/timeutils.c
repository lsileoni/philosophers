/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:40:51 by lsileoni          #+#    #+#             */
/*   Updated: 2023/07/28 22:40:52 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_ms(void)
{
	struct timeval	val;

	(void)gettimeofday(&val, NULL);
	return ((val.tv_sec * 1000) + (val.tv_usec / 1000));
}

int	synchronized_sleep(t_philo *philo, size_t n_ms)
{
	size_t	start_ms;
	size_t	end_ms;

	if (!n_ms)
		return (1);
	start_ms = get_current_ms();
	end_ms = get_current_ms();
	while ((end_ms - start_ms) < n_ms)
	{
		if (philo_check_death(philo))
		{
			try_lock(philo);
			return (0);
		}
		if (*(philo->vars->simulation_state) == S_DONE)
			return (0);
		(void)usleep(250);
		end_ms = get_current_ms();
	}
	return (1);
}

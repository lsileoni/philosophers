/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@gmail.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:18:56 by lsileoni          #+#    #+#             */
/*   Updated: 2023/07/14 02:55:57 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/time.h>
#include <unistd.h>


size_t	get_current_ms(void)
{
	struct timeval val;

	gettimeofday(&val, NULL);
	return ((val.tv_sec * 1000) + (val.tv_usec / 1000));
}

void	synchronized_sleep(size_t n_ms)
{
	size_t	start_ms;
	size_t	end_ms;

	start_ms = get_current_ms();
	end_ms = get_current_ms();
	while ((end_ms - start_ms) < n_ms)
	{
		usleep(250);
		end_ms = get_current_ms();
	}
}

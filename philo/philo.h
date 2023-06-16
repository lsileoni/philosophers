/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:14:28 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/16 19:31:43 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "libft.h"
# include <pthread.h>
# include <stddef.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

enum e_state
{
	P_DEAD,
	P_THINKING,
	P_DONE,
	P_EATING,
	P_SLEEPING,
	P_UNINITIALIZED
};

typedef struct s_args
{
	size_t	philo_count;
	size_t	ttd;
	size_t	tte;
	size_t	tts;
	size_t	eating_times;
	size_t	set;
}	t_args;

typedef struct s_philo
{
	t_args			params;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	unsigned int	ms_state;
	unsigned char	times_eaten;
	unsigned char	state;
}	t_philo;

t_args	parse_args(int argc, char **argv);
int		init_philos(t_philo **philos, const t_args *args);

#endif

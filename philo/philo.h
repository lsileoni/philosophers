/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:14:28 by lsileoni          #+#    #+#             */
/*   Updated: 2023/07/13 02:05:37 by lsileoni         ###   ########.fr       */
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

enum e_philo_state
{
	P_DEAD,
	P_THINKING,
	P_DONE,
	P_EATING,
	P_SLEEPING,
	P_UNINITIALIZED
};

enum e_sim_state
{
	S_UNINITIALIZED,
	S_STARTED,
	S_DONE
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
	pthread_mutex_t	*simulation;
	pthread_mutex_t	*print;
	size_t			*timestamp;
	size_t			*simulation_state;
	unsigned int	id;
	unsigned int	ms_state;
	unsigned int	times_eaten;
	unsigned char	state;
	unsigned char	record;
	unsigned char	eating_flag;
}	t_philo;

t_args	parse_args(int argc, char **argv);
int		init_philos(t_philo **philos, const t_args args);

#endif

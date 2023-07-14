/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:14:28 by lsileoni          #+#    #+#             */
/*   Updated: 2023/07/14 04:04:31 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stddef.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

enum e_philo_state
{
	P_DEAD,
	P_THINKING,
	P_DONE,
	P_EATING,
	P_SLEEPING
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
	size_t			*simulation_state;
	size_t			*simulation_start;
	size_t			time_since_eating;
	unsigned int	id;
	unsigned int	times_eaten;
	unsigned char	state;
}	t_philo;

t_args	parse_args(int argc, char **argv);
int		init_philos(t_philo **philos, const t_args args);
size_t	get_current_ms(void);
void	synchronized_sleep(size_t n_ms);
void	ft_bzero(void *s, size_t n);
int		ft_atoi(const char *str);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:14:28 by lsileoni          #+#    #+#             */
/*   Updated: 2023/07/17 16:01:13 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# define MAX_THREAD 512

enum e_philo_state
{
	P_UNINITIALIZED,
	P_DONE
};

enum e_sim_state
{
	S_UNINITIALIZED,
	S_STARTED,
	S_DONE
};

typedef struct s_args
{
	size_t			philo_count;
	size_t			ttd;
	size_t			tte;
	size_t			tts;
	size_t			eating_times;
	unsigned char	set;
	unsigned char	eating_set;
}					t_args;

typedef struct s_philo
{
	t_args			params;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*simulation;
	size_t			*simulation_state;
	size_t			*simulation_start;
	size_t			time_since_eating;
	unsigned int	id;
	unsigned int	times_eaten;
	unsigned char	state;
}					t_philo;

t_args	parse_args(int argc, char **argv);
int		init_philos(t_philo **philos, const t_args args);
size_t	get_current_ms(void);
int		synchronized_sleep(t_philo *philo, size_t n_ms);
void	ft_bzero(void *s, size_t n);
int		ft_atoi(const char *str);
size_t	philo_get_timestamp(t_philo *philo);
int		try_print(t_philo *philo, const char *message);
void	try_lock(t_philo *philo);
int		philo_check_death(t_philo *philo);
int		try_thinking(t_philo *philo);
int		try_sleeping(t_philo *philo);
int		try_eating(t_philo *philo);
void	*philosopher_thread(void *arg);
int		philo_check_eating_times(t_philo *philo);
int		assign_forks(pthread_mutex_t *forks, t_philo *philos,
			t_args args, size_t n);
int		allocate_philo_vars(size_t **simulation_state,
			size_t **simulation_start, pthread_mutex_t **simulation);
int		init_mutexes(pthread_mutex_t *forks,
			pthread_mutex_t *simulation, int n);

#endif

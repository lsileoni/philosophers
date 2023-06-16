/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:14:28 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/16 14:16:19 by lsileoni         ###   ########.fr       */
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

typedef struct s_args
{
	size_t	philo_count;
	size_t	ttd;
	size_t	tte;
	size_t	tts;
	size_t	eating_times;
	size_t	set;
}	t_args;

t_args	parse_args(int argc, char **argv);

#endif

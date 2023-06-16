/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:24:01 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/16 19:29:06 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	const t_args	args = parse_args(argc, argv);
	t_philo			*philos;
	size_t			i;

	if (!args.set)
		return (ft_printf("Issue in parsing arguments!\n"));
	if (!init_philos(&philos, &args))
		return (ft_printf("Issue in initializing philosophers!\n"));
	i = 0;
	while (i < args.philo_count)
	{
		ft_printf("philos[%d]->state: %d\n", i, philos[i].state);
		ft_printf("philos[%d]->left_fork: %p\n", i, philos[i].left_fork);
		ft_printf("philos[%d]->right_fork: %p\n", i, philos[i].right_fork);
		i++;
	}
	return (0);
}

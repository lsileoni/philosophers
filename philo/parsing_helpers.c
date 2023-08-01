/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:39:52 by lsileoni          #+#    #+#             */
/*   Updated: 2023/07/28 22:39:53 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

static int	overflow_return(int is_neg)
{
	if (is_neg)
		return (0);
	return (-1);
}

static int	integer_return(int is_neg, long long res)
{
	if (is_neg)
		return (res * -1);
	return (res);
}

void	ft_bzero(void *s, size_t n)
{
	int				i;
	unsigned char	*p;

	p = (unsigned char *)s;
	if (n)
	{
		i = 0;
		while (n--)
		{
			p[i] = 0;
			i++;
		}
	}
}

int	ft_atoi(const char *str)
{
	int			is_neg;
	long long	res;

	is_neg = 0;
	res = 0;
	if (*str)
	{
		while (is_whitespace(*str))
			str++;
		if (*str == '-' || *str == '+')
		{
			if (*str == '-')
				is_neg = 1;
			str++;
		}
		while (*str >= '0' && *str <= '9')
		{
			res = (res * 10) + (*str - '0');
			str++;
			if (res < 0)
				return (overflow_return(is_neg));
		}
		return (integer_return(is_neg, res));
	}
	return (0);
}

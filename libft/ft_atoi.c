/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 11:49:33 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/22 13:48:34 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_iterative_power(int nb, int power)
{
	int i;

	if (power == 0)
		return (1);
	else if (power < 0)
		return (0);
	else
	{
		i = nb * ft_iterative_power(nb, power - 1);
	}
	return (i);
}

static int		answer(char *num, long k, long m)
{
	int ans;
	int i;

	i = 0;
	ans = 0;
	while (k > 0)
	{
		ans = ans * 10 + (num[i] - 48);
		k--;
		i++;
	}
	if (m == -1)
		return (ans * -1);
	else
		return (ans);
}

static long		get_number(const char *str, char *num)
{
	long	k;
	int		i;

	i = 0;
	k = 0;
	while (*str >= '0' && *str <= '9')
	{
		num[i] = *str++;
		k++;
		i++;
	}
	return (k);
}

int				ft_atoi(const char *str)
{
	long		k;
	long		m;
	long		count;
	char		num[256];

	k = 0;
	m = 1;
	count = 0;
	while (*str != '\0' && (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r'))
		str++;
	while (*str != '\0' && (*str == '-' || *str == '+'))
	{
		if (*str == '+' || *str == '-')
			count++;
		if (*str++ == '-')
			m = m * -1;
	}
	if (*str == '\0' || *str < '0' || *str > '9' || count > 1)
		return (0);
	k = get_number(str, num);
	return (answer(&num[0], k, m));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 11:45:32 by yiwasa            #+#    #+#             */
/*   Updated: 2020/06/28 13:44:53 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long		get_digit(long n)
{
	long digit;

	if (n == 0)
		return (1);
	digit = 0;
	while (n > 0)
	{
		n /= 10;
		digit++;
	}
	return (digit);
}

long			ft_recursive_power(long nb, int power)
{
	if (power == 0)
		return (1);
	if (power < 0)
		return (0);
	return (nb * ft_recursive_power(nb, power - 1));
}

static char		*pattern_min(char *str, long num, long digit)
{
	int i;

	i = 0;
	if (str == 0)
		return (0);
	str[i++] = '-';
	while (i < digit + 1)
	{
		str[i] = (num / ft_recursive_power(10, digit - (i))) + '0';
		num %= ft_recursive_power(10, digit - (i));
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char		*pattern_pul(char *str, long num, long digit)
{
	int i;

	if (num == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	i = 0;
	while (i < digit)
	{
		str[i] = (num / ft_recursive_power(10, digit - (i + 1))) + '0';
		num %= ft_recursive_power(10, digit - (i + 1));
		i++;
	}
	str[i] = '\0';
	return (str);
}

char			*ft_itoa(int n)
{
	char	*str;
	long	digit;
	long	num;
	int		min;

	min = 0;
	num = n;
	if (num < 0)
	{
		num *= -1;
		min = -1;
	}
	digit = get_digit(num);
	if (min < 0)
	{
		str = malloc(digit + 2);
		return (pattern_min(str, num, digit));
	}
	else
	{
		str = malloc(digit + 1);
		return (pattern_pul(str, num, digit));
	}
}

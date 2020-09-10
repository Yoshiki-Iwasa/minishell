/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollor_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 11:05:14 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/10 11:05:21 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 文字列中の、'$'の数を数える関数
*/

int		count_dollor(char *str)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

int		count_strs(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		i++;
	}
	return (i);
}

int		is_only_or_many_dollor(char *arg)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			count++;
		}
		if (arg[i] == '$' && arg[i + 1] == '$')
			return (1);
		i++;
	}
	if (count == i)
		return (1);
	return (0);
}

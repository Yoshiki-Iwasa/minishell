/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 10:53:03 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/18 11:14:09 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ascii_sort(char **args)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (args[i])
	{
		j = i + 1;
		while (args[j])
		{
			if (ft_strcmp(args[i], args[j]) > 0)
			{
				tmp = args[i];
				args[i] = args[j];
				args[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

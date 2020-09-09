/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 11:03:05 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/09 11:04:18 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_echo(char **args)
{
	int i;

	i = 1;
	if (!ft_strcmp(args[i], "-n"))
	{
		i++;
		while (args[i] != 0)
		{
			ft_putstr_fd(args[i++], 1);
			if (args[i] != NULL)
				write(1, " ", 1);
		}
	}
	else
	{
		while (args[i] != 0)
		{
			ft_putstr_fd(args[i++], 1);
			if (args[i] != NULL)
				write(1, " ", 1);
		}
		write(1, "\n", 1);
	}
	return (0);
}

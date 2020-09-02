/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 07:23:44 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/02 08:57:11 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** コマンドラインを読んでくる関数。
 ** 読み込むたびに minishell$ を表示する。
*/

int		read_command(char **line, int *state)
{
	int gnl_rv;

	ft_putstr_fd("minishell$ ", 1);
	gnl_rv = get_next_line(0, line);
	if (**line == '\0' && gnl_rv == 1)
	{
		free(*line);
		return (0);
	}
	if (gnl_rv == 0)
	{
		free(*line);
		write(1, "exit\n", 5);
		*state = 0;
		return (0);
	}
	if (gnl_rv == -1)
	{
		write(1, "GNL Fail\n", 9);
		exit(0);
		return (0);
	}
	return (1);
}

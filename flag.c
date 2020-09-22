/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 12:30:33 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/22 12:30:56 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** フラグの初期化を行う。
*/

void			init_flags(t_flags *flag)
{
	flag->flag_in = 0;
	flag->flag_error = 0;
	flag->flag_out = 0;
}

/*
** 標準入力のflag の値を入力
*/

int				set_in_flag(char **args, t_flags *flag, int *fd, int i)
{
	if (change_stdin_fd(args[i], fd))
		flag->flag_in = 1;
	else
	{
		flag->flag_in = -1;
		return (0);
	}
	return (1);
}

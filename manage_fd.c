/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 07:26:19 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/05 17:33:52 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** 一回close された 標準入力と標準出力を元に戻している
*/

void	recover_stdinout
	(int in_out, int *stdin_fd, int *stdout_fd, int *stderror_fd)
{
	if (in_out == 0)
	{
		close(0);
		dup2(*stdin_fd, 0);
	}
	if (in_out == 1)
	{
		close(1);
		dup2(*stdout_fd, 1);
	}
	if (in_out == 2)
	{
		close(2);
		dup2(*stderror_fd, 2);
	}
	if (in_out == 3)
	{
		close(0);
		dup2(*stdin_fd, 0);
		close(1);
		dup2(*stdout_fd, 1);
	}
}

/*
 ** 標準入力と標準出力のfd を他のfd にコピーしておく。
*/

void	escape_fds(int *stdin_fd, int *stdout_fd, int *stderror_fd)
{
	*stdin_fd = dup(0);
	*stdout_fd = dup(1);
	*stderror_fd = dup(2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:12:42 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/05 14:48:00 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** フラグの初期化を行う。
*/

static void init_flags(int *flag_in, int *flag_out, int *flag_error)
{
	*flag_in = 0;
	*flag_out = 0;
	*flag_error = 0;
}

/*
 ** リダイレクトの処理をする。具体的には、fd の値を書き換えて標準入出力先を変更する。
*/
int		deal_redirection(char **args, int *fd, char **error)
{
	int i;
	int flag_in;
	int flag_out;
	int flag_error;

	init_flags(&flag_in, &flag_out, &flag_error);
	i = 0;
	while (args[i])
	{
		if(!ft_strcmp(args[i], "<"))
		{
			args[i] = NULL;
			i++;
			if(change_stdin_fd(args[i], fd))
				flag_in = 1;
			else
			{
				*error = args[i];
				flag_in = -1;
			}
		}
		else if(!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], ">|") || !ft_strcmp(args[i], "1>"))
			change_stdout_fd_set_null(args, &flag_out, fd, &i);
		else if (!ft_strcmp(args[i], ">>"))
			change_stdout_fd_set_null_append(args, &flag_out, fd, &i);
		else if (!ft_strcmp(args[i], "2>"))
			change_stderror_fd_set_null(args, &flag_error, fd, &i);
		if(args[i])
			i++;
	}
	if (flag_in > 0 && !flag_out)
		return (0);
	else if (flag_out && !flag_in)
		return (1);
	else if (flag_error && flag_in != -1)
		return (2);
	else if (flag_in == -1)
		return (-1);
	else
		return (3);
}

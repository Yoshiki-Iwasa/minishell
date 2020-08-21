/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:12:42 by yiwasa            #+#    #+#             */
/*   Updated: 2020/08/21 13:36:21 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*標準出力のリダイレクトの実装*/

void	change_stdout_fd(char *arg, int *fd)
{
	int close_rv;
	int dup2_rv;

	*fd = open(arg, O_RDWR | O_CREAT | S_IREAD | S_IWRITE);
	close_rv = close(1);
	dup2_rv = dup2(*fd, 1);
}

/*標準入力のリダイレクトの実装*/

void	change_stdin_fd(char *arg, int *fd)
{
	*fd = open(arg, O_RDWR | O_CREAT | S_IREAD | S_IWRITE);
	close(0);
	dup2(*fd, 0);
}
/*
	標準出力の追記用fd 作成
*/
void	change_stdout_fd_for_append(char *arg, int *fd)
{
	*fd = open(arg, O_RDWR | O_APPEND | O_CREAT | S_IREAD | S_IWRITE);
	close(1);
	dup2(*fd, 1);
}
/*
	リダイレクトの処理をする。具体的には、fd の値を書き換えて標準入出力先を変更する。
*/
int		deal_redirection(char **args, int *fd)
{
	int i;
	int flag_in;
	int flag_out;
	int	flag_attach;

	i = 0;
	flag_in = 0;
	flag_out = 0;
	while (args[i])
	{
		if(!ft_strcmp(args[i], "<"))
		{
			args[i] = NULL; //リダイレクト以降が出力されないようにするため
			i++;
			change_stdin_fd(args[i], fd);
			flag_in = 1;
			return (0);
		}
		else if(!ft_strcmp(args[i], ">"))
		{
			args[i] = NULL; //リダイレクト以降が出力されないようにするため
			i++;
			change_stdout_fd(args[i], fd);
			flag_out = 1;
			return (1);
		}
		else if (!ft_strcmp(args[i], ">>"))
		{
			args[i] = NULL;
			i++;
			change_stdout_fd_for_append(args[i], fd);
			return (1);
		}
		i++;
	}
	if (flag_in == 0 && flag_out == 0)
	return (3);
}

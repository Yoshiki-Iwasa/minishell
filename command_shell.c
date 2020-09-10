/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 09:14:29 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/10 14:16:36 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_pid;
int		g_count;
int		g_core_flag;

/*
** シグナルハンドラー(ctrl-C 用)
*/

void		sig_handle_c(int sig)
{
	if (g_pid != 0)
	{
		sig = kill(g_pid, SIGINT);
		if (sig == -1)
		{
			write(1, "\n", 1);
			ft_putstr_fd("minishell$ ", 1);
		}
	}
	else
	{
		write(1, "\n", 1);
		ft_putstr_fd("minishell$ ", 1);
	}
}

/*
** シグナルハンドラー ctrl-\ 用
*/

void		sig_handle_bs(int sig)
{
	if (g_pid != 0)
		sig = kill(g_pid, SIGQUIT);
	else
		sig = -1;
	if (sig == -1)
		write(1, "\b\b  \b\b", 6);
}

/*
** 終了ステータスコアダンプをだすかどうか決める関数
*/

void	put_quit_message(int status)
{
	if (WCOREDUMP(status))
		ft_putendl("Quit: (core dumped)");
	else
		ft_putendl("Quit");
}

/*
** build in 以外の関数が呼ばれたときに使う関数
*/

int			exec_shell_command
	(char **args, t_edlist *vals, char **paths, char *origin_arg)
{
	int		status;

	g_pid = fork();
	if (g_pid == 0)
	{
		if (!child_precess(args, vals, paths, origin_arg))
			exit(1);
	}
	else if (g_pid < 0)
		strerror(errno);
	else
	{
		wait(&status);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				put_quit_message(status);
			if (WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
			return (128 + WTERMSIG(status));
		}
	}
	return (WEXITSTATUS(status));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 13:27:58 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/11 08:36:33 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_ret;
int		g_sig_count;

void	signel_pipe(int sig)
{
	if (g_ret != 0)
	{
		g_sig_count++;
		sig = kill(g_ret, SIGINT);
		if (!sig && g_sig_count == 1)
		{
			write(1, "\n", 1);
		}
	}
}

void	signel_pipe_bs(int sig)
{
	if (g_ret != 0)
	{
		sig = 1;
		g_sig_count += sig;
		kill(g_ret, SIGQUIT);
	}
}

/*
** パイプでつながれたコマンドの実行を再帰的に行う関数
*/

void	exec_pipes(int i, char ***args_array, int com_num, t_edlist *vals)
{
	int status;
	int pp[2];

	if (i == com_num - 1)
		exit(no_pipe(args_array[0], vals));
	else
	{
		pipe(pp);
		g_sig_count++;
		g_ret = fork();
		if (g_ret == 0)
		{
			close_and_dup2_1(pp[0], pp[1]);
			exec_pipes(i + 1, args_array, com_num, vals);
			exit(0);
		}
		else
		{
			close_and_dup2_2(pp[0], pp[1]);
			no_pipe(args_array[com_num - i - 1], vals);
			wait(&status);
			exit(WEXITSTATUS(status));
		}
	}
}

void	update_term_status(t_edlist *vals, int status)
{
	char	*num_str;
	char	*status_str;

	num_str = ft_itoa(WEXITSTATUS(status));
	status_str = ft_strjoin("?=", num_str);
	free(num_str);
	update_val(&(vals->d_val), status_str);
	free(status_str);
}

/*
** コマンドにパイプが一個以上含まれていた場合の関数。fork して子プロセスを作り上げる。
** ここから、再帰関数を使って、コマンドの右から順に実行させる。
*/

int		yes_pipe(char **args, t_edlist *vals, int pipe_count)
{
	char	**envp;
	int		status;
	char	***args_array;

	envp = change_into_array(vals->e_val);
	args_into_array(args, &args_array, pipe_count);
	signal(SIGINT, signel_pipe);
	signal(SIGQUIT, signel_pipe_bs);
	g_sig_count = 0;
	g_ret = fork();
	if (g_ret == 0)
		exec_pipes(0, args_array, pipe_count + 1, vals);
	else
	{
		wait(&status);
		free_all(envp, 0);
		setting_signal();
		update_term_status(vals, status);
		free(args_array);
		g_sig_count = 0;
	}
	return (WEXITSTATUS(status));
}

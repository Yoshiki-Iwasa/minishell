/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 13:27:58 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/06 13:08:03 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t g_ret;
int	  g_sig_count;

void	signel_pipe(int sig)
{
	if (g_ret != 0)
	{
		g_sig_count++;
		sig = kill(g_ret, SIGINT);
		if(!sig && g_sig_count == 1)
		{
			write(1, "\n", 1);
		}
	}
}

/*
	パイプでつながれたコマンドの実行を再帰的に行う関数
*/
void	exec_pipes(int i, char ***args_array, int com_num, t_edlist *vals)
{
	int status;
	int pp[2] = {};
	if (i == com_num - 1)
		exit(no_pipe(args_array[0], vals));
	else
	{
		pipe(pp);
		g_sig_count++;
		g_ret = fork();
		if (g_ret == 0)
		{
			close(pp[0]);
			dup2(pp[1], 1);
			close(pp[1]);
			exec_pipes(i + 1, args_array, com_num, vals);
			exit(0);
		}
		else
		{
				close(pp[1]);
				dup2(pp[0], 0);
				close(pp[0]);
				no_pipe(args_array[com_num -i -1], vals);
				wait(&status);
				exit(WEXITSTATUS(status));
		}
	}
}

/*
	コマンドにパイプが一個以上含まれていた場合の関数。fork して子プロセスを作り上げる。
	ここから、再帰関数を使って、コマンドの右から順に実行させる。
*/


int		yes_pipe(char **args, t_edlist *vals, int pipe_count)
{
	char	**envp;
	int		status;
	char	***args_array; // こいつ最終的にfreeする必要あり。
	char	*num_str;
	char	*status_str;

	envp = change_into_array(vals->e_val); //環境変数リストを文字列に変換。
	args_into_array(args, &args_array, pipe_count);// ここまでで、args_array でコマンドをパイプごとに分割できた
	signal(SIGINT,signel_pipe);
	g_sig_count = 0;
	g_ret = fork();
	if (g_ret == 0)
		exec_pipes(0, args_array, pipe_count + 1, vals); //一番右のコマンドを親として、右から左にコマンドを順次実行させる。
	else
	{
		wait(&status);
		free_all(envp, 0);
		setting_signal();
		num_str = ft_itoa(WEXITSTATUS(status)); //終了ステータスを文字列としてゲット
		status_str = ft_strjoin("?=", num_str); //終了ステータスの変数の更新用に整形
		free(num_str);
		update_val(&(vals->d_val), status_str);//終了ステータス更新。
		free(status_str);
		free(args_array);
	}
	return (WEXITSTATUS(status));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 09:14:29 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/06 10:14:29 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_pid;
int		g_count;
int		g_core_flag;

/*
 ** シグナルハンドラー(ctrl-C 用)
*/

void		sig_handle_C(int sig)
{
	if (g_pid != 0)
	{
		// write(1, "\b\b^C", 4);
		sig = kill(g_pid, SIGINT);
		if(sig == -1)
		{
			write(1, "\n",1);
			ft_putstr_fd("minishell$ ", 1);
		}

	}
	else//入力途中にCtrl + C されても無視。
	{
			write(1, "\n",1);
			ft_putstr_fd("minishell$ ", 1);
	}
}

/*
** シグナルハンドラー ctrl-\ 用
*/

void		sig_handle_bs(int sig)
{
	int tmp;

	tmp = sig;
	// write(1, "\b\b  \b\b", 6);
	if (g_pid != 0)
	{
		sig = kill(g_pid, SIGQUIT);
	}
	else
	{
		sig = -1;
	}
	if (sig == -1)
	{
		signal(tmp, SIG_IGN);
	}
}

/*
	子供プロセスの実行を司る関数。与えられたコマンドと、PATHをexecve に逐一与えていく。
*/

int	child_precess(char **args, char **envp, char **paths, char *origin_arg)// args には "ls" "-la" みたいなふうにコマンドが文字列配列化して入っている。
{
	int		i;
	char	command[PATH_MAX + 1];
	char	*cmd_ptr;

	i = 0;
	while(paths[i])
	{
		if (args[0][0] == '\0')
		{
			errno = 2;
			break ;
		}
		command[0] = '\0';
		cmd_ptr = ft_strcat(command, paths[i]); //環境変数PATH を一個ずつ試す。
		cmd_ptr = ft_strcat(command, "/");
		cmd_ptr = ft_strcat(command, args[0]); //これで /user/bin/ls みたいにパスを完成させる。
		//相対パスと、絶対パスによる実行のために、コマンドの入力が スラッシュか、ピリオ土ではじまったときは、パスをpaths に追加した後、args[0]を編集する。
		execve(cmd_ptr, args, envp); //実行がうまく行けば子プロセスはここで終了。
		cmd_ptr[0] = '\0';
		i++;
	}
	if (errno == 2)
	{
		if (paths[0][0]  == '\0') //PATH がunset された時
		{
			ft_putstr_fd("bash: ",2);
			ft_putstr_fd(origin_arg, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		else
		{
			if (origin_arg[0] == '/' || !ft_strncmp(origin_arg, "./", 2))
			{
				ft_putstr_fd("bash: ",2);
				ft_putstr_fd(origin_arg, 2);
				ft_putstr_fd(": No such file or directory\n", 2);
			}
			else
			{
				ft_putstr_fd("bash: ",2);
				ft_putstr_fd(origin_arg, 2);
				ft_putstr_fd(": commnad not found\n", 2);
			}

		}

		exit(127);
	}
	else if (errno == 13)
	{
		ft_putstr_fd("bash: ", 1);
		ft_putstr_fd(args[0], 1);
		ft_putstr_fd(": Permission denied\n", 1);
		exit(126);
	}
	return (0);
}

/*
 ** build in 以外の関数が呼ばれたときに使う関数
*/

int		exec_shell_command(char **args, t_list *e_val, t_list **d_val,char **paths, char *origin_arg)
{
	char	**envp;
	int		status;
	char	*num_str;
	char	*status_str;

	envp = change_into_array(e_val);// execve にわたす環境変数は文字列配列でなくてはならないので、ここで一回リストを文字列配列に直してる。
	if (!envp)
	{
		return (0);
	}
	g_pid = fork();
	if (g_pid == 0)
	{
		if(!child_precess(args, envp, paths, origin_arg))
			exit (1);
	}
	else if (g_pid < 0)
		strerror(errno);
	else
	{
		wait(&status);
		free_all(envp, 0);
		//ここで終了ステータスを変更する関数を入れる。
		num_str = ft_itoa(WEXITSTATUS(status)); //終了ステータスを文字列としてゲット
		status_str = ft_strjoin("?=", num_str); //終了ステータスの変数の更新用に整形
		free(num_str);
		update_val(d_val, status_str);//終了ステータス更新。
		free(status_str);
	}
	if(WIFSIGNALED(status))
	{
		if(WTERMSIG(status) == SIGQUIT)
		{
			if(WCOREDUMP(status))
				ft_putendl("Quit: (core dumped)");
			else
				ft_putendl("Quit");
		}
		if (WTERMSIG(status) == SIGINT)
		{
			// ft_putendl("kiteru\n");
			write (1, "\n", 1);
		}
	}
	return (WEXITSTATUS(status));
}

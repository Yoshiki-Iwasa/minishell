/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 09:14:29 by yiwasa            #+#    #+#             */
/*   Updated: 2020/08/28 10:59:35 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_pid;

/*
 ** シグナルハンドラー(ctrl-C 用)
*/

void		sig_handle_C(int sig)
{
	int kill_rv;
	write(1, "\b\b  ", 4);
	sig = 0;
	if (g_pid != 0)
		kill_rv = kill(g_pid, SIGKILL);
	else
		kill_rv = -1;
	write(1, "\n",1);
	if (kill_rv == -1)
	ft_putstr_fd("minishell$ ", 1);
}

/*
** シグナルハンドラー ctrl-\ 用
*/

void		sig_handle_bs(int sig)
{
	int kill_rv;

	sig = 0;
	write(1, "\b\b  \b\b", 6);
	if (g_pid != 0)
	{
		kill_rv = kill(g_pid, SIGQUIT);
	}
	else
	{
		kill_rv = -1;
	}
	if (kill_rv == -1)
	{
		signal(sig, SIG_IGN);
	}

}

/*
	子供プロセスの実行を司る関数。
*/

int	child_precess(char **args, char **envp, char **paths)
{
	int		i;
	char	command[PATH_MAX + 1];
	char	*cmd_ptr;

	i = 0;
	while(paths[i])
	{
		cmd_ptr = ft_strcat(command, paths[i]);
		cmd_ptr = ft_strcat(command, "/");
		cmd_ptr = ft_strcat(command, args[0]);
		execve(cmd_ptr, args, envp);
		cmd_ptr[0] = '\0';
		i++;
	}
	if (errno == 2)
	{
		ft_putstr_fd("bash: ",1);
		ft_putstr_fd(args[0], 1);
		ft_putstr_fd(": commnad not found\n", 1);
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

int		exec_shell_command(char **args, t_list *e_val, t_list **d_val,char **paths)
{
	char	**envp;
	int		status;
	char	*num_str;
	char	*status_str;

	// update_val(d_val, "?=0");
	envp = change_into_array(e_val);// ここで、一回envp にmalloc ガードをつける必要ある。change_into_array も同様。
	if (!envp)
	{
		return (0);
	}
	g_pid = fork();
	if (g_pid == 0)
	{
		if(!child_precess(args, envp, paths))
			exit (1);
	}
	else if (g_pid < 0)
		strerror(errno);
	else
	{
		wait(&status);
		//ここで終了ステータスを変更する関数を入れる。

		num_str = ft_itoa(WEXITSTATUS(status));
		status_str = ft_strjoin("?=", num_str);
		free(num_str);
		update_val(d_val, status_str);
		free(status_str);
	}
	if (WEXITSTATUS(status) == 0)
		return (1);
	if (WEXITSTATUS(status) == 1)
		return (0);
	return (WEXITSTATUS(status));
}
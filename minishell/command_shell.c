/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 09:14:29 by yiwasa            #+#    #+#             */
/*   Updated: 2020/08/18 09:34:27 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_pid;

/*
**	シグナルハンドラー(ctrl-C 用)
*/

void		sig_handle_C(int sig)
{
	int kill_rv;

	if (g_pid != 0)
		kill_rv = kill(g_pid, SIGKILL);
	else
		kill_rv = -1;
	write(1, "\n",1);
	if (kill_rv == -1)
	ft_putstr_fd("yiwasa$ ", 1);

}

/*
** シグナルハンドラー ctrl-\ 用
*/

void		sig_handle_bs(int sig)
{
	int kill_rv;
	write(1, "\n",1);
	if (g_pid != 0)
	{
		kill_rv = kill(g_pid, SIGQUIT);
	}
	else
	{
		kill_rv = -1;
	}
	if (kill_rv == -1)
	ft_putstr_fd("yiwasa$ ", 1);
	
}
/*
	環境変数リストを文字列の配列に変える関数
*/

char	**change_into_array(t_list *e_val) ///malloc失敗したときに全部freeするようにする。
{
	char **ret;
	int	i;

	ret = malloc(sizeof(char *) * ft_lstsize(e_val) + 1);
	i = 0;
	while (e_val)
	{
		ret[i] = ft_strdup(e_val->content);
		i++;
		e_val = e_val->next;
	}
	ret[i] = NULL;
	return (ret);
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
	return (0);
}

/*
	build in 以外の関数が呼ばれたときに使う関数
*/

int		exec_shell_command(char **args, t_list *e_val, char **paths)
{
	char	**envp;
	int		status;

	envp = change_into_array(e_val);// ここで、一回envp にmalloc ガードをつける必要ある。　change_into_array も同様。
	g_pid = fork();
	if (g_pid == 0)
	{
		if(!child_precess(args, envp, paths))
		return (0);
	}
	else if (g_pid < 0)
		strerror(errno);
	else
		wait(&status);
	return (1);
}

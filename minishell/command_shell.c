/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 09:14:29 by yiwasa            #+#    #+#             */
/*   Updated: 2020/08/08 09:28:25 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
	pid_t	pid;
	int		status;

	envp = change_into_array(e_val);
	pid = fork();
	if (pid == 0)
	{
		if(!child_precess(args, envp, paths))
		return (0);
	}
	else if (pid < 0)
		strerror(errno);
	else
		wait(&status);
	return (1);
}

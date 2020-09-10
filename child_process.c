/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 10:08:19 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/10 10:09:09 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 子供プロセスの実行を司る関数。与えられたコマンドと、PATHをexecve に逐一与えていく。
*/

int	child_precess(char **args, t_edlist *vals, char **paths, char *origin_arg)// args には "ls" "-la" みたいなふうにコマンドが文字列配列化して入っている。
{
	int		i;
	char	command[PATH_MAX + 1];
	char	*cmd_ptr;
	char	**envp;

	i = 0;
	envp = change_into_array(vals->e_val);
	while(paths[i])
	{
		if (args[0][0] == '\0')
		{
			errno = 2;
			break ;
		}
		command[0] = '\0';
		cmd_ptr = ft_strcat(command, paths[i]);
		cmd_ptr = ft_strcat(command, "/");
		cmd_ptr = ft_strcat(command, args[0]);
		execve(cmd_ptr, args, envp);
		if (errno == 8)
			break;
		cmd_ptr[0] = '\0';
		i++;
	}
	free_all(envp, 0);
	if (errno == 2)
	{
		if (paths[0][0]  == '\0')
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
	else if (errno == 8)
	{
		int fd;
		int rv;
		char *line;

		fd = open(cmd_ptr, O_RDWR);
		while (get_next_line(fd, &line) > 0)//一行取得。
			rv = launch_shell(*vals, line);
		close(fd);
		exit(0);
		return (rv);
	}
	return (0);
}

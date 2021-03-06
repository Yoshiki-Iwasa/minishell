/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 10:08:19 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/11 23:14:55 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** errno == 2 だったとき。
*/

void	put_error_2(char **paths, char *origin_arg)
{
	if (paths[0][0] == '\0')
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(origin_arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
	{
		if (origin_arg[0] == '/' || !ft_strncmp(origin_arg, "./", 2))
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(origin_arg, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		else
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(origin_arg, 2);
			ft_putstr_fd(": commnad not found\n", 2);
		}
	}
	exit(127);
}

void	make_cmp_ptr
	(char **cmd_ptr, char **command, char *paths_i, char *args_zero)
{
	(*command)[0] = '\0';
	*cmd_ptr = ft_strcat(*command, paths_i);
	*cmd_ptr = ft_strcat(*command, "/");
	*cmd_ptr = ft_strcat(*command, args_zero);
}

void	free_dup(char **args_zero, char **cmd_ptr)
{
	free(*args_zero);
	*args_zero = ft_strdup(*cmd_ptr);
}

/*
** path をつくって、execve を実行する関数。
*/

void	exec_execve(t_edlist *vals, char **args, char **paths, char **cmd_ptr)
{
	int		i;
	char	**envp;
	char	*command;

	i = -1;
	command = malloc(PATH_MAX + 1);
	envp = change_into_array(vals->e_val);
	while (paths[++i])
	{
		if (args[0][0] == '\0')
		{
			errno = 2;
			break ;
		}
		make_cmp_ptr(cmd_ptr, &command, paths[i], args[0]);
		if ((*cmd_ptr)[0] == '/' && paths[1] == NULL)
			free_dup(&args[0], cmd_ptr);
		execve(*cmd_ptr, args, envp);
		if (errno == 8)
			break ;
		(*cmd_ptr)[0] = '\0';
	}
	free_all(envp, *cmd_ptr);
}

/*
** 子供プロセスの実行を司る関数。与えられたコマンドと、PATHをexecve に逐一与えていく。
*/

int		child_precess(char **args, t_edlist *vals,\
	char **paths, char *origin_arg)
{
	char	*cmd_ptr;
	int		fd;
	int		rv;
	char	*line;

	exec_execve(vals, args, paths, &cmd_ptr);
	if (errno == 2 || errno == 63)
		put_error_2(paths, origin_arg);
	else if (errno == 13)
	{
		ft_putstr_fd("bash: ", 1);
		ft_putstr_fd(args[0], 1);
		ft_putstr_fd(": Permission denied\n", 1);
		exit(126);
	}
	else if (errno == 8)
	{
		fd = open(cmd_ptr, O_RDONLY);
		while (get_next_line(fd, &line) > 0)
			rv = launch_shell(*vals, line);
		close(fd);
		exit(0);
		return (rv);
	}
	return (0);
}

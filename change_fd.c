/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 13:36:27 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/22 11:15:58 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 標準出力のリダイレクトの実装
*/

int		change_stdout_fd(char *arg, int *fd)
{
	*fd = open(arg, O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
	if (*fd == -1)
	{
		ft_putstr_fd("bash :", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (0);
	}
	close(1);
	dup2(*fd, 1);
	close(*fd);
	return (1);
}

/*
** 標準入力のリダイレクトの実装
*/

int		change_stdin_fd(char *arg, int *fd)
{
	*fd = open(arg, O_RDONLY);
	if (*fd == -1)
	{
		ft_putstr_fd("bash :", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (0);
	}
	close(0);
	dup2(*fd, 0);
	close(*fd);
	return (1);
}

/*
** 標準出力の追記用fd 作成
*/

int		change_stdout_fd_for_append(char *arg, int *fd)
{
	*fd = open(arg, O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
	if (*fd == -1)
	{
		ft_putstr_fd("bash :", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (0);
	}
	close(1);
	dup2(*fd, 1);
	close(*fd);
	return (1);
}

/*
** 標準error出力のリダイレクトの実装
*/

int		change_stderror_fd(char *arg, int *fd)
{
	*fd = open(arg, O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
	if (*fd == -1)
	{
		ft_putstr_fd("bash :", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (0);
	}
	close(2);
	dup2(*fd, 2);
	close(*fd);
	return (1);
}

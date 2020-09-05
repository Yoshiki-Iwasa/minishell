/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_fd2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 14:02:47 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/05 14:26:39 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void change_stdout_fd_set_null(char **args, int *flag_out, int *fd, int *i)
{
	args[*i] = NULL;
	(*i)++;
	change_stdout_fd(args[*i], fd);
	*flag_out = 1;
}

void change_stdout_fd_set_null_append(char **args, int *flag_out, int *fd, int *i)
{
	args[*i] = NULL;
	(*i)++;
	change_stdout_fd_for_append(args[*i], fd);
	*flag_out = 1;
}

void change_stderror_fd_set_null(char **args, int *flag_error, int *fd, int *i)
{
	args[*i] = NULL;
	(*i)++;
	change_stderror_fd(args[*i], fd);
	*flag_error = 1;
}

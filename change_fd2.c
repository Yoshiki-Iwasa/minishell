/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_fd2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 14:02:47 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/22 11:30:53 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		change_stdout_fd_set_null(char **args, int *flag_out, int *fd, int *i)
{
	free(args[*i]);
	args[*i] = NULL;
	(*i)++;
	if (change_stdout_fd(args[*i], fd))
		*flag_out = 1;
	else
	{
		*flag_out = -1;
		return (0);
	}
	return (1);
}

int		change_stdout_fd_set_null_append
	(char **args, int *flag_out, int *fd, int *i)
{
	free(args[*i]);
	args[*i] = NULL;
	(*i)++;
	if (change_stdout_fd_for_append(args[*i], fd))
		*flag_out = 1;
	else
	{
		*flag_out = -1;
		return (0);
	}
	return (1);
}

int		change_stderror_fd_set_null
	(char **args, int *flag_error, int *fd, int *i)
{
	free(args[*i]);
	args[*i] = NULL;
	(*i)++;
	if (change_stderror_fd(args[*i], fd))
		*flag_error = 1;
	else
	{
		*flag_error = -1;
		return (0);
	}
	return (1);
}

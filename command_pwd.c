/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 10:53:30 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/09 10:53:31 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		command_pwd(void)
{
	char *pwd;
	char *buf;

	errno = 0;
	buf = NULL;
	pwd = getcwd(buf, PATH_MAX);
	if (!pwd)
	{
		ft_putendl_fd(strerror(errno), 1);
		return (1);
	}
	else
		ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 11:05:57 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/09 11:06:48 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_cd(char *arg, t_list **e_val)
{
	char	path[PATH_MAX + 1];
	char	*home;
	int		chdir_rv;

	errno = 0;
	path[0] = '\0';
	if (arg == NULL)
		arg = find_value(e_val, "HOME=");
	else if (arg[0] == '~')
	{
		home = find_value(e_val, "HOME=");
		ft_strcat(path, home);
		ft_strcat(path, &arg[1]);
		arg = path;
	}
	chdir_rv = chdir(arg);
	if (chdir_rv == -1)
	{
		ft_putendl_fd(strerror(errno), 1);
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 11:05:57 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/14 09:19:44 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_error_cd(char *arg)
{
	ft_putstr_fd("bash: cd: ", 1);
	ft_putstr_fd(arg, 1);
	ft_putstr_fd(": ", 1);
	ft_putendl_fd(strerror(errno), 1);
}

int		command_cd(char *arg, t_list **e_val)
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
		put_error_cd(arg);
		return (1);
	}
	return (0);
}

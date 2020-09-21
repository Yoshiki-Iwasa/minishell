/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 11:05:57 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/21 09:30:58 by yiwasa           ###   ########.fr       */
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

void	update_oldpwd(t_list **e_val)
{
	char *pwd;
	char *oldpwd;
	char *buf;

	buf = NULL;
	pwd = getcwd(buf, PATH_MAX);
	oldpwd = ft_strjoin("OLDPWD=", pwd);
	update_val(e_val, oldpwd);
	free(oldpwd);
	free(pwd);
}

void	update_pwd(t_list **e_val)
{
	char *pwd;
	char *newpwd;
	char *buf;

	buf = NULL;
	pwd = getcwd(buf, PATH_MAX);
	newpwd = ft_strjoin("PWD=", pwd);
	update_val(e_val, newpwd);
	free(newpwd);
	free(pwd);
}

int		command_cd(char *arg, t_list **e_val)
{
	char	path[PATH_MAX + 1];
	char	*home;
	int		chdir_rv;

	errno = 0;
	update_oldpwd(e_val);
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
	update_pwd(e_val);
	if (chdir_rv == -1)
	{
		put_error_cd(arg);
		return (1);
	}
	return (0);
}

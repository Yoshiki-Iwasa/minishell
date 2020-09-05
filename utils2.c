/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 09:18:11 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/05 13:30:26 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** 環境変数PATH に含まれているpath達を分離する関数
*/

char	**get_path(t_list *e_val)
{
	char *cmd_path;
	char **tmp;

	cmd_path = find_value(&e_val, "PATH=");
	if (!ft_strcmp(cmd_path, "not_found"))
	{
		tmp = malloc(sizeof(char*) * 2);
		tmp[0] = ft_strdup("");
		tmp[1] = NULL;
		return (tmp);
	}
	tmp = ft_split(cmd_path, ':');
	free(cmd_path);
	return (tmp);
}

/*
 **	形が、$key=value または、key=$value になってないかを調べる関数。
*/

int		check_doller_exit(char *arg)
{
	int i;

	i = 0;
	if (arg[0] == '$')
		return (1);
	while (arg[i] != '\0')
	{
		if (arg[i] == '=' && arg[i + 1] == '$')
			return (1);
		i++;
	}
	return (0);
}

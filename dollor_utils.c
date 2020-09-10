/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollor_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 11:01:06 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/10 12:37:08 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** 文字列を結合させる関数。
*/

char		*joint_strs(char **args)
{
	char	*ret;
	char	*tmp;
	int		i;

	i = 0;
	ret = ft_strdup("");
	while (args[i])
	{
		tmp = ret;
		ret = ft_strjoin(ret, args[i]);
		free(tmp);
		i++;
	}
	return (ret);
}

/*
 ** 先頭に無理やり、'$' をつける関数。
*/

int			add_dollor(char **args)
{
	int		i;
	char	*tmp;

	i = 0;
	while (args[i])
	{
		tmp = args[i];
		if (args[i][0] != '$')
		{
			args[i] = ft_strjoin("$", args[i]);
			free(tmp);
		}
		i++;
	}
	return (1);
}

/*
 ** 存在しない$変数を、空文字列に変えるための関数。
*/

void		chage_dollor_val_space(char **args)
{
	int		i;
	char	*tmp;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '$')
		{
			tmp = args[i];
			args[i] = ft_strdup("");
			free(tmp);
		}
		i++;
	}
}

void		triple_free(char *one, char *two, char *three)
{
	free(one);
	free(two);
	free(three);
}

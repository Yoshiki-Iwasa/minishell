/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_equal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 12:15:09 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/11 09:38:23 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			pattern_multi_args(char **args, int *i)
{
	if (*i > 0)
	{
		if (ft_strcmp(args[*i - 1], "export") != 0)
		{
			(*i)++;
			return (1);
		}
		return (0);
	}
	else
	{
		(*i)++;
		return (1);
	}
}

int			pattern_single_args(char **args, char **new_args, int *i, int *j)
{
	if (*i > 0)
	{
		if (!ft_strcmp(args[*i - 1], "export"))
		{
			new_args[*j] = ft_strdup(args[*i]);
			(*i)++;
			(*j)++;
			return (1);
		}
		return (0);
	}
	else
	{
		new_args[*j] = ft_strdup(args[*i]);
		(*i)++;
		(*j)++;
		return (1);
	}
}

/*
** TEST= pwd とか TEST = pwd みたいなのに対応
** TEST= pwd とか TEST =pwd ならイコールついてるやつを消す。
** TEST = pwd なら、"TEST: =: unexpected operator" 吐いて終了。<- これはむしするか、、、**
*/

char		**check_and_change_equal(char **args)
{
	int		i;
	int		j;
	char	**new_args;

	i = 0;
	j = 0;
	new_args = malloc(sizeof(char*) * (count_strs(args) + 1));
	while (args[i])
	{
		if (count_strs(args) > 1 && args[i][ft_strlen(args[i]) - 1] == '=')
		{
			if (pattern_multi_args(args, &i))
				continue ;
		}
		if (args[i + 1] == NULL && ft_strlen(args[i]) != 1 &&\
			(args[i][ft_strlen(args[i]) - 1] == '=' || args[i][0] == '='))
		{
			if (pattern_single_args(args, new_args, &i, &j))
				continue ;
		}
		new_args[j++] = ft_strdup(args[i++]);
	}
	new_args[j] = NULL;
	return (new_args);
}

/*
 ** シェル変数に使える文字列かどうかをチェック key に アンダーバー以外の特殊文字が入ってたらOUT
*/

int			check_key_str(char *arg)
{
	int i;

	i = 0;
	if (ft_isdigit(arg[0]))
	{
		return (0);
	}
	while (arg[i] != '\0' && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

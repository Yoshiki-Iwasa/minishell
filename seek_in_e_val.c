/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_in_e_val.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 12:30:38 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/10 12:30:40 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** エントリーが見つかったらそのvalue を獲得してargs に変換する関数。
*/

void	get_value_change_args_e
	(t_list *e_val, char *key, char **args_i, char *strs[3])
{
	t_list	*find;
	char	*tmp;

	if ((find = search_entry(e_val, key)))
	{
		tmp = get_key(find->content);
		free(strs[0]);
		strs[0] = find_value(&e_val, tmp);
		triple_free(tmp, key, *args_i);
		*args_i = ft_strjoin(strs[0], strs[1]);
		if ((*args_i)[0] == '$')
			(*args_i)[0] = 2;
		free(strs[0]);
		free(strs[1]);
	}
	else
	{
		free(strs[0]);
		strs[0] = ft_strdup("");
		*args_i = ft_strjoin(strs[0], strs[1]);
		triple_free(strs[0], strs[1], key);
	}
}

/*
** e_val の中を探索しに行く。
*/

int		seek_in_e_val(char **args, t_list *e_val, char *strs[3])
{
	int		i;
	char	*arg;
	char	*key;
	int		index;

	i = 0;
	while (args[i])
	{
		arg = args[i];
		if (arg[0] == '$')
		{
			index = 1;
			while (arg[index] == '_' || ft_isalnum(arg[index]))
				index++;
			strs[0] = ft_substr(arg, 0, index);
			strs[1] = ft_substr(arg, index, ft_strlen(arg));
			strs[2] = NULL;
			key = ft_strjoin(&strs[0][1], "=");
			if (!key)
				return (0);
			get_value_change_args_e(e_val, key, &args[i], strs);
		}
		i++;
	}
	return (1);
}

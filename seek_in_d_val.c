/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_in_d_val.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 12:31:30 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/10 12:32:22 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** エントリーが見つかったらそのvalue を獲得してargs に変換する関数。
*/

void	get_value_change_args_d
	(t_list *d_val, char *key, char **args_i, char *strs[3])
{
	t_list	*find;
	char	*tmp;

	if ((find = search_entry(d_val, key)))
	{
		tmp = get_key(find->content);
		free(strs[0]);
		strs[0] = find_value(&d_val, tmp);
		triple_free(tmp, key, *args_i);
		*args_i = ft_strjoin(strs[0], strs[1]);
		if ((*args_i)[0] == '$')
			(*args_i)[0] = 2;
		free(strs[0]);
		free(strs[1]);
	}
	else
		triple_free(strs[0], strs[1], key);
}

/*
** d_val の中を探索しに行く。
*/

int		seek_in_d_val(char **args, t_list *d_val, char *strs[3])
{
	int		i;
	char	*arg;
	char	*key;
	int		inx;

	i = 0;
	while (args[i])
	{
		arg = args[i];
		if (arg[0] == '$')
		{
			inx = 1;
			while (arg[inx] == '_' || ft_isalnum(arg[inx]) || arg[inx] == '?')
				inx++;
			strs[0] = ft_substr(arg, 0, inx);
			strs[1] = ft_substr(arg, inx, ft_strlen(arg));
			strs[2] = NULL;
			key = ft_strjoin(&strs[0][1], "=");
			if (!key)
				return (0);
			get_value_change_args_d(d_val, key, &args[i], strs);
		}
		i++;
	}
	return (1);
}

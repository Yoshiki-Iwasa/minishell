/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 09:18:11 by yiwasa            #+#    #+#             */
/*   Updated: 2020/08/07 09:18:37 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	環境変数PATH に含まれているpath達を分離する関数
*/
char		**get_PATH(t_list *e_val)
{
	char *cmd_path;

	cmd_path = find_value(&e_val, "PATH");
	return (ft_split(cmd_path, ':'));
}


/*
	入力の中に＄があるかどうか探す。そして変数リストから検索して値を変換して返す
*/

int		trans_valiable(char **args, t_list *d_val)
{
	int		i;
	char	*arg;
	char	*key;
	t_list	*find;

	i = 0;
	while (args[i])
	{
		arg = args[i];
		if (arg[0] == '$')
		{
			if((find = search_entry(d_val, &arg[1])))
			{
				free(args[i]);
				args[i] = find_value(&d_val, get_key(find->content));
			}
			else
			{
				ft_putstr_fd(args[i], 1);
				ft_putendl(" : No such valiable :)");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

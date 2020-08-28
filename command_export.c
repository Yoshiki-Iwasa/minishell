/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:05:12 by yiwasa            #+#    #+#             */
/*   Updated: 2020/08/27 11:08:51 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	exportコマンドを司る関数。
*/

int		command_export(char **args, t_edlist *vals)
{
	int i;
	t_list *find;

	i = 0;
	while (args[i])
	{
		if (!ft_isalpha(args[i][0]))//先頭がアルファベットじゃなかったらerror
		{
			ft_putstr_fd("bash: export: ", 1);
			ft_putstr_fd(args[i], 1);
			ft_putstr_fd(": not a valid identifier\n", 1);
			return (0);
		}
		if (check_if_key_value(args[i])) //DDD=1234 みたいな形になっていたら
		{
			update_val((&vals->e_val), args[i]);
		}
		else
		{
			if (!(find = search_entry(vals->d_val ,args[i])))
			{
				i++;
				continue ;
			}
			else
			{
				update_val((&vals->e_val), find->content);//あたらしい要素をd_val からついか。
			}
		}
		i++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 10:53:11 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/11 23:41:42 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** リストの要素削除とkeyのfreeをする関数
*/

void	delete_entry_and_free_key(t_list *val, char *key)
{
	lst_del_connect(&val, key, free);
	free(key);
}

/*
 ** command unset を実行するための関数
*/

int		command_unset(char **args, t_list *e_val, t_list *d_val)
{
	int		i;
	t_list	*find;
	char	*key;

	i = -1;
	while (args[++i])
	{
		key = get_key(args[i]);
		find = search_entry(e_val, key);
		if (find != NULL)
			delete_entry_and_free_key(e_val, key);
		else
			free(key);
	}
	i = -1;
	while (args[++i])
	{
		key = get_key(args[i]);
		find = search_entry(d_val, key);
		if (find != NULL)
			delete_entry_and_free_key(d_val, key);
		else
			free(key);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 10:53:11 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/12 12:56:43 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 文法的にout なものが送られたときの処理
*/

static int	unset_error(char *arg)
{
	ft_putstr_fd("bash: unset: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	return (1);
}

/*
** リストの要素削除とkeyのfreeをする関数
*/

void		delete_entry_and_free_key(t_list *val, char *key)
{
	lst_del_connect(&val, key, free);
	free(key);
}

/*
** unset の引数に当たるエントリーがあるか確認する関数
*/

t_list		*find_entry(char **key, char *args_i, t_list *val)
{
	*key = get_key(args_i);
	return(search_entry(val, *key));
}

/*
 ** command unset を実行するための関数
*/

int			command_unset(char **args, t_list *e_val, t_list *d_val)
{
	int		i;
	t_list	*find;
	char	*key;

	i = -1;
	while (args[++i])
	{
		if (!check_key_str(args[i]))
			return (unset_error(args[i]));
		find = find_entry(&key, args[i], e_val);
		if (find != NULL)
			delete_entry_and_free_key(e_val, key);
		else
			free(key);
	}
	i = -1;
	while (args[++i])
	{
		find = find_entry(&key, args[i], d_val);
		if (find != NULL)
			delete_entry_and_free_key(d_val, key);
		else
			free(key);
	}
	return (0);
}

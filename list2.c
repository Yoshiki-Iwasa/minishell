/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:17:24 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/09 15:54:14 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** key=value の形をした引数からkeyだけを取り出す
*/

char	*get_key(char *arg)
{
	int		i;
	int		key_len;
	char	*key;
	char	*key_equal;

	key_len = 0;
	while (arg[key_len] != '=' && arg[key_len] != '\0')
		key_len++;
	key = malloc(key_len + 1); // malloc ガード入れる必要あり。
	i = 0;
	while (i < key_len)
	{
		key[i] = arg[i];
		i++;
	}
	key[i] = '\0';
	key_equal = ft_strjoin(key, "=");
	free(key);
	return (key_equal);
}

/*
 ** arg が　key=valu　の形をしているか判定する関数
*/

int		check_if_key_value(char *arg)
{
	if (arg[0] == '=')
		return (0);
	while (ft_isspace(*arg))
		arg++;
	while (*arg != '=' && *arg != '\0')
		arg++;
	if(*arg == '\0')
		return (0);
	else
	{
		arg++;
		if (ft_isspace(*arg))
			return (0);
		else
			return (1);
	}
}

/*
 ** 新しい要素をリストの一番後ろに追加する関数
*/

int		add_val(t_list **val, char *arg)
{
	t_list *new;

	new = ft_lstnew(arg);
	if (!new)
	{
		return (0);
	}
	ft_lstadd_back(val, new);
	return (1);
}

/*
** すでにあるkey=valueのvalue を変更する。
** もしarg に対応するエントリーが存在しなければarg をリストに追加。
** arg は key=value 型で送られてくる。
*/

int		update_val(t_list **val, char *arg)
{
	t_list	*find;
	char	*key;
	char	*tmp;

	key = get_key(arg);
	if (!key)
		return (0);
	find = search_entry(*val, key);
	if (find != NULL)
	{
		tmp = find->content;
		if (!(find->content = ft_strdup(arg)))
			return (free_return(key, 0));
		free(tmp);
	}
	else
	{
		if (!(tmp = ft_strdup(arg)))
			return (free_return(key, 0));
		if (!add_val(val, tmp))
			return (free_return(tmp, 0));
		free(tmp);
	}
	free(key);
	return (1);
}

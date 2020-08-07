/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:17:24 by yiwasa            #+#    #+#             */
/*   Updated: 2020/08/07 07:45:45 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
	key=value の形をした引数からkeyだけを取り出す
*/

char	*get_key(char *arg)
{
	int		i;
	int		key_len;
	char	*key;

	key_len = 0;
	while (arg[key_len] != '=')
		key_len++;
	key = malloc(key_len + 1);
	i = 0;
	while (i < key_len)
	{
		key[i] = arg[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

/*
	arg が　key=valu　の形をしているか判定する関数
*/

int		check_if_key_value(char *arg)
{
	while(ft_isspace(*arg))
		arg++;
	while(*arg != '=' && *arg != '\0')
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
	新しい要素をリストの一番後ろに追加する関数
*/

int		add_val(t_list **val, char *arg) //ただ加えるだけじゃなくて、更新もしないといけないか。
{
	t_list *new;

	new = ft_lstnew(arg);
	ft_lstadd_back(val, new);
	return (1);
}

/*
	すでにあるkey=valueのvalue を変更する。
*/

int		update_val(t_list **val, char *arg)
{
	t_list *find;
	char *key;

	key = get_key(arg);
	find = search_entry(*val, key);
	if (find != NULL)
		find->content = ft_strdup(arg);
	else
	{
		add_val(val, ft_strdup(arg)); //lst_newで全てmallcする仕様に変えて、delにfreeを渡すように実装する必要あり。
	}
	free(key);
	return (1);
}

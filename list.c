/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 09:07:55 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/11 15:41:32 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** keyに該当するvalue だけを返す関数。これはfreeを考える必要あり
*/

char		*find_value(t_list **val, char *key)
{
	char	*value;
	int		key_len;
	t_list	*search;
	char	*ptr;

	errno = 0;
	key_len = ft_strlen(key);
	search = *val;
	while (search)
	{
		if (!ft_strncmp(search->content, key, key_len))
		{
			ptr = search->content;
			value = ft_strdup(&((ptr[key_len])));
			if (!value)
				return (0);
			return (value);
		}
		search = search->next;
	}
	return (ft_strdup("not_found"));
}

/*
 ** num 番目のlistのアドレスを返す関数。
*/

t_list		*find_num_list(t_list *lst, int num)
{
	int i;

	i = 0;
	if (!lst)
		return (0);
	while (i < num)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}

/*
 ** key に該当するlist があるかどうかを判定し、あったらそのlistのアドレスを返す関数。
*/

t_list		*search_entry(t_list *val, char *key)
{
	char	*key_equal;

	key_equal = ft_strdup(key);
	if (!key_equal)
		return (NULL);
	while (val)
	{
		if (!ft_strncmp(val->content, key_equal, ft_strlen(key_equal)))
		{
			free(key_equal);
			return (val);
		}
		val = val->next;
	}
	free(key_equal);
	return (NULL);
}

/*
 ** 一個要素を消して、つなげる関数。
*/

void		del_one(t_list **val, t_list **tmp, void (*del)(void*))
{
	*tmp = (*val)->next;
	ft_lstdelone(*val, del);
	(*val) = *tmp;
}

/*
 ** list のなかのkey に該当するlist を消す関数。
*/

void		lst_del_connect(t_list **val, char *key, void (*del)(void*))
{
	t_list	*search;
	t_list	*tmp;
	int		num;

	num = 0;
	search = *val;
	while (search)
	{
		if (!ft_strncmp(search->content, key, ft_strlen(key)))
		{
			if (num == 0)
				del_one(val, &tmp, del);
			else
			{
				tmp = find_num_list(*val, num - 1);
				tmp->next = search->next;
				ft_lstdelone(search, del);
			}
			return ;
		}
		search = search->next;
		num++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 09:07:55 by yiwasa            #+#    #+#             */
/*   Updated: 2020/08/06 13:36:30 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_e_val_list(t_list **e_val, char **envp)
{
	t_list *new;

	*e_val = ft_lstnew(*envp);
	envp++;
	while (*envp != NULL)
	{
		new = ft_lstnew(*envp);
		ft_lstadd_back(e_val, new);
		envp++;
	}
	return ;
}

char*	find_value(t_list **val, char *key)
{
	char *value;
	int key_len;
	t_list *search;

	errno = 0;
	key_len = ft_strlen(key);
	search = *val;
	while(search)
	{
		if (!ft_strncmp(search->content, key, key_len))
		{
			value = ft_strdup(&(search->content[key_len + 1]));
			if (!value)
				return (0);
			return (value);
		}
		search = search->next;
	}
	return ("not_found");
}

t_list *find_num_list(t_list *lst, int num)
{
	int i = 0;


	if (!lst)
		return (0);
	while (i < num)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}

t_list		*serch_entry(t_list **val, char *key)//リストの長差分だけmallocして検索かける。
{
	t_list **search;
	t_list *tmp;
	int num;
	char	*result;

	search = malloc(sizeof(t_list*) * ft_lstsize(*val) + 1);
	search[ft_lstsize(*val)] = NULL;
	num = 0;
	search[num] = *val;
	while (search[num])
	{
		if (!ft_strncmp(search[num]->content, key, ft_strlen(key)))
		{
			if (num == 0) //先頭を消さないといけない場合。
				return (*val);
			else
				return (find_num_list(*val, num));//見つけた場所のアドレス。
		}
		num++;
		search[num] = search[num - 1]->next;
	}
	return (NULL);
}

void	lst_del_connect(t_list **val, char *key ,void (*del)(void*))
{
	t_list *search;
	t_list *tmp;
	int num;
	char	*result;

	num = 0;
	search = *val;
	while (search)
	{
		if (!ft_strncmp(search->content, key, ft_strlen(key)))
		{//このエントリーがkeyを含んでたら、valのそこを消して、入れ替える。
			if (num == 0) //先頭を消さないといけない場合。
			{
				tmp = (*val)->next;
				ft_lstdelone(*val, del_str);
				(*val) = tmp;
			}
			else
			{
				tmp = find_num_list(*val, num -1); //keyが見つかった一個前のリストのアドレス
				tmp->next = search->next; //一個前の次を見つかった奴の次にする。
				// ft_lstdelone(search, free);
			}
			return ;
		}
		search = search->next;
		num++;
	}
	
}
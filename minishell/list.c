/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 09:07:55 by yiwasa            #+#    #+#             */
/*   Updated: 2020/08/22 10:34:04 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	一番最初に環境変数をリスト構造に初期化する関数。
*/

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

/*
	keyに該当するvalue だけを返す関数。これはfreeを考える必要あり
*/

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
			value = ft_strdup(&(search->content[key_len]));
			if (!value)
				return (0);
			return (value);
		}
		search = search->next;
	}
	return ("not_found");
}

/*
	num 番目のlistのアドレスを返す関数。
*/

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

/*
	key に該当するlist があるかどうかを判定し、あったらそのlistのアドレスを返す関数。
*/

t_list		*search_entry(t_list *val, char *key)
{
	t_list	*tmp;
	int		num;
	char	*key_equal;//ここで、送られて来たkey は "key="の形に変えて、比較してあげる方がいい。
					//freeが心配だけど。
	key_equal = ft_strjoin(key, "=");
	if (!key_equal)
		return (NULL);
	num = 0;
	while (val)
	{
		if (!ft_strncmp(val->content, key_equal, ft_strlen(key_equal)))
		{
			free(key_equal);
			return (val);//見つけた場所のアドレス。
		}
		val = val->next;
	}
	free(key_equal);
	return (NULL);
}

/*
	list のなかのkey に該当するlist を消す関数。
*/

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
				// ft_lstdelone(search, free); <- これ入れて領域解放せよ
			}
			return ;
		}
		search = search->next;
		num++;
	}	
}
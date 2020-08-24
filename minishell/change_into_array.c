/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_into_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 10:09:51 by yiwasa            #+#    #+#             */
/*   Updated: 2020/08/24 10:10:39 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** 環境変数リストを文字列の配列に変える関数
*/

char	**change_into_array(t_list *e_val)
{
	char **ret;
	int	i;

	ret = malloc(sizeof(char *) * ft_lstsize(e_val) + 1);
	if (!ret)
		return (0);
	i = 0;
	while (e_val)
	{
		ret[i] = ft_strdup(e_val->content);
		if (!ret[i])
		{
			while (i >= 0)
			{
				free(ret[i]);
				i--;
			}
			free(ret);
			return (0);
		}
		i++;
		e_val = e_val->next;
	}
	ret[i] = NULL;
	return (ret);
}

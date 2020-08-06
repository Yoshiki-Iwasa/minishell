/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:17:24 by yiwasa            #+#    #+#             */
/*   Updated: 2020/08/06 16:17:27 by yiwasa           ###   ########.fr       */
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

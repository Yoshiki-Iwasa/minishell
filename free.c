/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 07:37:54 by yiwasa            #+#    #+#             */
/*   Updated: 2020/08/28 17:54:29 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** 毎回のコマンドの実行後に各要素をfreeするために使う。
*/

void	free_all(char **args, char *line)
{
	int i;

	i = 0;
	free(line);
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

/*
 ** lstdelone に渡すために仮置きしてる
 ** 本来こいつはfreeであるべきなんだ！！！！
*/

void	del_str(void *str)
{
	str = 0;
}

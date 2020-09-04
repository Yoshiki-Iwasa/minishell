/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_multi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 12:39:01 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/04 12:52:53 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	；を見てコマンドが何個あるか数える関数。
*/

int		count_commands(char **args)
{
	int		i;
	int		count;

	i = 0;
	if (args[0][0] == ';')//258 で終了スべし。
	{
		ft_putstr_fd("bash: syntax error near unexpected token `;\'\n", 2);
		return (0);
	}
	count = 1; // コマンドの先頭にセミコロンがきた場合を排除
	while(args[i])
	{
		if(!ft_strcmp(args[i], ";") && args[i + 1] != NULL && ft_strcmp(args[i + 1], ";"))
			count++;
		else if ((!ft_strcmp(args[i], ";") && args[i + 1] != NULL && !ft_strcmp(args[i + 1], ";")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `;;\'\n", 2);
			return (0);
		}
		i++;
	}
	return (count);
}

/*
	"；"　が文字列配列の何番目に入っているかを数えるための関数。
*/

int		find_semi_co(char	**args)
{
	int num;

	num = 0;
	while(ft_strcmp(args[num], ";") && args[num] != NULL)
	{
		num++;
	}
	return (num);
}

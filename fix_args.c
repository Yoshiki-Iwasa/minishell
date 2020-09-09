/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 10:45:50 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/10 08:19:05 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** argsに含まれているascii文字をcに変える関数
*/

void	fix_args(char **args, char ascii, char c)
{
	int i;
	int j;

	i = 0;
	while (args[i] != NULL)
	{
		j = 0;
		while (args[i][j] != '\0')
		{
			if (args[i][j] == ascii)
				args[i][j] = c;
			j++;
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_unprintable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 10:06:27 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/10 06:46:13 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** クォーテーションマークによる処理を分岐する
*/

int		process_quotations(char *line, int *i)
{
	if (line[*i] == '"')
	{
		if (when_meets_double_q(line, i))
			return (1);
		else if (!when_meets_double_q(line, i))
			return (0);
	}
	else if (line[*i] == 39)
	{
		if (when_meets_single_q(line, i))
			return (1);
	}
	return (2);
}

/*
** クオーテーションで囲まれた文字列のスペースを非表示文字にする。
*/

void	insert_unprintable(char *line)
{
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$' && (line[i + 1] == '\0' || line[i + 1] == ' '))
		{
			line[i++] = 2;
			continue ;
		}
		if (line[i] == '"' || line[i] == 39)
		{
			if (process_quotations(line, &i))
				continue ;
			else if (!process_quotations(line, &i))
				break ;
		}
		if (line[i] == '"' || line[i] == 39)
			i++;
		else if (line[i] == '\0')
			break ;
		i++;
	}
}

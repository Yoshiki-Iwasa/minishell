/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 06:40:41 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/22 08:54:18 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** ダブルクオートに出会ったときに入る。
** エスケープさせたり、クオート文字を抜かす役割。
*/

int		when_meets_double_q(char *line, int *i)
{
	if (line[*i + 1] == '\0')
	{
		(*i)++;
		return (0);
	}
	if (line[*i + 1] == '"'\
		&& (line[*i + 2] == '\0' || line[*i + 2] == ' '))
	{
		if (*i > 0 && line[*i - 1] == '\\')
		{
			(*i) += 2;
			return (1);
		}
		line[*i] = ' ';
		line[*i + 1] = 4;
		(*i) += 2;
		return (1);
	}
	else
	{
		pattern_double(line, i);
		return (2);
	}
}

/*
** 該当する文字を非表示文字に変換
*/

void	change_special_char(char *line, int *i)
{
	if (line[*i] == ' ')
		line[*i] = 1;
	if (line[*i] == '$' && (line[*i + 1] == '\0' || line[*i + 1] == ' ' \
		|| line[*i + 1] == 1 || line[*i + 1] == '"'))
		line[*i] = 2;
	if (line[*i] == '>')
		line[*i] = 3;
	if (line[*i] == '<')
		line[*i] = 5;
	if (line[*i] == '=')
		line[*i] = 8;
	if (line[*i] == '|')
		line[*i] = 15;
	if (line[*i] == '2' && line[*i + 1] == '>')
	{
		line[*i] = 6;
		line[*i + 1] = 7;
	}
	if (line[*i] == '\\' && line[*i + 1] != '"' \
		&& line[*i + 1] != '$' && line[*i + 1] != '\\')
		line[*i] = 16;
}

/*
** ダブルクオーテーションでエスケープする時に下処理する関数。
*/

void	pattern_double(char *line, int *i)
{
	(*i)++;
	while (line[*i] != '"')
	{
		change_special_char(line, i);
		if (line[*i] == '\0')
			break ;
		(*i)++;
	}
}

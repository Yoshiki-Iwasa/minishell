/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_double_q.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 09:35:53 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/09 10:02:33 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** クォーテーションマークをスキップする関数。
*/

int		skip_double_q(char *line, int *i, int *quote_count)
{
	if (line[*i] == '"')
	{
		(*i)++;
		(*quote_count)++;
		return (1);
	}
	return (0);
}

/*
** ダブルクオート内でのバックスラッシュでの＄のエスケープ
*/

void	escape_dollor_in_double_q(char *line, int *i, char *new_line, int *j)
{
	if (line[*i] == '\\')
	{
		(*i)++;
		if (line[*i] == '$')
			line[*i] = 2;
	}
	new_line[(*j)++] = line[(*i)++];
}

/*
** while に break するか continue するか
*/

int		decide_break_or_continue(char *line, int *i)
{
	if (line[*i] == '\0')
		return (1);
	else
	{
		(*i)++;
		return (0);
	}
}

/*
** ダブルクオートをline から排除するための関数。
*/

int		escape_double_q(char *line, char *new_line, int *i, int *j)
{
	int quote_count;

	quote_count = 0;
	while (line[*i] != '\0')
	{
		if (skip_double_q(line, i, &quote_count))
			continue;
		if (line[*i] == '$' && line[*i + 1] != '{' && line[*i - 1] != '{')
		{
			new_line[(*j)++] = line[(*i)++];
			new_line[(*j)++] = '{';
			while (line[*i] != '"' && line[*i] != '\0')
				new_line[(*j)++] = line[(*i)++];
			if (line[*i] == '"')
				quote_count = quote_count + 1;
			new_line[(*j)++] = '}';
			if (decide_break_or_continue(line, i))
				break ;
			else
				continue ;
		}
		escape_dollor_in_double_q(line, i, new_line, j);
	}
	new_line[*j] = '\0';
	return (quote_count % 2);
}

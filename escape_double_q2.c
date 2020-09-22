/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_double_q2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 10:04:51 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/22 10:26:00 by yiwasa           ###   ########.fr       */
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
** 無理やり開カッコをつける関数
*/

void	insert_open_bracket(char *new_line, char *line, int *i, int *j)
{
	new_line[(*j)++] = line[(*i)++];
	new_line[(*j)++] = '{';
	while (line[*i] != '"' && line[*i] != '\0')
		new_line[(*j)++] = line[(*i)++];
}

/*
** quote_countを増やして、閉カッコをいれる関数
*/

void	add_q_count_and_close_bracket
	(char *line_i, char *new_line, int *j, int *quote_count)
{
	if (*line_i == '"')
		*quote_count = *quote_count + 1;
	new_line[(*j)++] = '}';
}

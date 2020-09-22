/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_double_q.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 09:35:53 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/22 10:32:39 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** ダブルクオートをline から排除するための関数。
** new_line のnull 終端は呼び出し先で。
*/

int		escape_double_q(char *line, char *new_line, int *i, int *j)
{
	int quote_count;

	quote_count = 0;
	while (line[*i] != '\0')
	{
		if (quote_count > 0 && quote_count % 2 == 0)
		{
			if (make_spaces(line, new_line, i, j))
				continue ;
		}
		if (skip_double_q(line, i, &quote_count))
			continue;
		if (line[*i] == '$' && line[*i + 1] != '{' && line[*i - 1] != '{' \
			&& line[*i + 1] != ' ')
		{
			insert_open_bracket(new_line, line, i, j);
			add_q_count_and_close_bracket(&line[*i], new_line, j, &quote_count);
			if (decide_break_or_continue(line, i))
				break ;
			else
				continue ;
		}
		escape_dollor_in_double_q(line, i, new_line, j);
	}
	return (quote_count % 2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_single_q.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 10:23:09 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/09 10:23:17 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** シングルクオートをline から排除するための関数。
*/

int	escape_single_q(char *line, char *new_line, int *i, int *j)
{
	int quote_count;

	quote_count = 0;
	while(line[*i] != '\0')
	{
		if (line[*i] == 39)
		{
			(*i)++;
			quote_count++;
			continue ;
		}
		if (line[*i] == '$')
				line[*i] = 2;
		new_line[*j] = line[*i];
		(*i)++;
		(*j)++;
	}
	new_line[*j] = '\0';
	return (quote_count % 2);
}
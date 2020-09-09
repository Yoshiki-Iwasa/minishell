/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 10:06:18 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/09 10:20:16 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		space_for_semicolon(char *new_line, int *i, int *j)
{
	new_line[*j] = ' ';
	new_line[*j + 1] = ';';
	new_line[*j + 2] = ' ';
	(*j) += 3;
	(*i)++;
	return (1);
}

int		space_for_piep(char *new_line, int *i, int *j)
{
	new_line[*j] = ' ';
	new_line[*j + 1] = '|';
	new_line[*j + 2] = ' ';
	(*j) += 3;
	(*i)++;
	return (1);
}

int		space_for_simple_redirect(char *line, char *new_line, int *i, int *j)
{
	new_line[*j] = ' ';
	new_line[*j + 1] = line[*i];
	new_line[*j + 2] = ' ';
	(*j) += 3;
	(*i)++;
	return (1);
}

int		space_for_error_redirect(char *new_line, int *i, int *j)
{
	new_line[*j] = ' ';
	new_line[*j + 1] = '2';
	new_line[*j + 2] = '>';
	new_line[*j + 3] = ' ';
	(*j) += 4;
	(*i) += 2;
	return (1);
}

/*
** パイプやリダイレクトにむりやりスペースを使う。
*/

int		make_spaces(char *line, char *new_line, int *i, int *j)
{
	if (*i > 0 && line[*i] == ';')
		return (space_for_semicolon(new_line, i, j));
	if (*i > 0 && line[*i] == '|')
		return (space_for_piep(new_line, i, j));
	if (*i > 0 && line[*i] == '>' && line[*i + 1] == '>')
	{
		new_line[*j] = ' ';
		new_line[*j + 1] = '>';
		new_line[*j + 2] = '>';
		new_line[*j + 3] = ' ';
		(*j) += 4;
		(*i) += 2;
		return (1);
	}
	if (*i > 0 && (line[*i] == '>' || line[*i] == '<'))
		return (space_for_simple_redirect(line, new_line, i, j));
	if (*i > 0 && line[*i] == '2' && line[*i + 1] == '>')
		return (space_for_error_redirect(new_line, i, j));
	return (0);
}

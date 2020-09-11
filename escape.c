/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 09:06:46 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/11 10:12:41 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		put_error_free_return(char *new_line)
{
	ft_putendl(new_line);
	free(new_line);
	ft_putendl_fd("bash : Bad quotation", 2);
	return (0);
}

static	char	*free_and_return(char *line)
{
	free(line);
	return (0);
}

void			change_chars_unprintable
	(char *line, char *new_line, int *i, int *j)
{
	(*i)++;
	if (line[*i] == '2' && line[*i + 1] == '>')
	{
		line[*i] = 6;
		line[*i + 1] = 7;
		new_line[(*j)++] = line[(*i)++];
		new_line[(*j)++] = line[(*i)++];
		return ;
	}
	if (line[*i] == '$')
		line[*i] = 2;
	if (line[*i] == '>')
		line[*i] = 3;
	if (line[*i] == '<')
		line[*i] = 5;
	if (line[*i] == '=')
		line[*i] = 8;
	if (line[*i] == ' ')
		line[*i] = 9;
	new_line[(*j)++] = line[(*i)++];
	return ;
}

/*
** ダブルクオートまたはシングルクオートが合ったときになかでエスケープさせる処理
*/

int				deal_quotations(char *line, char *new_line, int *i, int *j)
{
	if (line[*i] == '"')
	{
		if (escape_double_q(line, new_line, i, j))
			return (put_error_free_return(new_line));
	}
	else if (line[*i] == 39)
	{
		if (escape_single_q(line, new_line, i, j))
			return (put_error_free_return(new_line));
	}
	return (1);
}

/*
** クオーテーションで囲まれた文字列のスペースを非表示文字にしてクオートを削除
*/

char			*preparation_for_escape(char *line)
{
	int		i;
	int		j;
	char	*new_line;

	insert_unprintable(line);
	if (!(new_line = malloc(10000 + 1)))
		return (free_and_return(line));
	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		if (make_spaces(line, new_line, &i, &j))
			continue ;
		if (line[i] == '\\')
		{
			change_chars_unprintable(line, new_line, &i, &j);
			continue ;
		}
		if (!deal_quotations(line, new_line, &i, &j))
			return (0);
		new_line[j++] = line[i++];
	}
	free(line);
	new_line[j] = '\0';
	return (new_line);
}

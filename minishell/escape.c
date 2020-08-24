/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 09:06:46 by yiwasa            #+#    #+#             */
/*   Updated: 2020/08/24 08:32:15 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	ダブルクオートをline から排除するための関数。
*/

void	escape_double_q(char *line, char *new_line, int *i, int *j)
{
	while(line[*i] != '"')
	{
		new_line[*j] = line[*i];
		(*i)++;
		(*j)++;
	}
	(*i)++;
}

/*
	シングルクオートをline から排除するための関数。
*/

void	escape_single_q(char *line, char *new_line, int *i, int *j)
{
	while(line[*i] != 39)
	{
		new_line[*j] = line[*i];
		(*i)++;
		(*j)++;
	}
	(*i)++;
}

/*
	クオーテーションで囲まれた文字列のスペースを非表示文字にしてクオートを削除
*/
char	*preparation_for_escape(char *line)
{
	int		i;
	int		j;
	char	*new_line;

	insert_unprintable(line);

	new_line = malloc(ft_strlen(line) + 1);
	if (!new_line)
	{
		free(line);
		return (0);
	}
	i = 0;
	j = 0;
	while(line[i] != '\0')
	{
		if (line[i] == '"')
		{
			i++;
			escape_double_q(line, new_line, &i, &j);
		}
		else if (line[i] == 39)
		{
			i++;
			escape_single_q(line, new_line, &i, &j);
		}
		new_line[j] = line[i];
		i++;
		j++;
	}
	free(line);
	new_line[j] = '\0';
	return (new_line);
}

/*
	argsに含まれている非表示文字を空白に変える関数
*/

void	fix_args(char **args)
{
	int i;
	int j;

	i = 0;
	while(args[i] != NULL)
	{
		j = 0;
		while(args[i][j] != '\0')
		{
			if (args[i][j] == 1) // エスケープさせるために非表示文字にしてたところをスペースに直す
				args[i][j] = ' ';
			j++;
		}
		i++;
	}
}

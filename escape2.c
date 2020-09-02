/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 09:07:44 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/02 09:47:02 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
	ダブルクオーテーションでエスケープする時に下処理する関数。
*/

void	pattern_double(char *line, int *i)
{
	(*i)++;
	while(line[*i] != '"')
	{
		if(line[*i] == ' ')
			line[*i] = 1;
		if(line[*i] == '$')
			line[*i] = 2;
		else if (line[*i] == '\0')
			break;
		(*i)++;
	}
}

/*
	シングルクオーテーションでエスケープする時に下処理する関数。
*/

void	pattern_single(char *line, int *i)
{
	(*i)++;
	while(line[*i] != 39)
	{
		if(line[*i] == ' ')
			line[*i] = 1;
		if(line[*i] == '$')
			line[*i] = 2;
		else if (line[*i] == '\0')
			break;
		(*i)++;
	}
}

/*
	クオーテーションで囲まれた文字列のスペースを非表示文字にする。
*/

void	insert_unprintable(char *line)
{
	int		i;

	i = 0;
	while(line[i] != '\0')
	{
		if (line[i] == '"' || line[i] == 39)
		{
			if (line[i] == '"')
				pattern_double(line, &i);
			else if (line[i] == 39)
				pattern_single(line, &i);
		}
		if (line[i] == '"' || line[i] == 39)
			i++;
		else if(line[i] == '\0')
			break ;
		i++;
	}
}

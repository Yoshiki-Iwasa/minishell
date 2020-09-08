/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_unprintable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 10:06:27 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/08 09:40:47 by yiwasa           ###   ########.fr       */
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
		if (line[*i] == '$' && (line[*i + 1] == '\0' || line[*i + 1] == ' ' || line[*i + 1] == 1 || line[*i + 1] == '"'))
			line[*i] = 2;
		if(line[*i] == '>')
			line[*i] = 3;
		if(line[*i] == '<')
			line[*i] = 5;
		if(line[*i] == '=')
			line[*i] = 8;
		if(line[*i] == '2' && line[*i + 1] == '>')
		{
			line[*i] = 6;
			line[*i + 1] = 7;
		}
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
		if(line[*i] == '>')
			line[*i] = 3;
		if(line[*i] == '<')
			line[*i] = 5;
		if(line[*i] == '=')
			line[*i] = 8;
		if(line[*i] == '2' && line[*i + 1] == '>')
		{
			line[*i] = 6;
			line[*i + 1] = 7;
		}
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
		if (line[i] == '$' && (line[i + 1] == '\0' || line[i + 1] == ' '))
		{
			line[i] = 2;
			i++;
			continue ;
		}
		if (line[i] == '"' || line[i] == 39)
		{
			if (line[i] == '"')
			{
				if (line[i + 1] == '\0')
				{
					i++;
					break ;
				}
				if (line[i + 1] == '"' && (line[i + 2] == '\0' || line[i + 2] == ' '))//"" を空文字にする処理。
				{
					if (i > 0 && line[i - 1] == '\\')
					{
						i += 2;
						continue ;
					}
					line[i] = ' ';
					line[i + 1] = 4;
					i += 2;
					continue ;
				}
				else
					pattern_double(line, &i);
			}
			else if (line[i] == 39)
			{
				if (line[i + 1] == 39)
				{
					line[i] = ' ';
					line[i + 1] = 4;
					i += 2;
					continue ;
				}
				if (line[i + 1] == 39 && (line[i + 2] == '\0' || line[i + 2] == ' '))//'' を空文字にする処理。
				{
					line[i] = ' ';
					line[i + 1] = 4;
					i += 2;
					continue ;
				}
				if (line[i + 1] == '\\')
				{
					i+=2;
					continue ;
				}
				else
					pattern_single(line, &i);
			}
		}
		if (line[i] == '"' || line[i] == 39)
			i++;
		else if(line[i] == '\0')
			break ;
		i++;
	}
}

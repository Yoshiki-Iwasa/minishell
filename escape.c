/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 09:06:46 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/04 15:17:10 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	ダブルクオートをline から排除するための関数。
*/

// ダブルクオートの数を数えて、奇数だったらerror
int	escape_double_q(char *line, char *new_line, int *i, int *j)
{
	int quote_count;

	quote_count = 0;
	while(line[*i] != '\0')
	{
		if (line[*i] == '"')
		{
			(*i)++;
			quote_count++;
			continue ;
		}
		if (line[*i] == '\\') //エスケープさせる。
		{
			(*i)++;
			if (line[*i] == '$' && line[*i + 1] != '{')
				line[*i] = 2;
		}
		new_line[*j] = line[*i];
		(*i)++;
		(*j)++;
	}
	new_line[*j] = '\0';
	if (quote_count % 2 != 0)
		return (0);
	// (*i)++;
	return (1);
}

/*
	シングルクオートをline から排除するための関数。
*/
// シングルクオートの数を数えて、奇数だったらerror
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
		if (line[*i] == '\\') //エスケープさせる。
		{
			(*i)++;
			if (line[*i] == '$')
				line[*i] = 2;
		}
		new_line[*j] = line[*i];
		(*i)++;
		(*j)++;
	}
		new_line[*j] = '\0';

	if (quote_count % 2 != 0)
		return (0);
	// (*i)++;
	return (1);
}

/*
	クオーテーションで囲まれた文字列のスペースを非表示文字にしてクオートを削除
*/

char	*preparation_for_escape(char *line)
{
	int		i;
	int		j;
	char	*new_line;

	insert_unprintable(line);//バックスラッシュ以外のエスケープ担当。
							// エスケープさせたい文字にだけunprintable を挿入。

	new_line = malloc(PATH_MAX + 1);
	if (!new_line)
	{
		free(line);
		return (0);
	}
	i = 0;
	j = 0;
	while(line[i] != '\0')
	{
		if (i > 0 && line[i] == ';')
		{
			new_line[j] = ' ';
			new_line[j + 1] = ';';
			new_line[j + 2] = ' ';
			j+=3;
			i++;
			continue;
		}
		if (i > 0 && line[i] == '>' && line[i + 1] == '>' )
		{
			new_line[j] = ' ';
			new_line[j + 1] = '>';
			new_line[j + 2] = '>';
			new_line[j + 3] = ' ';
			j+=4;
			i+=2;
			continue;
		}
		if (i > 0 && (line[i] == '>' || line[i] == '<' ))
		{
			new_line[j] = ' ';
			new_line[j + 1] = line[i];
			new_line[j + 2] = ' ';
			j+=3;
			i++;
			continue;
		}
		if (i > 0 && line[i] == '2' && line[i + 1] == '>' )
		{
			new_line[j] = ' ';
			new_line[j + 1] = '2';
			new_line[j + 2] = '>';
			new_line[j + 3] = ' ';
			j+=4;
			i+=2;
			continue;
		}
		if (line[i] == '\\') //バックスラッシュによるエスケープ。
		{
			i++;
			if(line[i] == '2' && line[i + 1] == '>')
			{
				line[i] = 6;
				line[i + 1] = 7;
				new_line[j] = line[i];
				i++;
				j++;
				new_line[j] = line[i];
				i++;
				j++;
				continue ;
			}
			if (line[i] == '$')
				line[i] = 2;
			if(line[i] == '>')
				line[i] = 3;
			if(line[i] == '<')
				line[i] = 5;
			if(line[i] == '=')
				line[i] = 8;
			if(line[i] == ' ')
				line[i] = 9;
			new_line[j] = line[i];
			i++;
			j++;
			continue ;
		}
		if (line[i] == '"')
		{
			if(!escape_double_q(line, new_line, &i, &j))
			{
				free(new_line);
				ft_putendl("bash : Bad quotation");
				return (0);
			}
		}
		else if (line[i] == 39)
		{
			if(!escape_single_q(line, new_line, &i, &j))
			{
				ft_putendl("bash : Bad quotation");
				free(new_line);
				return (0);
			}
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
 ** argsに含まれているascii文字をcに変える関数
*/

void	fix_args(char **args, char ascii, char c)
{
	int i;
	int j;

	i = 0;
	while(args[i] != NULL)
	{
		j = 0;
		while(args[i][j] != '\0')
		{
			if (args[i][j] == ascii) // エスケープさせるために非表示文字にしてたところをスペースに直す
				args[i][j] = c;
			j++;
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 09:06:46 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/09 08:19:55 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** ダブルクオート内でのバックスラッシュでの＄のエスケープ
*/

void	escape_dollor_in_double_q(char *line, int *i)
{
	(*i)++;
	if (line[*i] == '$' /*&& line[*i + 1] != '{'*/)
		line[*i] = 2;
}

/*
** ダブルクオートをline から排除するための関数。
*/

int	escape_double_q(char *line, char *new_line, int *i, int *j)
{
	int quote_count;
	int doller_flag;

	doller_flag = 0;
	quote_count = 0;
	while(line[*i] != '\0')
	{
		if (line[*i] == '"')
		{
			(*i)++;
			quote_count++;
			continue ;
		}
		if (line[*i] == '$' && line[*i + 1] != '{' && line[*i - 1] != '{')
		{
			new_line[(*j)++] = line[(*i)++];
			new_line[(*j)++] = '{';
			while(line[*i] != '"' && line[*i] != '\0')
				new_line[(*j)++] = line[(*i)++];
			if (line[*i] == '"')
				quote_count++;
			new_line[(*j)++] = '}';
			if (line[(*i)++] == '\0')
				break;
			else
				continue ;
		}
		if (line[*i] == '\\')
			escape_dollor_in_double_q(line, i);
		new_line[(*j)++] = line[(*i)++];
	}
	new_line[*j] = '\0';
	if (quote_count % 2 != 0)
		return (0);
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
		if (line[*i] == '$')
				line[*i] = 2;
		new_line[*j] = line[*i];
		(*i)++;
		(*j)++;
	}
		new_line[*j] = '\0';

	if (quote_count % 2 != 0)
		return (0);
	return (1);
}

static	char*	put_error_free_return(char *new_line)
{
		ft_putendl(new_line);
		free(new_line);
		ft_putendl_fd("bash : Bad quotation", 2);
		return (0);
}

static	char*	free_and_return(char *line)
{
	free(line);
	return (0);
}

/*
** ';' や '>' など、近くにスペースがなくても無理やりスペースを作る関数
*/

int		make_spaces(char *line, char *new_line, int *i, int *j)
{
	if (*i > 0 && line[*i] == ';')
	{
		new_line[*j] = ' ';
		new_line[*j + 1] = ';';
		new_line[*j + 2] = ' ';
		(*j)+=3;
		(*i)++;
		return (1);
	}
	if (*i > 0 && line[*i] == '|')
	{
		new_line[*j] = ' ';
		new_line[*j + 1] = '|';
		new_line[*j + 2] = ' ';
		(*j)+=3;
		(*i)++;
		return (1);
	}
	if (*i > 0 && line[*i] == '>' && line[*i + 1] == '>' )
	{
		new_line[*j] = ' ';
		new_line[*j + 1] = '>';
		new_line[*j + 2] = '>';
		new_line[*j + 3] = ' ';
		(*j)+=4;
		(*i)+=2;
		return (1);
	}
	if (*i > 0 && (line[*i] == '>' || line[*i] == '<' ))
	{
		new_line[*j] = ' ';
		new_line[*j + 1] = line[*i];
		new_line[*j + 2] = ' ';
		(*j)+=3;
		(*i)++;
		return (1);
	}
	if (*i > 0 && line[*i] == '2' && line[*i + 1] == '>' )
	{
		new_line[*j] = ' ';
		new_line[*j + 1] = '2';
		new_line[*j + 2] = '>';
		new_line[*j + 3] = ' ';
		(*j)+=4;
		(*i)+=2;
		return (1);
	}
	// if (*i > 0 && line[*i] == '"' && line[*i - 1] != ' ' )
	// {
	// 	new_line[*j] = ' ';
	// 	new_line[*j + 1] = '"';
	// 	(*j)+=2;
	// 	(*i)++;
	// 	return (1);
	// }
	return (0);
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
	new_line = malloc(PATH_MAX + 1);// 入力の長さ見て変更する必要あるかも
	if (!new_line)
		return(free_and_return(line));
	i = 0;
	j = 0;
	while(line[i] != '\0')
	{
		if(make_spaces(line, new_line, &i, &j))
			continue ;
		if (line[i] == '\\') //バックスラッシュによるエスケープ。
		{
			i++;
			if(line[i] == '2' && line[i + 1] == '>')
			{
				line[i] = 6;
				line[i + 1] = 7;
				new_line[j++] = line[i++];
				new_line[j++] = line[i++];
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
			new_line[j++] = line[i++];
			continue ;
		}
		if (line[i] == '"')
		{
			if(!escape_double_q(line, new_line, &i, &j))
				return (put_error_free_return(new_line));
		}
		else if (line[i] == 39)
		{
			if(!escape_single_q(line, new_line, &i, &j))
				return (put_error_free_return(new_line));
		}
		new_line[j++] = line[i++];
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

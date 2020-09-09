/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 09:06:46 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/09 10:22:59 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /*
// ** シングルクオートをline から排除するための関数。
// */

// int	escape_single_q(char *line, char *new_line, int *i, int *j)
// {
// 	int quote_count;

// 	quote_count = 0;
// 	while(line[*i] != '\0')
// 	{
// 		if (line[*i] == 39)
// 		{
// 			(*i)++;
// 			quote_count++;
// 			continue ;
// 		}
// 		if (line[*i] == '$')
// 				line[*i] = 2;
// 		new_line[*j] = line[*i];
// 		(*i)++;
// 		(*j)++;
// 	}
// 	new_line[*j] = '\0';
// 	return (quote_count % 2);
// }

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
			if(escape_double_q(line, new_line, &i, &j))
				return (put_error_free_return(new_line));
		}
		else if (line[i] == 39)
		{
			if(escape_single_q(line, new_line, &i, &j))
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

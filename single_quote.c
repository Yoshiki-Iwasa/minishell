/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 06:40:56 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/10 06:42:40 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
** シングルクオートに出会ったときに入る。
** エスケープさせたり、クオート文字を抜かす役割。
*/

int		when_meets_single_q(char *line, int *i)
{
	if (line[*i + 1] == 39)
	{
		line[*i] = ' ';
		line[*i + 1] = 4;
		(*i) += 2;
		return (1);
	}
	if (line[*i + 1] == 39 && (line[*i + 2] == '\0' || line[*i + 2] == ' '))//'' を空文字にする処理。
	{
		line[*i] = ' ';
		line[*i + 1] = 4;
		(*i) += 2;
		return (1);
	}
	if (line[*i + 1] == '\\')
	{
		(*i)+=2;
		return (1);
	}
	else
	{
		pattern_single(line, i);
		return (2);
	}
}

/*
** シングルクオーテーションでエスケープする時に下処理する関数。
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 13:01:59 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/06 13:02:11 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
	> < >> を見て実行数が何個あるか数える関数。
*/

int		count_execs(char **args)
{
	int		i;
	int		count;

	i = 0;
	count = 1; // コマンドの先頭にセミコロンがきた場合を排除
	while(args[i])
	{
		if(!ft_strcmp(args[i], ";") && args[i + 1] != NULL && ft_strcmp(args[i + 1], ";"))
			count++;
		i++;
	}
	return (count);
}


/**
 * "|" が何個入っているか数える関数
 * */

int		count_pipe(char **args)
{
	int		i;
	int		count;

	i = 0;
	count = 0; // コマンドの先頭にセミコロンがきた場合を排除
	while(args[i])
	{
		if (!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], "<") || !ft_strcmp(args[i], ">>"))
		{
			// args[i] = NULL;
			i++;
			if (!args[i])
				break ;
		}
		if(!ft_strcmp(args[i], "|"))
			count++;
		i++;
	}
	return (count);
}


/*
	args_array に、args のパイプが入ってるとこの次のコマンドのアドレスを渡す。
	そうすると、コマンド群の配列ができる。args は、malloc してできた配列で、必ずしもメモリが一列に並んでいるとは限らない？
*/

void	args_into_array(char **args, char ****args_array, int pipe_num)
{
	int i;
	int j;

	*args_array = malloc(sizeof(char **) * (pipe_num + 2));
	(*args_array)[pipe_num + 1] = NULL;
	(*args_array)[0] = &args[0];
	i = 0;
	j = 1;
	while (args[i])
	{
		if(!ft_strcmp(args[i], "|"))
		{
			(*args_array)[j] = &args[i + 1];
			args[i] = NULL;
			j++;
		}
		i++;
	}
	return ;
}

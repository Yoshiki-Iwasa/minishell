/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:12:42 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/22 12:41:59 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			free_args_set_null(char **args, int *i)
{
	free(args[*i]);
	args[(*i)++] = NULL;
}

/*
** リダイレクト演算子が何であるかを見て標準入出力を変える関数
*/

int				decide_redirection(char **args, t_flags *flag, int *fd, int *i)
{
	if (!ft_strcmp(args[*i], "<"))
	{
		free_args_set_null(args, i);
		if (set_in_flag(args, flag, fd, *i) == 0)
			return (0);
	}
	else if (!ft_strcmp(args[*i], ">") || !ft_strcmp(args[*i], ">|") \
		|| !ft_strcmp(args[*i], "1>"))
	{
		if (change_stdout_fd_set_null(args, &(flag->flag_out), fd, i) == 0)
			return (0);
	}
	else if (!ft_strcmp(args[*i], ">>"))
	{
		if (change_stdout_fd_set_null_append(args, &(flag->flag_out), \
			fd, i) == 0)
			return (0);
	}
	else if (!ft_strcmp(args[*i], "2>"))
	{
		if (change_stderror_fd_set_null(args, &(flag->flag_error), \
			fd, i) == 0)
			return (0);
	}
	return (1);
}

/*
** redirection の文字を読み取って、fd を変換する関数
*/

void			change_fd_based_on_redirection
	(t_flags *flag, char **args, int *fd)
{
	int i;

	i = 0;
	while (args[i])
	{
		if (decide_redirection(args, flag, fd, &i) == 0)
			return ;
		if (args[i])
			i++;
	}
}

/*
 ** リダイレクトの処理をする。具体的には、fd の値を書き換えて標準入出力先を変更する。
*/

int				deal_redirection(char **args, int *fd)
{
	t_flags flag;

	init_flags(&flag);
	change_fd_based_on_redirection(&flag, args, fd);
	if (flag.flag_in > 0 && !flag.flag_out)
		return (0);
	else if (flag.flag_out > 0 && !flag.flag_in)
		return (1);
	else if (flag.flag_error > 0 && flag.flag_in != -1)
		return (2);
	else if (flag.flag_in == -1 || flag.flag_out == -1 || flag.flag_error == -1)
		return (-1);
	else
		return (3);
}

/*
 ** リダイレクトの文法をチェックする関数。
*/

int				check_redirect_syntax(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		if (!ft_strcmp(">", args[i]) || !ft_strcmp("<", args[i]) || \
			!ft_strcmp(">>", args[i]) || !ft_strcmp("2>", args[i]))
		{
			if (!ft_strcmp(args[i + 1], ";") || !args[i + 1] || \
				!ft_strcmp(args[i + 1], ">") || !ft_strcmp(args[i + 1], "<") \
				|| !ft_strcmp(args[i + 1], ">>") || \
				!ft_strcmp(args[i + 1], "2>"))
				return (0);
		}
		i++;
	}
	return (1);
}

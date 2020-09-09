/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:12:42 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/09 11:45:35 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** フラグの初期化を行う。
*/

static	void	init_flags(t_flags *flag)
{
	flag->flag_in = 0;
	flag->flag_error = 0;
	flag->flag_out = 0;
}

void			set_error_and_flag(char **error, char *arg, t_flags *flag)
{
	*error = arg;
	flag->flag_in = -1;
}

void			change_fd_based_on_redirection
	(t_flags *flag, char **args, int *fd, char **error)
{
	int i;

	i = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], "<"))
		{
			args[i++] = NULL;
			if (change_stdin_fd(args[i], fd))
				flag->flag_in = 1;
			else
				set_error_and_flag(error, args[i], flag);
		}
		else if (!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], ">|") \
			|| !ft_strcmp(args[i], "1>"))
			change_stdout_fd_set_null(args, &(flag->flag_out), fd, &i);
		else if (!ft_strcmp(args[i], ">>"))
			change_stdout_fd_set_null_append(args, &(flag->flag_out), fd, &i);
		else if (!ft_strcmp(args[i], "2>"))
			change_stderror_fd_set_null(args, &(flag->flag_error), fd, &i);
		if (args[i])
			i++;
	}
}

/*
 ** リダイレクトの処理をする。具体的には、fd の値を書き換えて標準入出力先を変更する。
*/

int				deal_redirection(char **args, int *fd, char **error)
{
	t_flags flag;

	init_flags(&flag);
	change_fd_based_on_redirection(&flag, args, fd, error);
	if (flag.flag_in > 0 && !flag.flag_out)
		return (0);
	else if (flag.flag_out && !flag.flag_in)
		return (1);
	else if (flag.flag_error && flag.flag_in != -1)
		return (2);
	else if (flag.flag_in == -1)
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
		if (!ft_strcmp(">", args[i]) || !ft_strcmp("<", args[i]) || !ft_strcmp(">>", args[i]) || !ft_strcmp("2>", args[i]))
		{
			if (!ft_strcmp(args[i + 1], ";") || !args[i + 1] || !ft_strcmp(args[i + 1], ">") || !ft_strcmp(args[i + 1], "<") || !ft_strcmp(args[i + 1], ">>") || !ft_strcmp(args[i + 1], "2>"))
			return (0);
		}
		i++;
	}
	return (1);
}

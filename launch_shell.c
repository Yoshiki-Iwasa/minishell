/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 12:00:04 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/20 11:39:23 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** syntax error を履きながら、free をしてreturn する関数。
*/

int			put_syntax_error_free_return(char **args, char *line, int arglen)
{
	ft_putstr_fd("bash: syntax error near unexpected token `newline\'\n",\
			2);
	free_args(args, line, arglen);
	return (1);
}

/*
** fix_args をまとめて行う関数。
*/

static void	fix_args_compose(char **args)
{
	fix_args(args, 1, ' ');
	fix_args(args, 4, '\0');
	fix_args(args, 6, '2');
	fix_args(args, 9, ' ');
}

/*
** コマンドを読み込んでshell を実行する関数。
*/

int			launch_shell(t_edlist vals, char *line)
{
	int		state;
	char	**args;
	int		cmd_num;
	int		arglen;

	line = preparation_for_escape(line);
	if (!line)
		return (1);
	args = ft_split(line, ' ');
	arglen = count_strs(args);
	if (args == NULL || args[0] == NULL)
		return (free_return(line, 1));
	if (!(check_redirect_syntax(args)))
		return (put_syntax_error_free_return(args, line, arglen));
	fix_args_compose(args);
	if (!(cmd_num = count_commands(args)))
	{
		update_val(&vals.d_val, "?=2");
		free_args(args, line, arglen + 1);
		return (1);
	}
	state = exec_each_command(vals, args, cmd_num);
	free_args(args, line, arglen + 1);
	return (state);
}

/*
 ** コマンドの実行の前に、入力取得ー＞ エスケープの処理 -> セミコロンによるコマンド分割を行う。
*/

int			commnad_loop(t_edlist vals)
{
	int		state;
	char	*line;

	state = 1;
	while (state != 0 && state < 1000)
	{
		ft_putstr_fd("minishell$ ", 1);
		if (!read_command(&line, &state, vals.d_val))
			continue ;
		state = launch_shell(vals, line);
	}
	if (state >= 1000)
	{
		return (state - 1000);
	}
	return (state);
}

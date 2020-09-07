/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 07:47:02 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/07 13:06:50 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** 各コマンドを実行する前にパイプの有無を見て処理を変える関数。
*/

int			shell_execute(char **args, t_edlist *vals)
{
	int pipe_count;

	pipe_count = count_pipe(args);
	if (pipe_count == 0)
	{
		return (pattern_pipe_not_exit(args, vals));
	}
	else
	{
		return (pattern_pipe_exist(args, vals, pipe_count));
	}
}

/*
** DDD= ; ls みたいなとき、DDD= -> ls に実行コマンドを進める関数
*/

void		go_to_next_command(char ***args, int *cmd_num, int semi_co_place)
{
	(*cmd_num)--;
	if (*cmd_num)
		(*args) = &((*args)[semi_co_place + 1]);
}

/*
 ** 一個以上のコマンドを順に実行するコマンド。
*/

int			exec_each_command(t_edlist vals, char **args, int cmd_num)
{
	int		state;
	int		semi_co_place;

	while (cmd_num)
	{
		state = 1;
		change_semicon_null(args, &semi_co_place);
		if (!translate_dollor_valiable(args, (vals.d_val), vals.e_val))
		{
			go_to_next_command(&args, &cmd_num, semi_co_place);
			continue ;
		}
		if (args[0] == 0 || args[0][0] == 0)
		{
			go_to_next_command(&args, &cmd_num, semi_co_place);
			continue ;
		}
		state = shell_execute(args, &(vals));
		if (!state)
			break ;
		go_to_next_command(&args, &cmd_num, semi_co_place);
	}
	return (state);
}

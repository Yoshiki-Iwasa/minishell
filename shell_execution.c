/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 07:47:02 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/07 12:31:36 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** 各コマンドを実行する前にパイプの有無を見て処理を変える関数。
*/

int		shell_execute(char **args, t_edlist *vals)
{
	int pipe_count; //パイプの個数。
	int	rv; //コマンド実行時の返り値を取得。
	char *state_val;
	char *state;

	pipe_count = count_pipe(args);
	if (pipe_count == 0)
	{
		rv = no_pipe(args, vals); //ここの返り値を見て、成功したら１、失敗したら０
		if (rv == 100)//exit の場合100が帰るようになっている。
		{
			if (!update_val(&(vals->d_val), "?=0"))
				return (1);
			return (0);
		}
		else
		{
			state_val = ft_itoa(rv);
			state = ft_strjoin("?=", state_val);
			if (!update_val(&(vals->d_val), state))
				return (1);
			free(state_val);
			free(state);
			if (rv == 0)
				return (1);
			else
				return (rv);
		}
	}
	else
	{
		rv = yes_pipe(args, vals, pipe_count);
		if (rv == 0)
		{
			if (!update_val(&(vals->d_val), "?=0"))
				return (1);
		}
		else if (rv == 1)
		{
			if (!update_val(&(vals->d_val), "?=1"))
				return (1);
		}
		else if (rv == 100)//exit の場合100が帰るようになっている。
			return (0);
	}
	return (1);
}

/*
 ** 一個以上のコマンドを順に実行するコマンド。
*/

int		exec_each_command(t_edlist vals, char **args, int cmd_num)
{
	int		state;
	int		semi_co_place;


	while(cmd_num)
	{
		state = 1;
		change_semicon_null(args, &semi_co_place);//セミコロンがどこにあるかsemi_co_place に格納。同時に、セミコロンがあった場所はNULLにしてある。
		if(!translate_dollor_valiable(args, (vals.d_val), vals.e_val)) // ここで、$変数を変換している。
		{
			cmd_num--;
			if (cmd_num)
				args = &args[semi_co_place + 1];
			continue ;
		}
		if (args[0] == 0 || args[0][0] == 0)
		{
			cmd_num--;
			if (cmd_num)
				args = &args[semi_co_place + 1];
			continue ;

		}
		 //エスケープされていた'$'はここで復帰させる。
								//復帰させるのはここでないと、上の＄変換関数で変換されちゃうから。
		state = shell_execute(args, &(vals)); // ”;”　で区切られた各コマンドを実行する関数。
		if (!state) //state = 0でminishell 終了。
			break;
		cmd_num--; //$ pwd ; ls のような時、 cmd_num = 2 -> cmd_num = 1 -> cmd_num = 0 となる。
		if (cmd_num) // コマンドがまだ残ってるときは、args の先頭を pwd -> ls へと変更。
			args = &args[semi_co_place + 1];
	}
	return (state);
}

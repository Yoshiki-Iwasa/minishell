/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 07:47:02 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/07 12:50:03 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** 各コマンドを実行する前にパイプの有無を見て処理を変える関数。
*/

int		shell_execute(char **args, t_edlist *vals)
{
	int pipe_count; //パイプの個数。

	pipe_count = count_pipe(args);
	if (pipe_count == 0)
		return (pattern_pipe_not_exit(args, vals));
	else
	{
		return (pattern_pipe_exist(args, vals, pipe_count));
		// //yes pipe のときもno pipe みたいに返り値とか考える必要あり。
		// rv = yes_pipe(args, vals, pipe_count);
		// if (rv == 0)
		// {
		// 	if (!update_val(&(vals->d_val), "?=0"))
		// 		return (1);
		// }
		// else if (rv == 1)
		// {
		// 	if (!update_val(&(vals->d_val), "?=1"))
		// 		return (1);
		// }
		// else if (rv == 100)//exit の場合100が帰るようになっている。
		// 	return (0);
		// else
		// 	return (1);
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

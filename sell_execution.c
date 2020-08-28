/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sell_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 07:47:02 by yiwasa            #+#    #+#             */
/*   Updated: 2020/08/28 16:36:46 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** 各コマンドを実行する前にパイプの有無を見て処理を変える関数。
*/

int		shell_execute(char **args, t_edlist *vals, char **paths)
{
	int pipe_count;
	int	rv;

	pipe_count = count_pipe(args);
	if (pipe_count == 0)
	{
		rv = no_pipe(args, vals, paths); //ここの返り値を見て、成功したら１、失敗したら０
		if (rv == 1)
		{
			if (!update_val(&(vals->d_val), "?=0"))
				return (1);
		}
		else if (rv == 0)
		{
			if (!update_val(&(vals->d_val), "?=1"))
				return (1);
		}
		else if (rv == 100)//exit の場合100が帰るようになっている。
			return (0);
	}
	if (pipe_count > 0)
		yes_pipe(args, vals, paths, pipe_count);
	return (1);
}

/*
 ** 一個以上のコマンドを順に実行するコマンド。
*/

int		exec_each_command(t_edlist vals, char **paths, char **args, int cmd_num)
{
	int		state;
	int		semi_co_place;

	while(cmd_num)
	{
		change_semicon_null(args, &semi_co_place);//セミコロンがどこにあるかsemi_co_place に格納。同時に、セミコロンが合った場所はNULLにしてある。
		// ここ以降でメモリリークが発生する可能性あり。
		if(!translate_dollor_valiable(args, (vals.d_val), vals.e_val)) // ここで、$変数を変換している。
		{
			cmd_num--;
			if (cmd_num)
				args = &args[semi_co_place + 1];
			continue ;
		}
		fix_args(args, 2, '$'); //エスケープされていた'$'はここで復帰させる。
		state = shell_execute(args, &(vals), paths); // ”;”　で区切られた各コマンドを実行する関数。
		if (!state)
			break;
		cmd_num--;
		if (cmd_num)
			args = &args[semi_co_place + 1];
	}
	return (state);
}

/*
 ** コマンドの実行の前に、入力取得ー＞ エスケープの処理 -> セミコロンによるコマンド分割を行う。
*/

int		commnad_loop(t_edlist vals, char **paths)
{
	int		state;
	char	*line;
	char	**args;
	int		cmd_num;

	state = 1;
	while (state)
	{
		if (!read_command(&line)) //get_next_lineでコマンドラインの入力取得。
			continue ;
		line = preparation_for_escape(line); //クオートで囲まれた文字列に対して、エスケープさせる必要のある文字にunprintable を挿入
											// スペースは 1, $ は 2 にしてある。
									// ここで、シングルクオートの場合のみ、'$' を unprintable に変えておく。
		if (!line)
			continue ;
		args = ft_split(line, ' '); //スペースごとにコマンドを分割。
		if (!args)
		{
			free(line);
			return (0);
		}
		fix_args(args, 1, ' ');// 非表示文字 1 が入ってる部分をスペースに置き換える。
		cmd_num = count_commands(args); //ここで何個コマンド列が ';' で区切られているか数える。
		state = exec_each_command(vals, paths, args, cmd_num); //この関数で ; で区切られた各コマンドを実行していく。
		free_all(args, line);
	}
	return (1);
}

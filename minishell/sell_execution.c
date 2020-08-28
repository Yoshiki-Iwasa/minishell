/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sell_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 07:47:02 by yiwasa            #+#    #+#             */
/*   Updated: 2020/08/28 09:36:33 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** パイプの有無を判断して条件わけをしている。
*/

int		shell_execute(char **args, t_edlist *vals, char **paths)
{
	int pipe_count;
	int	rv;

	// リダイレクトの部分がnull になってしまっているのが問題。
	// args[1] = "2";
	pipe_count = count_pipe(args); // パイプの中にリダイレクトがあるとカウントされない。これは問題だ。
	// args[1] = NULL;
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
		else if (rv == 100)//exit の場合。
			return (0);
	}
	if (pipe_count > 0)
		yes_pipe(args, vals, paths, pipe_count);
	return (1);
}

/*
 ** ${KEY} -> $KEY と変換する関数。
*/

// int	erase_bracket_for_doller_variable(char **args)
// {
// 	int i;

// 	i = 0;
// 	while (args[i])
// 	{
// 		if (args[i][0] == '$' && args[i][1] == '{')
// 		{
// 			if (args[i][ft_strlen(args[i]) - 1] != '}')
// 				return (0);
// 		}
// 		i++;
// 	}
// }

// /*
//  **
// */

// void	chage_dollor_val_space(char **args)
// {
// 	int i;
// 	char *tmp;

// 	i = 0;
// 	while (args[i])
// 	{
// 		if (args[i][0] == '$')
// 		{
// 			tmp = args[i];
// 			args[i] = ft_strdup("");
// 			free(tmp);
// 		}
// 		i++;
// 	}
// }

/*
 ** 一個以上のコマンドを順に実行するコマンド。
*/

int		exec_each_command(t_edlist vals, char **paths, char **args, int cmd_num)
{
	int		state;
	int		semi_co_place;

	while(cmd_num)
	{
		change_semicon_null(args, &semi_co_place);//セミコロンがどこにあるかsemi_co_place に格納。
		// ここ以降でメモリリークが発生する可能性あり。
		// translate_dollor_valiable(args, (vals.d_val), vals.e_val);
		// erase_bracket_for_dollor__variable(args);
		if(!translate_dollor_valiable(args, (vals.d_val), vals.e_val)) // ここで$ 変数の格納を行なっている
		{
			cmd_num--;
			if (cmd_num)
				args = &args[semi_co_place + 1];
			continue ;
		}
		// chage_dollor_val_space(args);//translate_dollor_valiable を抜けてなお$がついてるやつは潰す。

		fix_args(args, 2, '$');
		//このリダイレクトの処理は、パイプで区切られたコマンド毎に行うべき。
		// in_out = deal_redirection(args, &fd); //ここでファイルディスクリプターを書き換えて、処理が終わったらクローズして、正しい奴に戻してあげる。
		state = shell_execute(args, &(vals), paths); // <- この先でパイプの処理する。
		if (!state)
			break;
		cmd_num--;
		if (cmd_num)
			args = &args[semi_co_place + 1];
		// recover_stdinout(in_out, &fd, &stdin_fd, &stdout_fd);
	}
	return (state);
}

/*
 ** コマンドの実行を繰り替えす関数。preparation_for_escapeのなかでline のfreeは完了
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
		if (!read_command(&line))
			continue ;
		line = preparation_for_escape(line);// ’＄’もエスケープに加える必要あり。
		// ここで、シングルクオートの場合のみ、'$' を unprintable に変えておく。
		if (!line)
			continue ;
		args = ft_split(line, ' '); // args が死んだ時の処理必要
		if (!args)
		{
			free(line);
			return (0);
		}
		fix_args(args, 1, ' ');// 非表示文字が入ってる部分をスペースに置き換える。
		cmd_num = count_commands(args); //ここで何個コマンド列が;で区切られているか数える。
		state = exec_each_command(vals, paths, args, cmd_num);
		free_all(args, line);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sell_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 07:47:02 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/02 11:09:00 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** 各コマンドを実行する前にパイプの有無を見て処理を変える関数。
*/

int		shell_execute(char **args, t_edlist *vals, char **paths)
{
	int pipe_count; //パイプの個数。
	int	rv; //コマンド実行時の返り値を取得。

	pipe_count = count_pipe(args);
	if (pipe_count == 0)
	{
		rv = no_pipe(args, vals, paths); //ここの返り値を見て、成功したら１、失敗したら０
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
	else
	{
		rv = yes_pipe(args, vals, paths, pipe_count);
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
 ** paths に新しいパスを追加する関数。
*/

char	**add_new_path(char *new_path, char **paths)
{
	int str_num;
	char **new_paths;
	int i;

	i = 0;
	while(paths[i])
		i++;
	str_num = i;
	new_paths = malloc(sizeof(char *) * (i + 2));// 新しいpath と NULL分。
	i = 0;
	while (paths[i])
	{
		new_paths[i] = ft_strdup(paths[i]);
		i++;
	}
	new_paths[i] = ft_strdup(new_path);
	i++;
	new_paths[i] = NULL;
	return (new_paths);
}

/*
 ** 文字列配列を複製する関数。
*/

char	**ft_strsdup(char **args)
{
	int i;
	char **new_args;

	i = 0;
	while (args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (args[i])
	{
		new_args[i] = ft_strdup(args[i]);
		i++;
	}
	new_args[i] = NULL;
	return (new_args);
}

/*
 ** arg[0]が "." または、 "/" で始まっていたら、paths に相対or 絶対パスを追加。そして、arg[0] をパスなしの実行ファイル名に変える。
*/

char	**add_paths_and_change_arg0(char **argZero, char **paths)
{
	int i;
	char *execFile_ptr;
	char *new_path;

	i = 0;
	if (((*argZero)[0] == '.' || (*argZero)[0] == '/' ) && (*argZero)[1] != '\0')
	{
		i = ft_strlen(*argZero);
		while (i >= 0)
		{
			if ((*argZero)[i] == '/') //パスとして最後のスラッシュを探している。
			{
				execFile_ptr = ft_strdup(&(*argZero)[i + 1]);
				new_path = ft_substr(*argZero, 0, i);// スラッシュの一個手前まで取ってくる。
				free(*argZero);
				paths = add_new_path(new_path, paths);
				*argZero = execFile_ptr;// arg0 を実行ファイル名のみに。
				free(new_path);
				break ;
			}
			i--;
		}
		return (paths);
	}
	else
	{
		return (ft_strsdup(paths));
	}

}

/*
 ** 一個以上のコマンドを順に実行するコマンド。
*/

int		exec_each_command(t_edlist vals, char **paths, char **args, int cmd_num)
{
	int		state;
	int		semi_co_place;
	// char	**tmp;

	// tmp = paths;
	while(cmd_num)
	{
		change_semicon_null(args, &semi_co_place);//セミコロンがどこにあるかsemi_co_place に格納。同時に、セミコロンがあった場所はNULLにしてある。
		if(!translate_dollor_valiable(args, (vals.d_val), vals.e_val)) // ここで、$変数を変換している。
		{
			cmd_num--;
			if (cmd_num)
				args = &args[semi_co_place + 1];
			continue ;
		}
		fix_args(args, 2, '$'); //エスケープされていた'$'はここで復帰させる。
		// paths = add_paths_and_change_arg0(&args[0], paths);// 新しいパスを追加。(相対パスまたは絶対パスによるファイル実行のための処理)
		state = shell_execute(args, &(vals), paths); // ”;”　で区切られた各コマンドを実行する関数。
		// free_all(paths, 0);
		// paths = tmp;
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
		if (!read_command(&line, &state)) //get_next_lineでコマンドラインの入力取得。
			continue ;
		line = preparation_for_escape(line); //クオートで囲まれた文字列に対して、エスケープさせる必要のある文字にunprintable を挿入
											// ' 'は 1, '$' は 2 にしてある。
									// ここで、シングルクオートの場合のみ、'$' を unprintable に変えておく。
		if (!line)
			continue ;
		args = ft_split(line, ' '); //スペースごとにコマンドを分割
		if (args == NULL || args[0] == NULL)
		{
			free(line);
			continue ;
		}
		fix_args(args, 1, ' ');// 非表示文字 1 が入ってる部分をスペースに置き換える。
		fix_args(args, 4, '\0');
		cmd_num = count_commands(args); //ここで何個コマンド列が ';' で区切られているか数える。
		state = exec_each_command(vals, paths, args, cmd_num); //この関数で ; で区切られた各コマンドを実行していく。
		free_all(args, line);
	}
	return (1);
}

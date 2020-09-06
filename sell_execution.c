/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sell_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 07:47:02 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/07 06:54:32 by yiwasa           ###   ########.fr       */
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
 ** paths に新しいパスを追加する関数。
*/

char	**add_new_path(char *new_path, char **paths)
{
	char **new_paths;
	int i;

	i = 0;
	while(paths[i])
		i++;
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
	free_all(paths, 0);
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
		free_all(paths, 0);
		i = ft_strlen(*argZero);
		while (i >= 0)
		{
			if ((*argZero)[i] == '/') //パスとして最後のスラッシュを探している。
			{
				execFile_ptr = ft_strdup(&(*argZero)[i + 1]);//	実行ファイル名前の部分。
				new_path = ft_substr(*argZero, 0, i);// スラッシュの一個手前まで取ってくる。
				free(*argZero);
				paths = malloc(sizeof(char*) * 2);
				paths[0] = ft_strdup(new_path);
				paths[1] = NULL;
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
		return (add_new_path("/", paths));
	}

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

/*
 ** リダイレクトの文法をチェックする関数。
*/

int		check_syntax(char **args)
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

int		launch_shell(t_edlist vals, char *line)
{
	int		state;
	char	**args;
	int		cmd_num;
	int		arglen;
	int		esc_flag;

	esc_flag = 0;
		line = preparation_for_escape(line); //クオートで囲まれた文字列に対して、エスケープさせる必要のある文字にunprintable 文字を挿入
											// ' 'は 1, '$' は 2 にしてある。
									//加えて、バックスラッシュの
									// ここで、シングルクオートの場合のみ、'$' を unprintable に変えておく。
		if (!line)
			return (1);
		args = ft_split(line, ' '); //スペースごとにコマンドを分割
		arglen = count_strs(args); //後にargs をfree するために必要。


		if (args == NULL || args[0] == NULL)
		{
			free(line);
			return (1);
		}
		if (!(check_syntax(args)))// リダイレクトのsyntax をチェックしてる。
		{
			//ここに入るのは $ pwd > みたいな時。
			ft_putstr_fd("bash: syntax error near unexpected token `newline\'\n", 2);
			free_args(args, line, arglen);
			return (1) ;
		}
		// ここ以降は、エスケープさせてた文字の一部を復帰させる。
		fix_args(args, 1, ' ');// 非表示文字 1 が入ってる部分をスペースに置き換える。
		fix_args(args, 4, '\0');
		fix_args(args, 6, '2');
		fix_args(args, 9, ' ');
		if(!(cmd_num = count_commands(args))) //ここで何個コマンド列が ';' で区切られているか数える。
		{
			// ここに入ってくるのは、 $ pwd ;; pwd とか $ ; のとき。
			update_val(&vals.d_val, "?=258");
			free_args(args, line, arglen);
			return (1) ;
		}
		state = exec_each_command(vals, args, cmd_num); //この関数で ; で区切られた各コマンドを実行していく。
		free_args(args, line, arglen);
		return (state);
}

/*
 ** コマンドの実行の前に、入力取得ー＞ エスケープの処理 -> セミコロンによるコマンド分割を行う。
*/

int		commnad_loop(t_edlist vals)
{
	int		state;
	char	*line;

	state = 1;
	while (state != 0)
	{
		ft_putstr_fd("minishell$ ", 1);
			if (!read_command(&line, &state)) //get_next_lineでコマンドラインの入力取得。
			continue ;
		state = launch_shell(vals, line);
	}
	return (1);
}

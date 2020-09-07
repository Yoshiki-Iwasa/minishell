#include "minishell.h"


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
		if (!(check_redirect_syntax(args)))// リダイレクトのsyntax をチェックしてる。
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

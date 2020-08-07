#include "minishell.h"

/*
	get_next_line でコマンドラインを読み取ってくる
	次に、ft_split でコマンドと引数にコマンドラインを分解（エスケープの処理を入れる必要あり）
	fork() を使ってプロセスを新たに作る必要あり。プロセスを分岐させて各実行ファイルを呼び出す
	unix は 環境変数PATH を使ってコマンド名前がある実行ファイルを探しにいっている。

*/
/*
	シェルコマンドを実行するための関数。組み込み以外のがきたらプロセス分けて探しにいく
	いずれは全部の引数をargsに統一したい。関数間で変数名が変わると可読性がめちゃ下がる。
*/
int		shell_execute(char **args, t_list **e_val, t_list **d_val, char **paths)
{
		if (!ft_strncmp(args[0], "exit", 4))
			return(command_exit());
		else if (!ft_strncmp(args[0], "pwd", 3))
			return(command_pwd());
		else if (!ft_strncmp(args[0], "cd", 2))
			return(command_cd(args[1], e_val));
		else if (!ft_strncmp(args[0], "env", 3))
			return (command_env(e_val));
		else if (!ft_strncmp(args[0], "d_env", 4))
			return (command_env(d_val));
		else if(!ft_strncmp(args[0], "echo", 4))
			return (command_echo(args));
		else if(!ft_strncmp(args[0], "export", 6))
			return (command_export(args, e_val));
		else if(!ft_strncmp(args[0], "unset", 6))
			return (command_unset(&args[1], *e_val, *d_val));
		else if(check_if_key_value(args[0]))
			return (update_val(d_val, args[0]));
		else
			return (exec_shell_command(args, *e_val, paths));
		return (1);
}

/*
	毎回のコマンドの実行の後かく要素をfreeするために使う。
*/

void	free_all(char **args, char *line)
{
	int i = 0;
	free(line);

	while(!args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

/*
	lstdelone に渡すために仮置きしてる
	本来こいつはfreeであるべきなんだ！！！！
*/

void	del_str(void *str)
{
	str = 0;
}

/*
	クオーテーションで囲まれた文字列のスペースを非表示文字にする。
*/

void	insert_unprintable(char *line)
{
	int		i;

	i = 0;
	while(line[i] != '\0')
	{
		if (line[i] == '"' || line[i] == 39)
		{
			i++;
			while(line[i] != '"' || line[i] == 39)
			{
				if(line[i] == ' ')
					line[i] = 1;
				else if (line[i] == '\0')
					break;
				i++;
			}
		}
		i++;
	}
}

/*
	クオーテーションで囲まれた文字列のスペースを非表示文字にしてクオートを削除
*/

char	*preparation_for_escape(char *line)
{
	int		i;
	int		j;
	char	*new_line;

	insert_unprintable(line);

	new_line = malloc(ft_strlen(line) + 1);
	if (!new_line)
		return (0);
	i = 0;
	j = 0;
	while(line[i] != '\0')
	{
		if(line[i] == '"' || line[i] == 39)
		{
			i++;
			continue;
		}
		new_line[j] = line[i];
		i++;
		j++;
	}
	free(line);
	new_line[j] = '\0';
	return (new_line);
}

/*
	argsに含まれている非表示文字を空白に変える関数
*/

void	fix_args(char **args)
{
	int i;
	int j;

	i = 0;
	while(args[i] != NULL)
	{
		j = 0;
		while(args[i][j] != '\0')
		{
			if (args[i][j] == 1)
				args[i][j] = ' ';
			j++;
		}
		i++;
	}
}

void	prompt_loop(char **envp)
{
	int		state;
	char	*line;
	char	**args;
	t_list	*d_val;
	t_list	*e_val;
	char	**paths;
	int		cmd_num;
	int		semi_co_place;
	char	**tmp;

	errno = 0;
	state = 1;
	d_val = NULL;
	init_e_val_list(&e_val, envp);
	paths = get_PATH(e_val);
	while (state)
	{
		ft_putstr_fd("yiwasa$ ", 1);
		get_next_line(0, &line);//コマンドラインを生で取ってくる
		if (*line == '\0')
			continue ;
		line = preparation_for_escape(line);
		args = ft_split(line, ' ');
		fix_args(args);
		tmp = args;
		cmd_num = count_commands(args); //ここで何個コマンドがあるか数える。
		while(cmd_num)
		{
			semi_co_place = find_semi_co(args);
			free(args[semi_co_place]);
			args[semi_co_place] = NULL;
			if(!trans_valiable(args, d_val))
			{
				free_all(args, line);
				continue ;
			}
			state = shell_execute(args, &e_val, &d_val, paths);
			cmd_num--;
			if (cmd_num)
				args = &args[semi_co_place + 1];

		}
		free_all(tmp, line);
	}
	ft_lstclear(&e_val, del_str);
}

int main(int argc, char **argv, char **envp)
{
	prompt_loop(envp);
	return EXIT_SUCCESS;
}

#include "minishell.h"

/*
	シェルコマンドを実行するための関数。組み込み以外のがきたらプロセス分けて探しにいく
	いずれは全部の引数をargsに統一したい。関数間で変数名が変わると可読性がめちゃ下がる。
	ここで、パイプが来た場合はパイプの前後で処理を分けて実行する必要がある。プロセスを分けてあげなければ。
*/
int		shell_execute(char **args, t_edlist *vals, char **paths)
{
	int pipe_count;
	int	rv;

	pipe_count = count_pipe(args);
	if (pipe_count == 0)
	{
		rv = no_pipe(args, &(vals->e_val), &(vals->d_val), paths); //ここの返り値を見て、成功したら１、失敗したら０
		if (rv == 1)
		{
			update_val(&(vals->d_val), "?=0");
		}
		else if (rv == 0)
		{
			update_val(&(vals->d_val), "?=1");
		}
		else if (rv == 100)//exit の場合。
		{
			return (0);
		}
	}
	if (pipe_count > 0)
	{
		yes_pipe(args, vals, paths, pipe_count);
	}
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

*/

void	change_semicon_null(char **args, int *semi_co_place)
{

	*semi_co_place = find_semi_co(args);
	free(args[*semi_co_place]);
	args[*semi_co_place] = NULL; // args をあとでまとめてfree するためにNULL で　；　を埋めてる
}

/*
 ** 一回dup2 
*/

void	recover_stdinout(int in_out, int *fd, int *stdin_fd, int *stdout_fd)
{
	int close_rv;
	int dup2_rv;
	if(in_out == 0)
	{
		close(0);
		close(*fd);
		dup2(*stdin_fd, 0);
	}
	if(in_out == 1)
	{
		close_rv = close(1);
		dup2_rv = dup2(*stdout_fd, 1);
	}
}

void	escape_fds(int *stdin_fd, int *stdout_fd)
{
	*stdin_fd = dup(0);
	*stdout_fd = dup(1);
}

/*
 **  コマンドラインを読んでくる関数。
*/

int		read_command(char **line)
{
	int gnl_rv;

	ft_putstr_fd("minishell$ ", 1);
	gnl_rv = get_next_line(0, line);//コマンドラインを生で取ってくる
	if (**line == '\0' && gnl_rv == 1 )
		return (0);
	if (gnl_rv == 0)
	{
		write(1, "\n",1);
		exit(0);
		return (0);
	}
	if (gnl_rv == -1) // gnl が失敗したときは、もう一度コマンドプロンプトに戻る。
	{
		write(1, "GNL Fail\n",9);
		exit(0);
		return (0);
	}
	return (1);
}

/*
 ** 一個以上のコマンドを順に実行するコマンド。
*/

int		exec_each_command(t_edlist vals, char **paths, char **args, int cmd_num)
{
	int		state;
	int		semi_co_place;
	int		fd;
	int		stdin_fd;
	int		stdout_fd;
	int		in_out;

	while(cmd_num)
	{
		change_semicon_null(args, &semi_co_place);
		escape_fds(&stdin_fd, &stdout_fd);
		if(!trans_dollor_valiable(args, (vals.d_val), vals.e_val)) // ここで$ 変数の格納を行なっているが、= の直後に$が来てしまった場合に対応していないことが判明。
		{
			cmd_num--;
			if (cmd_num)
				args = &args[semi_co_place + 1];
			continue ;
		}
		in_out = deal_redirection(args, &fd); //ここでファイルディスクリプターを書き換えて、処理が終わったらクローズして、正しい奴に戻してあげる。
		state = shell_execute(args, &(vals), paths); // <- この先でパイプの処理する。
		cmd_num--;
		if (cmd_num)
			args = &args[semi_co_place + 1];
		recover_stdinout(in_out, &fd, &stdin_fd, &stdout_fd);
	}
	return (state);
}

/*
 ** コマンドの実行を繰り替えす関数。
*/

void	commnad_loop(t_edlist vals, char **paths)
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
		line = preparation_for_escape(line);
		args = ft_split(line, ' '); // args が死んだ時の処理必要
		fix_args(args);// 非表示文字が入ってる部分をスペースに置き換える。
		cmd_num = count_commands(args); //ここで何個コマンドがあるか数える。
		state = exec_each_command(vals, paths, args, cmd_num);
		free_all(args, line);
	}
}

/*
 ** シグナルの設定、環境変数をリスト構造に格納、
*/

void	shell_start(char **envp)
{
	t_edlist vals;
	char	**paths;
	
	vals.d_val = NULL;
	vals.e_val = NULL;
	setting_signal(); // シグナルハンドルが入っている。
	update_val(&(vals.d_val), "?=1");
	init_e_val_list(&(vals.e_val), envp); //envp に入っている環境変数達をリスト構造にしてリストe_valを作る。
	paths = get_PATH(vals.e_val); // 環境変数の中からPATH を回収することで、buil in 出ない関数が呼ばれた時も対応できるように。
	commnad_loop(vals, paths);
	ft_lstclear(&(vals.e_val), del_str); //この処理の後、args, e_val をfreeする必要あり。
}

int main(int argc, char **argv, char **envp)
{
	shell_start(envp);
	return EXIT_SUCCESS;
}

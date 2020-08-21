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
	ここで、パイプが来た場合はパイプの前後で処理を分けて実行する必要がある。プロセスを分けてあげなければ。
*/
int		shell_execute(char **args, t_edlist *vals, char **paths)
{
	int pipe_count;

	pipe_count = count_pipe(args);
	if (pipe_count == 0)
	{
		no_pipe(args, &(vals->e_val), &(vals->d_val), paths);
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

void	deal_semicon(char ***args)
{
	int semi_co_place;

	semi_co_place = find_semi_co(*args);
	free((*args)[semi_co_place]);
	(*args)[semi_co_place] = NULL; // args をあとでまとめてfree するためにNULL で　；　を埋めてる
}

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
		close_rv = close(*fd);
		dup2_rv = dup2(*stdout_fd, 1);
	}
}

void	escape_fds(int *stdin_fd, int *stdout_fd)
{
	*stdin_fd = dup(0);
	*stdout_fd = dup(1);
}

void	prompt_loop(char **envp) //パイプの実装のためには、line を args に分ける段階で分岐させて
{
	int		state;
	char	*line;
	char	**args;
	t_edlist vals;
	t_list	*d_val;
	t_list	*e_val;
	char	**paths;
	int		cmd_num;
	int		semi_co_place;
	char	**tmp;
	int		fd;
	int		stdin_fd;
	int		stdout_fd;
	int		in_out;
	int		pipe_place;
	int		exec_num;
	int		gnl_rv;

	setting_signal();
	escape_fds(&stdin_fd, &stdout_fd);
	errno = 0;
	state = 1;
	d_val = NULL;
	init_e_val_list(&(vals.e_val), envp); //envp に入っている環境変数達をリスト構造にしてリストe_valを作る。
	paths = get_PATH(vals.e_val); // 環境変数の中からPATH を回収することで、buil in 出ない関数が呼ばれた時も対応できるように。
	while (state)
	{
		ft_putstr_fd("yiwasa$ ", 1);
		gnl_rv = get_next_line(0, &line);//コマンドラインを生で取ってくる
		if (*line == '\0' && gnl_rv == 1)
			continue ;
		if (gnl_rv == 0)
		{

			write(1, "\n",1);
			exit(0);
			continue ;
		}
		if (gnl_rv == -1) // gnl が失敗したときは、e_val と path を解放する必要あり。path は文字列の配列。
		{}
		line = preparation_for_escape(line);
		args = ft_split(line, ' '); // args が死んだ時の処理必要
		fix_args(args);// 非表示文字が入ってる部分をスペースに置き換える。
		tmp = args;
		cmd_num = count_commands(args); //ここで何個コマンドがあるか数える。
		while(cmd_num) // これ以降で、パイプの数を数えて実行してやる。
		{
			// deal_semicon(&args); //セミコロンをNULLに換えてる。
			semi_co_place = find_semi_co(args);
			free(args[semi_co_place]);
			args[semi_co_place] = NULL;
			if(!trans_valiable(args, (vals.d_val))) // ここで$ 変数の格納を行なっているが、= の直後に$が来てしまった場合に対応していないことが判明。
			{
				free_all(args, line);
				continue ;
			}
			in_out = deal_redirection(args, &fd); //ここでファイルディスクリプターを書き換えて、処理が終わったらクローズして、正しい奴に戻してあげる。
			state = shell_execute(args, &(vals), paths); // <- この先でパイプの処理する。
			cmd_num--;
			if (cmd_num)
				args = &args[semi_co_place + 1];
			recover_stdinout(in_out, &fd, &stdin_fd, &stdout_fd);
		}
		free_all(tmp, line);
	}
	ft_lstclear(&(vals.e_val), del_str); //この処理の後、args, e_val をfreeする必要あり。
}

int main(int argc, char **argv, char **envp)
{
	prompt_loop(envp);
	return EXIT_SUCCESS;
}

#include "minishell.h"

/*
	空白を判定する
*/

int		ft_isspace(char c)
{
	if (c == '\n' || c == '\t' || c == '\v')
		return (1);
	if (c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

/*
	arg が　key=valu　の形をしているか判定する関数
*/

int		check_if_key_value(char *arg)
{
	while(ft_isspace(*arg))
		arg++;
	while(*arg != '=' && arg != '\0')
		arg++;
	if(arg == '\0')
		return (0);
	else
	{
		arg++;
		if (ft_isspace(*arg))
			return (0);
		else
			return (1);
	}
}

/*
	新しい要素をリストの一番後ろに追加する関数
*/

int		add_val(t_list *val, char *arg) //ただ加えるだけじゃなくて、更新もしないといけないか。
{
	t_list *new;

	new = ft_lstnew(arg);
	ft_lstadd_back(&val, new);
	return (1);
}

/*
	すでにあるkey=valueのvalue を変更する。
*/

int		update_val(t_list *val, char *arg)
{
	t_list *find;
	char *key;

	key = get_key(arg);
	find = search_entry(val, key);
	if (find != NULL)
		find->content = ft_strdup(arg);
	else
		add_val(val, ft_strdup(arg)); //lst_newで全てmallcする仕様に変えて、delにfreeを渡すように実装する必要あり。
	free(key);
	return (1);
}

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
int		shell_execute(char **args, t_list **e_val, t_list **d_val)
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
			return (update_val(*d_val, args[0]));
		// else if (!!ft_strcmp(args[0], "unset"))
		// 	return(command_unset(args, e_val))
		
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
*/

void	del_str(void *str)
{
	str = 0;
}

void	prompt_loop(char **envp)
{
	int state;
	char *line;
	char **args;
	t_list *d_val;
	t_list *e_val;
	t_list *find;
	
	errno = 0;
	state = 1;
	d_val = NULL;
	init_e_val_list(&e_val, envp);
	while (state)
	{
		ft_putstr_fd("yiwasa$ ", 1);
		get_next_line(0, &line);
		if (*line == '\0')
			continue ;
		args = ft_split(line, ' ');
		state = shell_execute(args, &e_val, &d_val);
		free_all(args, line);
	}
	ft_lstclear(&e_val, del_str);
}

int main(int argc, char **argv, char **envp)
{

	prompt_loop(envp);

	return EXIT_SUCCESS;
}

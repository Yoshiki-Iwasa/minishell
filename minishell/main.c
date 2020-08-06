#include "minishell.h"
//とりあえず、

int		ft_isspace(char c)
{
	if (c == '\n' || c == '\t' || c == '\v')
		return (1);
	if (c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

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

char	*get_key(char *arg)
{
	int		i;
	int		key_len;
	char	*key;

	key_len = 0;
	while (arg[key_len] != '=')
		key_len++;
	key = malloc(key_len + 1);
	i = 0;
	while (i < key_len)
	{
		key[i] = arg[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

int		add_val(t_list **val, char *arg) //ただ加えるだけじゃなくて、更新もしないといけないか。
{
	t_list *new;

	new = ft_lstnew(arg);
	ft_lstadd_back(val, new);
	return (1);
}

int		update_val(t_list **val, char *arg)
{
	t_list *find;
	char *key;

	key = get_key(arg);
	find = serch_entry(val, key);
	if (find != NULL)
	{
		printf("更新前　：%s\n\n",find->content);
		find->content = arg;
		printf("===========kitemasu===================\n");
		printf("更新後　：%s\n", find->content);

	}
	else
		add_val(val, arg);
	free(key);
	return (1);
}


int		command_export(char **args, t_list **e_val)
{
	update_val(e_val, args[1]);
	return (1);
}

/*
	get_next_line でコマンドラインを読み取ってくる
	次に、ft_split でコマンドと引数にコマンドラインを分解（エスケープの処理を入れる必要あり）
	fork() を使ってプロセスを新たに作る必要あり。プロセスを分岐させて各実行ファイルを呼び出す
	unix は 環境変数PATH を使ってコマンド名前がある実行ファイルを探しにいっている。
	
*/
/*
	いずれは全部の引数をargsに統一したい。関数間で変数名が変わると可読性がめちゃ下がる。
*/
int		shell_execute(char **args, t_list **e_val, t_list **d_val)
{
		if (!ft_strcmp(args[0], "exit"))
			return(command_exit());
		else if (!ft_strcmp(args[0], "pwd"))
			return(command_pwd());
		else if (!ft_strcmp(args[0], "cd"))
			return(command_cd(args[1], e_val));
		else if (!ft_strcmp(args[0], "env"))
			return (command_env(e_val));
		else if(!ft_strcmp(args[0], "echo"))
			return (command_echo(args));
		else if(!ft_strcmp(args[0], "export"))
			return (command_export(args, e_val));
		else if(check_if_key_value(args[0]))
			return (update_val(d_val, args[0]));
		// else if (!!ft_strcmp(args[0], "unset"))
		// 	return(command_unset(args, e_val))
		
		return (1);
}

void	free_all(char **args, char *line)
{
	free(line);

	while(*args)
	{
		free(*args);
		args++;
	}
}

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
	// update_val(&e_val, "DDD=1234");
	// find = serch_entry(&e_val, "LLLLL");
	// if (find != NULL)
	// {
	// 	find->content = "KKK=dekiteru";
	// 	// printf("===========kitemasu===================\n");
	// 	// printf("%s\n", find->content);
	// 	// printf("%s\n", find->next->content);
	// }
	// else
	// 	add_val(&e_val, "TSUIKADAYO!");
	// ft_lstiter(e_val, ft_putendl);
	// exit(0);
	while (state)
	{
		// ft_lstiter(e_val, ft_putendl);
		ft_lstiter(d_val, ft_putendl);
		ft_putstr_fd("yiwasa$ ", 1);
		get_next_line(0, &line);
		if (*line == '\0')
			continue ;
		args = ft_split(line, ' ');
		state = shell_execute(args, &e_val, &d_val);
		free_all(args, line);
	}
	ft_lstclear(&e_val, del_str);
	ft_lstiter(d_val, ft_putendl);
}

int main(int argc, char **argv, char **envp)
{

	prompt_loop(envp);

	return EXIT_SUCCESS;
}

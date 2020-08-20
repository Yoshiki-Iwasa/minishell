/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 13:27:58 by yiwasa            #+#    #+#             */
/*   Updated: 2020/08/20 09:28:50 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
	> < >> を見て実行数が何個あるか数える関数。
*/

int		count_execs(char **args)
{
	int		i;
	int		count;

	i = 0;
	count = 1; // コマンドの先頭にセミコロンがきた場合を排除
	while(args[i])
	{
		if(!ft_strcmp(args[i], ";") && args[i + 1] != NULL && ft_strcmp(args[i + 1], ";"))
			count++;
		i++;
	}
	return (count);
}


/*
	"｜"が文字列配列の何番目に入っているかを数えるための関数。
*/

int		find_pipe(char	**args)
{
	int num;

	num = 0;
	while(ft_strcmp(args[num], "|") && args[num] != NULL)
	{
		num++;
	}
	return (num);
}

/**
 * "|" が何個入っているか数える関数
 * */

int		count_pipe(char **args)
{
	int		i;
	int		count;

	i = 0;
	count = 0; // コマンドの先頭にセミコロンがきた場合を排除
	while(args[i])
	{
		if(!ft_strcmp(args[i], "|"))
			count++;
		i++;
	}
	return (count);
}


/**
 * pipeが一個だけの時はforkをする必要がないので、別の処理にしている。
*/

int		no_pipe(char **args, t_list **e_val, t_list **d_val, char **paths)
{
	if (!ft_strncmp(args[0], "exit", 5))
		return(command_exit());
	else if (!ft_strncmp(args[0], "pwd", 4))
		return(command_pwd());
	else if (!ft_strncmp(args[0], "cd", 3))
		return(command_cd(args[1], e_val));
	else if (!ft_strncmp(args[0], "env", 4))
		return (command_env(e_val));
	else if (!ft_strncmp(args[0], "d_env", 5))
		return (command_env(d_val));
	else if(!ft_strncmp(args[0], "echo", 5))
		return (command_echo(args));
	else if(!ft_strncmp(args[0], "export", 7))
		return (command_export(args, e_val));
	else if(!ft_strncmp(args[0], "unset", 7))
		return (command_unset(&args[1], *e_val, *d_val));
	else if(check_if_key_value(args[0]))
		return (update_val(d_val, args[0]));
	else
		return (exec_shell_command(args, *e_val, paths));
}

// forkした後の処理は、子プロセス→親プロセスなので子プロセスの標準出力を
// pipe_fd[1]に、親プロセスの標準入力をpipe_fd[0]にすればとりあえず1本目のぴぷは対応できる。

/**
 * 子プロセス。入り口のpipe_fd[0]を塞ぐ。
 * その上で、標準出力をpipe_fd[1]の入り口に設定する。
 * 
*/

void	do_child(char **args, t_edlist *vals, char **paths, int *pipe_fd)
{
	int stdout_fd;

	stdout_fd = dup(1); //標準出力のfdを一旦退避
	close(pipe_fd[0]); //子プロセスの入り口を塞ぐ
	close(1); //標準出力を塞ぐ
	dup2(pipe_fd[1], 1); //１番を子プロセスの出口に設定。
	close(pipe_fd[1]);	//元々の出口を塞ぐ。
	no_pipe(args, &(vals->e_val), &(vals->d_val), paths);
	dup2(stdout_fd, 1);// 標準出力を1 番に復帰
	exit(0);
}


/**
 * 親プロセス。出口のpipe_fd[1]を塞ぐ。
 * その上で、標準入力をpipe_fd[0]の出口に設定する。
 * 
*/

void	do_parent(char **args, t_edlist *vals, char **paths, int *pipe_fd)
{
	int stdin_fd;

	stdin_fd = dup(0); //標準入力のfdを一旦退避
	close(pipe_fd[1]); // 親プロセスの出口を塞ぐ。
	close(0); //標準入力を塞ぐ
	dup2(pipe_fd[0], 0); //0番を親プロセスの入口に設定。
	close(pipe_fd[0]);	//元々の出口を塞ぐ。
	no_pipe(args, &(vals->e_val), &(vals->d_val), paths);
	dup2(stdin_fd, 0);// 標準入力を0 番に復帰
	
}

/*args の pipe が入ってるところをnull にしてる。*/

void	divide_args(char **base, char ***args_1, char ***args_2)
{
	int i;

	i = 0;
	*args_1 = &base[0];
	while (base[i])
	{
		if (!ft_strcmp(base[i], "|"))
		{
			base[i] = NULL;
			*args_2 = &base[i + 1];
		}
		i++;
	}
}

/*
	args_array に、args のパイプが入ってるとこの次のコマンドのアドレスを渡す。
	そうすると、コマンド群の配列ができる。args は、malloc してできた配列で、必ずしもメモリが一列に並んでいるとは限らない？
*/ 

void	args_into_array(char **args, char ****args_array, int pipe_num)
{
	int i;
	int j;

	*args_array = malloc(sizeof(char **) * (pipe_num + 2));
	(*args_array)[pipe_num + 1] = NULL;
	(*args_array)[0] = &args[0];
	i = 0;
	j = 1;
	while (args[i])
	{
		if(!ft_strcmp(args[i], "|"))
		{
			(*args_array)[j] = &args[i + 1];
			args[i] = NULL;
			j++;
		}
		i++;
	}
	return ;
}

/*
	パイプでつながれたコマンドの実行を再帰的に行う関数
*/
void	exec_pipes(int i, char ***args_array, int com_num, t_edlist *vals, char **paths)
{
	pid_t ret;
	int pp[2] = {};
	if (i == com_num - 1)
	{
		// 左端なら単に実行
		// execvp(cmds[0][0], cmds[0]);
		no_pipe(args_array[0], &(vals->e_val), &(vals->d_val), paths);
		exit(0);
	}
	else
	{
		// 左端以外ならpipeしてforkして親が実行、子が再帰
		pipe(pp);
		ret = fork();
		if (ret == 0)
		{
			// 子プロセスならパイプをstdoutにdup2してdopipes(i+1)で再帰し、
			// 次のforkで親になった側が右からi+1番目のコマンドを実行
			close(pp[0]);
			dup2(pp[1], 1);
			close(pp[1]);
			exec_pipes(i + 1, args_array, com_num, vals, paths);
			exit(0);
		}
		else
		{
				// 子プロセスの実行を待った後に
				// 親プロセスならパイプをstdinにdup2して、
				// 右からi番目のコマンドを実行
				wait(NULL);
				close(pp[1]);
				dup2(pp[0], 0);
				close(pp[0]);
				no_pipe(args_array[com_num -i -1], &(vals->e_val), &(vals->d_val), paths);
				exit(0);
		}
	}
}

/*
	コマンドにパイプが含まれていた場合の関数。fork して子プロセスを作り上げる。
	ここから、再帰関数を使って、コマンドの右から順に実行させる。
*/


int		yes_pipe(char **args, t_edlist *vals, char **paths, int pipe_count)
{
	int		i;
	char	**envp;
	int		pipe_fd[2];
	int		status;
	int		pid;
	char	**args_1;
	char	**args_2;
	char	***args_array; // こいつ最終的にfreeする必要あり。
	int		pipe_num;

	pipe_num = count_pipe(args);
	envp = change_into_array(vals->e_val);
	args_into_array(args, &args_array, pipe_num);// ここまでで、args_array でコマンドを分割できた
	// divide_args(args, &args_1, &args_2);
	pid_t ret;

	ret = fork();
	if (ret == 0)
	{
		exec_pipes(0, args_array, pipe_num + 1, vals, paths);
	}
	else
		wait(&status);
	printf("status = %d\n", status);
	return (0);
}
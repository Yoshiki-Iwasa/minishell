/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 13:27:58 by yiwasa            #+#    #+#             */
/*   Updated: 2020/08/31 10:40:32 by yiwasa           ###   ########.fr       */
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
		if (!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], "<") || !ft_strcmp(args[i], ">>"))
		{
			// args[i] = NULL;
			i++;
		}
		if(!ft_strcmp(args[i], "|"))
			count++;
		i++;
	}
	return (count);
}


/*
 ** コマンドを実行する関数。コマンド実行の前に標準入出力のfd を逃して、リダイレクトの処理をしてから実行。
*/

int		no_pipe(char **args, t_edlist *vals, char **paths)
{
	int fd;
	int in_out;
	int stdin_fd;
	int stdout_fd;
	int stderror_fd;
	int rv;

	escape_fds(&stdin_fd, &stdout_fd, &stderror_fd); //リダイレクトのあとに標準入出力を復帰させるためにエスケープさせる。
	in_out = deal_redirection(args, &fd);//リダイレクトの処理を入れている。
	if (!ft_strncmp(args[0], "exit", 5))
		rv = (command_exit());
	else if (!ft_strncmp(args[0], "pwd", 4))
		rv = (command_pwd());
	else if (!ft_strncmp(args[0], "cd", 3))
		rv = (command_cd(args[1], &(vals->e_val)));
	else if (!ft_strncmp(args[0], "env", 4))
		rv = (command_env(&(vals->e_val)));
	else if (!ft_strncmp(args[0], "d_env", 5))
		rv = (command_env((&vals->d_val)));
	else if(!ft_strncmp(args[0], "echo", 5))
		rv = (command_echo(args));
	else if(!ft_strncmp(args[0], "export", 7))
		rv = (command_export(args, vals));
	else if(!ft_strncmp(args[0], "unset", 7))
		rv = (command_unset(&args[1], vals->e_val, vals->d_val));// shell変数更新のための関数。
	else if(check_if_key_value(args[0]))
		rv = (update_val((&vals->d_val), args[0]));
	else
		rv = (exec_shell_command(args, vals->e_val, &(vals->d_val), paths));//build inではないコマンドが呼ばれるときに使われる。
	recover_stdinout(in_out, &fd, &stdin_fd, &stdout_fd, &stderror_fd);//標準入出力のfd を復帰させる。
	return (rv);
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
		no_pipe(args_array[0], vals, paths);
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
				no_pipe(args_array[com_num -i -1], vals, paths);
				exit(0);
		}
	}
}

/*
	コマンドにパイプが一個以上含まれていた場合の関数。fork して子プロセスを作り上げる。
	ここから、再帰関数を使って、コマンドの右から順に実行させる。
*/


int		yes_pipe(char **args, t_edlist *vals, char **paths, int pipe_count)
{
	char	**envp;
	int		status;
	char	***args_array; // こいつ最終的にfreeする必要あり。

	envp = change_into_array(vals->e_val); //環境変数リストを文字列に変換。
	args_into_array(args, &args_array, pipe_count);// ここまでで、args_array でコマンドをパイプごとに分割できた
	pid_t ret;

	ret = fork();
	if (ret == 0)
	{
		exec_pipes(0, args_array, pipe_count + 1, vals, paths); //一番右のコマンドを親として、右から左にコマンドを順次実行させる。
	}
	else
	{
		wait(&status);
	}
	return (0);
}

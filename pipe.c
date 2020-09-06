/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 13:27:58 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/06 11:41:20 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t g_ret;
int	  g_sig_count;

void	signel_pipe(int sig)
{
	if (g_ret != 0)
	{
		g_sig_count++;
		sig = kill(g_ret, SIGINT);
		if(!sig && g_sig_count == 1)
		{
			write(1, "\n", 1);
		}
	}
}

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
 ** シェル変数に使える文字列かどうかをチェック key に アンダーバー以外の特殊文字が入ってたらOUT
*/

int		check_key_str(char *arg)
{
	int i;

	i = 0;
	if (ft_isdigit(arg[0]))
	{
		return (0);
	}
	while (arg[i] != '\0' && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

/*
 ** TEST= pwd とか TEST = pwd みたいなのに対応
 ** TEST= pwd とか TEST =pwd ならイコールついてるやつを消す。
 ** TEST = pwd なら、"TEST: =: unexpected operator" 吐いて終了。<- これはむしするか、、、
 **
*/
char		**check_and_change_equal(char **args)
{
	int i;
	int j;
	char *arg;
	char **new_args;

	i = 0;
	j = 0;
	new_args = malloc(sizeof(char*) * (count_strs(args) + 1));
	while (args[i])
	{
		arg = args[i];
		if (args[i + 1] != NULL && ft_strlen(arg) != 1 && (arg[ft_strlen(arg) - 1] == '=' || arg[0] == '='))
		{
			i++;
			continue;
		}
		new_args[j] = ft_strdup(args[i]);
		i++;
		j++;
	}
	new_args[j] = NULL;
	return (new_args);
}

/*
 ** error出力のための関数。
*/

static void	put_error(char *arg)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

/*
 ** コマンドを実行する関数。コマンド実行の前に標準入出力のfd を逃して、リダイレクトの処理をしてから実行。
*/

int		no_pipe(char **args, t_edlist *vals)
{
	int fd;
	int in_out;
	int stdin_fd;
	int stdout_fd;
	int stderror_fd;
	int rv;
	char *origin_arg;
	char **paths;
	char *error;

	args = check_and_change_equal(args);//ここでargs を新しくしている。もともとのargs は free_args で開放している。
	fix_args(args, 8, '=');
	paths = get_path(vals->e_val);
	escape_fds(&stdin_fd, &stdout_fd, &stderror_fd); //リダイレクトのあとに標準入出力を復帰させるためにエスケープさせる。
	origin_arg = ft_strdup(args[0]);//こいつをmalloc するのはもっと前の別の関数でいい。
	paths = add_paths_and_change_arg0(&args[0], paths);// 新しいパスを追加。(相対パスまたは絶対パスによるファイル実行のための処理)。/
	in_out = deal_redirection(args, &fd, &error);//リダイレクトの処理を入れている。
	if (in_out == -1)
	{
		put_error(error);
		free_all(paths, origin_arg);
		return (1);
	}
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
	else if(check_if_key_value(args[0]) && check_key_str(args[0]))
	{
		rv = (update_val((&vals->d_val), args[0]));
		rv *= (update_val((&vals->e_val), args[0]));
		if (rv == 1)
			rv = 0;
		if (rv == 0)
			rv = 1;
	}
	else
		rv = (exec_shell_command(args, vals->e_val, &(vals->d_val), paths, origin_arg));//build inではないコマンドが呼ばれるときに使われる。
	recover_stdinout(in_out, &stdin_fd, &stdout_fd, &stderror_fd);//標準入出力のfd を復帰させる。
	free_all(args, 0);
	free_all(paths, origin_arg);
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
void	exec_pipes(int i, char ***args_array, int com_num, t_edlist *vals)
{
	// pid_t ret;
	int rv;
	int status;
	int pp[2] = {};
	if (i == com_num - 1)
	{
		// 左端なら単に実行
		rv = no_pipe(args_array[0], vals);
		exit(rv);
	}
	else
	{
		// 左端以外ならpipeしてforkして親が実行、子が再帰
		pipe(pp);
		g_sig_count++;
		g_ret = fork();
		if (g_ret == 0)
		{
			// 子プロセスならパイプをstdoutにdup2してdopipes(i+1)で再帰し、
			// 次のforkで親になった側が右からi+1番目のコマンドを実行
			close(pp[0]);
			dup2(pp[1], 1);
			close(pp[1]);
			exec_pipes(i + 1, args_array, com_num, vals);
			exit(0);
		}
		else
		{
				// 子プロセスの実行を待った後に
				// 親プロセスならパイプをstdinにdup2して、
				// 右からi番目のコマンドを実行
				close(pp[1]);
				dup2(pp[0], 0);
				close(pp[0]);
				no_pipe(args_array[com_num -i -1], vals);
				wait(&status);
				exit(WEXITSTATUS(status));
		}
	}
}

/*
	コマンドにパイプが一個以上含まれていた場合の関数。fork して子プロセスを作り上げる。
	ここから、再帰関数を使って、コマンドの右から順に実行させる。
*/


int		yes_pipe(char **args, t_edlist *vals, int pipe_count)
{
	char	**envp;
	int		status;
	char	***args_array; // こいつ最終的にfreeする必要あり。
	char	*num_str;
	char	*status_str;

	envp = change_into_array(vals->e_val); //環境変数リストを文字列に変換。
	args_into_array(args, &args_array, pipe_count);// ここまでで、args_array でコマンドをパイプごとに分割できた
	signal(SIGINT,signel_pipe);
	g_sig_count = 0;
	g_ret = fork();
	if (g_ret == 0)
	{

		exec_pipes(0, args_array, pipe_count + 1, vals); //一番右のコマンドを親として、右から左にコマンドを順次実行させる。
	}
	else
	{
		wait(&status);
		free_all(envp, 0);
		//ここで終了ステータスを変更する関数を入れる。
		setting_signal();
		num_str = ft_itoa(WEXITSTATUS(status)); //終了ステータスを文字列としてゲット
		status_str = ft_strjoin("?=", num_str); //終了ステータスの変数の更新用に整形
		free(num_str);
		update_val(&(vals->d_val), status_str);//終了ステータス更新。
		free(status_str);
		free(args_array);
	}
	return (WEXITSTATUS(status));
}

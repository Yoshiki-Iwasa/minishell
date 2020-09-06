/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 12:58:31 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/06 15:40:25 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	escape_fds(&stdin_fd, &stdout_fd, &stderror_fd); //リダイレクトのあとに標準入出力を復帰させるためにエスケープさせる。
	if (args[0][0] == 2)
		return (0);
	fix_args(args, 2, '$');
	args = check_and_change_equal(args);//ここでargs を新しくしている。もともとのargs は free_args で開放している。
	if (args[0] == 0)
		return (0);
	fix_args(args, 8, '=');
	paths = get_path(vals->e_val);
	origin_arg = ft_strdup(args[0]);//こいつをmalloc するのはもっと前の別の関数でいい。
	paths = add_paths_and_change_arg0(&args[0], paths);// 新しいパスを追加。(相対パスまたは絶対パスによるファイル実行のための処理)。/
	in_out = deal_redirection(args, &fd, &error);//リダイレクトの処理を入れている。
	fix_args(args, 3, '>');
	fix_args(args, 5, '<');
	fix_args(args, 7, '>');
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
		rv = (exec_shell_command(args, vals, paths, origin_arg));//build inではないコマンドが呼ばれるときに使われる。
	recover_stdinout(in_out, &stdin_fd, &stdout_fd, &stderror_fd);//標準入出力のfd を復帰させる。
	free_all(args, 0);
	free_all(paths, origin_arg);
	return (rv);
}
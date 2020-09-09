/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 12:58:31 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/10 07:51:15 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 文字列配列の先頭をみて、コマンドの処理先を分ける関数。
*/

int				look_argzero_and_exec_command
	(char **args, t_edlist *vals, char **paths, char *origin_arg)
{
	int		rv;

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
	else if (!ft_strncmp(args[0], "echo", 5))
		rv = (command_echo(args));
	else if (!ft_strncmp(args[0], "export", 7))
		rv = (command_export(args, vals));
	else if (!ft_strncmp(args[0], "unset", 7))
		rv = (command_unset(&args[1], vals->e_val, vals->d_val));
	else if (check_if_key_value(args[0]) && check_key_str(args[0]))
		rv = update_shell_value(args, vals);
	else
		rv = (exec_shell_command(args, vals, paths, origin_arg));
	return (rv);
}

/*
** fix_args をまとめて行う関数。
*/

static	void	fix_args_compose(char **args)
{
	fix_args(args, 3, '>');
	fix_args(args, 5, '<');
	fix_args(args, 7, '>');
}

/*
** errorを表示してreturnする関数。
*/

static int		free_and_return
	(char **paths, char *origin_arg)
{
	free_all(paths, origin_arg);
	return (1);
}

/*
** リダイレクトで変更したfd を変更する共に、必要なすべてのfree を行う。
*/

void			recover_fd_and_free_all
	(t_fds fds, char **args, char **paths, char *origin_arg)
{
	recover_stdinout(fds.fd_flag, \
		&(fds.stdin_fd), &(fds.stdout_fd), &(fds.stderror_fd));
	free_all(args, 0);
	free_all(paths, origin_arg);
}

/*
 ** コマンドを実行する関数。
 ** コマンド実行の前に標準入出力のfd を逃して、リダイレクトの処理をしてから実行。
*/

int				no_pipe(char **args, t_edlist *vals)
{
	t_fds	fds;
	char	*origin_arg;
	char	**paths;

	escape_fds(&(fds.stdin_fd), &(fds.stdout_fd), &(fds.stderror_fd));
	if (args[0][0] == 2 && args[0][1] != '\0')
		return (0);
	fix_args(args, 2, '$');
	args = check_and_change_equal(args);
	if (args[0] == 0 || args[0][0] == 0)
		return (0);
	fix_args(args, 8, '=');
	origin_arg = ft_strdup(args[0]);
	paths = add_paths_and_change_arg0(&args[0], vals);
	fds.fd_flag = deal_redirection(args, &(fds.fd));
	fix_args_compose(args);
	if (fds.fd_flag == -1)
		return (free_and_return(paths, origin_arg));
	fds.rv = look_argzero_and_exec_command(args, vals, paths, origin_arg);
	recover_fd_and_free_all(fds, args, paths, origin_arg);
	return (fds.rv);
}

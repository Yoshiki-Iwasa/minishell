/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 13:27:58 by yiwasa            #+#    #+#             */
/*   Updated: 2020/08/18 11:55:03 by yiwasa           ###   ########.fr       */
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

/*コマンドにパイプが含まれていた場合の関数。fork して子プロセスを作り上げる。*/

void	yes_pipe(char **args, t_edlist *vals, char **paths, int pipe_count)
{
	int i;

	i = 0;
	while (i < pipe_count) // pipe の数 分だけ fork してexec させる (初めは、一回だけにしよう)
	{
		
		i++;
	}
}
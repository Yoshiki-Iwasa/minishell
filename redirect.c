/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:12:42 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/04 06:50:39 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*標準出力のリダイレクトの実装*/

void	change_stdout_fd(char *arg, int *fd)
{
	*fd = open(arg, O_RDWR | O_TRUNC | O_CREAT , S_IRWXU);//とりあえず、０埋めして開く。
	close(1);//標準出力を閉じる。
	dup2(*fd, 1);//fd のコピーを　１　として作成。
	close(*fd);// もともとのfd はいらないので閉じる。
	// ２つ以上リダイレクトが合った場合、やりたいのは、元のfd を閉じて、新しいfd を　のコピーを1 として作成し、新しいfd はいらないので閉じること。
}

/*標準入力のリダイレクトの実装*/

void	change_stdin_fd(char *arg, int *fd)
{
	// close(*fd);
	*fd = open(arg, O_RDWR);
	close(0); //標準出力を閉じる。
	dup2(*fd, 0);//fd のコピーを　0　として作成。
	close(*fd);// もともとのfd はいらないので閉じる。
}
/*
	標準出力の追記用fd 作成
*/
void	change_stdout_fd_for_append(char *arg, int *fd)
{
	*fd = open(arg, O_RDWR | O_APPEND | O_CREAT , S_IRWXU);
	close(1);
	dup2(*fd, 1);
	close(*fd);

}

/*標準error出力のリダイレクトの実装*/

void	change_stderror_fd(char *arg, int *fd)
{
	*fd = open(arg, O_RDWR | O_TRUNC | O_CREAT , S_IRWXU);
	close(2); //標準error出力を閉じる。
	dup2(*fd, 2);//fd のコピーを　2　として作成。
	close(*fd);// もともとのfd はいらないので閉じる。
}

/*
	リダイレクトの処理をする。具体的には、fd の値を書き換えて標準入出力先を変更する。
*/
int		deal_redirection(char **args, int *fd)
{
	int i;
	int flag_in;
	int flag_out;
	int flag_error;

	i = 0;
	flag_in = 0;
	flag_out = 0;
	flag_error = 0;
	while (args[i])
	{
		if(!ft_strcmp(args[i], "<"))
		{
			args[i] = NULL; //リダイレクトの記号が引数にならないようNULL にする。
			i++;
			change_stdin_fd(args[i], fd);
			flag_in = 1;
		}
		else if(!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], ">|") || !ft_strcmp(args[i], "1>"))
		{
			args[i] = NULL; //リダイレクトの記号が引数にならないようNULL にする。
			i++;
			change_stdout_fd(args[i], fd);
			flag_out = 1;
		}
		else if (!ft_strcmp(args[i], ">>"))
		{
			args[i] = NULL;
			i++;
			change_stdout_fd_for_append(args[i], fd);
			flag_out = 1;
		}
		else if (!ft_strcmp(args[i], "2>"))
		{
			args[i] = NULL;
			i++;
			change_stderror_fd(args[i], fd);
			flag_error = 1;
		}
		i++;
	}
	if (flag_in && !flag_out)
		return (0);
	else if (flag_out && !flag_in)
		return (1);
	else if (flag_error)
		return (2);
	else
		return (3);

}

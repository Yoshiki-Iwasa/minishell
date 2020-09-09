/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 13:36:27 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/09 15:12:50 by yiwasa           ###   ########.fr       */
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

int		change_stdin_fd(char *arg, int *fd)
{
	// close(*fd);
	*fd = open(arg,  O_RDONLY);
	if (*fd == -1)
	{
		ft_putstr_fd("bash :", 1);
		ft_putstr_fd(arg, 1);
		ft_putstr_fd(": ", 1);
		ft_putendl_fd(strerror(errno), 2);
		return (0);
	}
	close(0); //標準出力を閉じる。
	dup2(*fd, 0);//fd のコピーを 0 として作成。
	close(*fd);// もともとのfd はいらないので閉じる。
	return (1);
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

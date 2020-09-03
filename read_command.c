/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 07:23:44 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/03 15:20:52 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char *g_tmp;
char *g_tmp2;

void	sig_free_line(int sig)
{
	sig = 0;
	free(g_tmp);
	g_tmp = ft_strdup("");
	g_tmp2 = ft_strdup("");
	write(1, "\n",1);
	ft_putstr_fd("minishell$ ", 1);
}

/*
 ** コマンドラインを読んでくる関数。
 ** 読み込むたびに minishell$ を表示する。
*/

int		read_command(char **line, int *state)
{
	int gnl_rv;
	// ft_putstr_fd("minishell$ ", 1);
	gnl_rv = get_next_line(0, line);

	if (**line == '\0' && gnl_rv == 1)
	{
		free(*line);
		return (0);
	}
	if (gnl_rv == 0)
	{
		write(1, "  \b\b ", 4);
		if((*line)[0] != '\0') // "$ ls Ctrl + D のとき" fork させる必要あるかな...
		{
			signal(SIGINT, sig_free_line);// もともとのコマンドが入ってるtmp1 をぶっ殺せばおｋ？
			g_tmp = ft_strdup(*line); // "ls"　とかが入ってる。
			free(*line);
			while ((get_next_line(0, line)) == 0)//この最中にCtrl + C を入力しても入力はとまらない。
			{
				g_tmp2 = *line;
				write(1, "  \b\b ", 4);
				*line = ft_strjoin(g_tmp, *line);
				free(g_tmp2);
				free(*line);
			}// 無視したいのは、Ctrl + C が押された時。Ctrl + C が押されたら、line を freeして空文字列にする。
			free(g_tmp2);
			g_tmp2 = *line;
			*line = ft_strjoin(g_tmp, g_tmp2);
			free(g_tmp);
			free(g_tmp2);
			setting_signal();
			return (1);
		}
		free(*line);
		write(1, "exit\n", 5);
		*state = 0;
		return (0);
	}
	if (gnl_rv == -1)
	{
		write(1, "GNL Fail\n", 9);
		exit(0);
		return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 07:23:44 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/18 08:48:20 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *g_tmp;
char *g_tmp2;
t_list *g_d_val;

void	sig_free_line(int sig)
{
	sig = 1;
	free(g_tmp);
	g_tmp = ft_strdup("");
	write(1, "\n", sig);
	ft_putstr_fd("minishell$ ", 1);
}

int		when_ctrl_d_pushed(char **line)
{
	signal(SIGINT, sig_free_line);
	g_tmp = ft_strdup(*line);
	while ((get_next_line(0, line)) == 0)
	{
		g_tmp2 = *line;
		write(1, "  \b\b ", 4);
		*line = ft_strjoin(g_tmp, *line);
		free(g_tmp2);
		free(*line);
	}
	g_tmp2 = *line;
	*line = ft_strjoin(g_tmp, g_tmp2);
	free(g_tmp);
	free(g_tmp2);
	setting_signal();
	return (1);
}

void	signal_read(int sig)
{
	sig = 1;
	update_val(&g_d_val, "?=130");
	write(1, "\n", sig);
	ft_putstr_fd("minishell$ ", 1);
}

/*
 ** コマンドラインを読んでくる関数。
 ** 読み込むたびに minishell$ を表示する。
*/

int		read_command(char **line, int *state, t_list *d_val)
{
	int gnl_rv;

	g_d_val = d_val;
	signal(SIGINT, signal_read);
	gnl_rv = get_next_line(0, line);
	if (**line == '\0' && gnl_rv == 1)
	{
		free(*line);
		return (0);
	}
	if (gnl_rv == 0)
	{
		write(1, "  \b\b ", 4);
		if ((*line)[0] != '\0')
			return (when_ctrl_d_pushed(line));
		free(*line);
		*state = 0;
		return (0 * write(1, "exit\n", 5));
	}
	if (gnl_rv == -1)
		return (0 * write(1, "GNL Fail\n", 9));
	setting_signal();
	return (1);
}

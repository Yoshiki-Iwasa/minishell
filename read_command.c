/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 07:23:44 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/03 06:21:38 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** コマンドラインを読んでくる関数。
 ** 読み込むたびに minishell$ を表示する。
*/

int		read_command(char **line, int *state)
{
	int gnl_rv;
	// char *tmp1;
	// char *tmp2;
	// int rv;
	// ft_putstr_fd("minishell$ ", 1);
	gnl_rv = get_next_line(0, line);

	if (**line == '\0' && gnl_rv == 1)
	{
		free(*line);
		return (0);
	}
	if (gnl_rv == 0)
	{
		// write(1, "  \b\b ", 4);
		if((*line)[0] != '\0')
		{
			write(1, "\n", 1);
		// 	tmp1 = ft_strdup(*line); // "ls"　とかが入ってる。
		// 	while ((rv = get_next_line(0, line)) == 0)
		// 	{
		// 		tmp2 = *line;
		// 		write(1, "  \b\b ", 4);
		// 		*line = ft_strjoin(tmp1, *line);
		// 		// printf("%s\n", *line);
		// 		free(tmp2);
		// 		rv = INT32_MAX;
			}
		// 	if (rv == INT32_MAX)
		// 	{
		// 		free(*line);
		// 		*line = "";
		// 		ft_putstr_fd("minishell$ ", 1);
		// 		return (1);
		// 	}
		// 	else
		// 	{
		// 		tmp2 = *line;
		// 		*line = ft_strjoin(tmp1, *line);
		// 		free(tmp2);
		// 		return (1);
		// 	}

		// }
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_pipe_exist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 12:47:15 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/07 12:50:35 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pattern_pipe_exist(char **args, t_edlist *vals, int pipe_count)
{
	int rv;
	//yes pipe のときもno pipe みたいに返り値とか考える必要あり。
		rv = yes_pipe(args, vals, pipe_count);
		if (rv == 0)
		{
			if (!update_val(&(vals->d_val), "?=0"))
				return (1);
		}
		else if (rv == 1)
		{
			if (!update_val(&(vals->d_val), "?=1"))
				return (1);
		}
		else if (rv == 100)//exit の場合100が帰るようになっている。
			return (0);
		else
			return (1);
		return (1);
}
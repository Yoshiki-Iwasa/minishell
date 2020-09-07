/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_pipe_not_exist.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 12:39:27 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/07 12:40:37 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pattern_pipe_not_exit(char **args, t_edlist *vals)
{
	int rv;
	char *state_val;
	char *state;
	rv = no_pipe(args, vals); //ここの返り値を見て、成功したら１、失敗したら０
		if (rv == 100)//exit の場合100が帰るようになっている。
		{
			if (!update_val(&(vals->d_val), "?=0"))
				return (1);
			return (0);
		}
		else
		{
			state_val = ft_itoa(rv);
			state = ft_strjoin("?=", state_val);
			if (!update_val(&(vals->d_val), state))
				return (1);
			free(state_val);
			free(state);
			if (rv == 0)
				return (1);
			else
				return (rv);
		}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_pipe_not_exist.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 12:39:27 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/21 10:29:41 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	update_exit_state_return(t_edlist *vals)
{
	update_val(&(vals->d_val), "?=1");
	return (1);
}

int			pattern_pipe_not_exit(char **args, t_edlist *vals)
{
	int		rv;
	char	*state_val;
	char	*state;

	rv = no_pipe(args, vals);
	if (rv >= 1000)
	{
		if (rv == 2001)
			return (update_exit_state_return(vals));
		return (rv);
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

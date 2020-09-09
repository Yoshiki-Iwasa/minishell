/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 11:02:18 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/09 11:02:19 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_env(t_list **e_val)
{
	if (e_val == NULL || *e_val == NULL)
	{
		ft_putendl_fd("No Env valiable", 1);
		return (1);
	}
	ft_lstiter(*e_val, ft_putendl);
	return (0);
}

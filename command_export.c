/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:05:12 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/10 08:12:46 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_error(char *arg)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	return (1);
}

/*
** exportコマンドを司る関数。
*/

int			command_export(char **args, t_edlist *vals)
{
	int		i;
	t_list	*find;

	i = 0;
	while (args[i])
	{
		if (!check_key_str(args[i]))
			return (export_error(args[i]));
		if (check_if_key_value(args[i]))
		{
			update_val((&vals->e_val), args[i]);
			update_val((&vals->d_val), args[i]);
		}
		else
		{
			if ((find = search_entry(vals->d_val, args[i])) != NULL)
				update_val((&vals->e_val), find->content);
		}
		i++;
	}
	return (0);
}

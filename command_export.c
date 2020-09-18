/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:05:12 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/18 09:56:32 by yiwasa           ###   ########.fr       */
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
** export コマンドに引数がなかったとき、環境変数を、一覧で表示する。
*/

static int	show_e_val(t_list *e_val, void (*f)(void *))
{
	if (!f)
		return (1);
	while (e_val)
	{
		ft_putstr_fd("declare -x ", 1);
		(*f)(e_val->content);
		e_val = e_val->next;
	}
	return (0);
}

/*
** exportコマンドを司る関数。
*/

int			command_export(char **args, t_edlist *vals)
{
	int		i;
	t_list	*find;

	i = 0;
	if (args[1] == NULL)
		return (show_e_val(vals->e_val, ft_putendl));
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 06:37:32 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/11 09:35:27 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** コマンドを分割するために  セミコロンの部分をnull にしている
** args をあとでまとめてfree するためにNULL で ； を埋めてる
*/

void	change_semicon_null(char **args, int *semi_co_place)
{
	*semi_co_place = find_semi_co(args);
	free(args[*semi_co_place]);
	args[*semi_co_place] = NULL;
}

/*
** シグナルの変換。
** リストの初期化。
** 環境変数はe_valにシェル変数はd_val に。
*/

void	shell_start(char **envp)
{
	t_edlist vals;

	vals.d_val = NULL;
	vals.e_val = NULL;
	setting_signal();
	if (!update_val(&(vals.d_val), "?=0"))
	{
		exit(EXIT_FAILURE);
	}
	if (!init_e_val_list(&(vals.e_val), envp))
	{
		ft_lstclear(&(vals.d_val), free);
		exit(EXIT_FAILURE);
	}
	commnad_loop(vals);
	ft_lstclear(&(vals.d_val), free);
	ft_lstclear(&(vals.e_val), free);
}

/*
 ** ここ以降の条件分岐は、argc と argv がunused で起こられないため。
*/

int		main(int argc, char **argv, char **envp)
{
	argc = 0;
	argv = 0;
	shell_start(envp);
	while (1);
	if (argc == 0 && argv == 0)
		return (EXIT_SUCCESS);
	if (argc != 0 && argv != 0)
		return (100);
}

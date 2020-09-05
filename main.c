/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 06:37:32 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/05 06:37:57 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifdef LEAKS

__attribute__((destructor))
void  end()
{
  while(1);
}

#endif
/*
 ** コマンドを分割するために  セミコロンの部分をnull にしている
 ** args をあとでまとめてfree するためにNULL で　；　を埋めてる
*/

void	change_semicon_null(char **args, int *semi_co_place)
{

	*semi_co_place = find_semi_co(args);
	free(args[*semi_co_place]);
	args[*semi_co_place] = NULL;
}

/*
 ** シグナルの設定、環境変数をリスト構造に格納、環境変数から$PATH を回収
 ** d_val はシェル変数のリスト
 ** e_val は環境変数のリスト
*/

void	shell_start(char **envp)
{
	t_edlist vals;
	// int i;

	vals.d_val = NULL;
	vals.e_val = NULL;
	setting_signal(); // シグナルハンドルが入っている。この関数以降、Ctrl + C, Ctrl + \ の挙動が変わる。
	if (!update_val(&(vals.d_val), "?=0")) //終了ステータスを表すシェル変数を?=0で初期化
	{
		exit(EXIT_FAILURE);
	}
	if (!init_e_val_list(&(vals.e_val), envp)) //envp に入っている環境変数達をリスト構造にしてリストe_valを作る。
	{
		ft_lstclear(&(vals.d_val), free);
		exit(EXIT_FAILURE);
	}
	commnad_loop(vals); // ここからがメインの処理。この関数以降で入力が行われる。
	ft_lstclear(&(vals.d_val), free);
	ft_lstclear(&(vals.e_val), free);
}

int main(int argc, char **argv, char **envp)
{
	argc = 0;
	argv = 0;
	ft_putstr_fd("                           ■                    ■   ■\n           ■           ■   ■                    ■   ■\n                           ■                    ■   ■\n■■■■  ■■   ■   ■ ■■■   ■   ■ ■■■   ■■■■   ■■■■  ■   ■\n■■  ■■  ■  ■   ■■  ■■  ■   ■■  ■■  ■     ■■  ■  ■   ■\n■   ■   ■  ■   ■    ■  ■   ■    ■  ■     ■   ■■ ■   ■\n■   ■   ■  ■   ■    ■  ■   ■    ■   ■■   ■■■■■■ ■   ■\n■   ■   ■  ■   ■    ■  ■   ■    ■     ■  ■      ■   ■\n■   ■   ■  ■   ■    ■  ■   ■    ■  ■  ■  ■■     ■   ■\n■   ■   ■  ■   ■    ■  ■   ■    ■  ■■■■   ■■■■  ■   ■\n\n\n", 1);

 	shell_start(envp);
/*
 ** ここ以降の条件分岐は、argc と argv がunused で起こられないため。
*/
	if (argc == 0 && argv == 0)
		return EXIT_SUCCESS;
	if (argc != 0 && argv != 0)
		return (100);
}

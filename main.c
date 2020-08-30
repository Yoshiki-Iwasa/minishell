#include "minishell.h"

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
	char	**paths;
	// int i;

	vals.d_val = NULL;
	vals.e_val = NULL;
	setting_signal(); // シグナルハンドルが入っている。
	if (!update_val(&(vals.d_val), "?=1")) //終了ステータスを表すシェル変数を?=1で初期化
	{
		exit(EXIT_FAILURE);
	}
	if (!init_e_val_list(&(vals.e_val), envp)) //envp に入っている環境変数達をリスト構造にしてリストe_valを作る。
	{
		ft_lstclear(&(vals.d_val), free);
		exit(EXIT_FAILURE);
	}
	paths = get_PATH(vals.e_val); // 環境変数の中からPATH を回収することで、buil in ではない関数が呼ばれた時も対応できるように。
	if (!paths)
	{
		ft_lstclear(&(vals.d_val), free);
		ft_lstclear(&(vals.e_val), free);
		exit(EXIT_FAILURE);
	}
	commnad_loop(vals, paths); // ここからがメインの処理。この関数以降で入力が行われる。
	ft_lstclear(&(vals.d_val), free);
	ft_lstclear(&(vals.e_val), free);
	free_all(paths, 0);
}

int main(int argc, char **argv, char **envp)
{
	argc = 0;
	argv = 0;
	shell_start(envp);
	while (1);
	return EXIT_SUCCESS;
}

#include "minishell.h"

/*
** shell変数の更新を行う。場合によっては環境変数の変更を行う関数。
*/

int		update_shell_value(char **args, t_edlist *vals)
{
	int		rv;
	char 	*key;

	rv = (update_val((&vals->d_val), args[0]));
	key = get_key(args[0]);
	if (search_entry(vals->e_val, key) != 0)
	{
		rv *= (update_val((&vals->e_val), args[0]));
	}
	free(key);
	if (rv == 1)
		rv = 0;
	if (rv == 0)
		rv = 1;
	return (rv);
}

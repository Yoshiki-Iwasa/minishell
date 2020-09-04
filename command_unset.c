#include "minishell.h"

/*
 ** command unset を実行するための関数
*/

int	command_unset(char **args, t_list *e_val, t_list *d_val)
{
	int		i;
	t_list	*find;
	char	*key;

	i = 0;
	while (args[i])
	{
		key = get_key(args[i]);
		find = search_entry(e_val ,key);
		if (find != NULL)
		{
			lst_del_connect(&e_val, key, free);
		}
		i++;
	}
	i = 0;
	while (args[i])
	{
		key = get_key(args[i]);
		find = search_entry(d_val ,key);
		if (find != NULL)
		{
			lst_del_connect(&d_val, key, free);
		}
		i++;
	}
	return (0);
}

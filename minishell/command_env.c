#include "minishell.h"

int	command_env(t_list **e_val)
{
	if (e_val == NULL || *e_val == NULL)
	{
		ft_putendl_fd("No Env valiable", 1);
		return (0);
	}
	ft_lstiter(*e_val, ft_putendl);
	return (1);
}
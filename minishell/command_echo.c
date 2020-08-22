#include "minishell.h"

int	command_echo(char **args)
{
	int i;
	i = 1;
	if (!ft_strcmp(args[i], "-n"))
	{
		i++;
		while (args[i] != 0)
		{
			ft_putstr_fd(args[i], 1);
			i++;
			if (args[i] != NULL)
				write(1, " ", 1);
		}
	}
	else
	{
		while (args[i] != 0)
		{
			ft_putstr_fd(args[i], 1);
			i++;
			if (args[i] != NULL)
				write(1, " ", 1);
		}
		write(1, "\n", 1);
	}
	return (1);
}

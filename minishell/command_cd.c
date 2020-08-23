#include "minishell.h"

int	command_cd(char *arg, t_list **e_val)
{
	char *pwd;
	char path[PATH_MAX + 1];
	char *home;
	int	chdir_rv;

	errno = 0;
	path[0] = '\0';
	if(arg == NULL)
	{
		arg = find_value(e_val, "HOME=");
	}
	else if (arg[0] == '~')
	{
		home = find_value(e_val, "HOME=");
		ft_strcat(path, home);
		ft_strcat(path, &arg[1]);
		arg = path;
	}
	chdir_rv = chdir(arg);
	if (chdir_rv == -1)
		ft_putendl_fd(strerror(errno), 1);
	return (1);
}

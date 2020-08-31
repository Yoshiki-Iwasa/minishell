#include "minishell.h"

int		command_pwd(void)
{
	char *pwd;
	char *buf;

	errno = 0;
	buf = NULL;
	pwd = getcwd(buf, PATH_MAX);
	if (!pwd)
	{
		ft_putendl_fd(strerror(errno), 1);
		return (1);
	}
	else
		ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}

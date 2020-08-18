#include "minishell.h"

int	command_exit(void)
{
	exit(0); // こいつでexit するとおもいっきりメモリリークする。
	return (0);
}
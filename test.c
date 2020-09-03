#ifdef TEST
#include <stdio.h>
#include <unistd.h>
int main()
{
	char buf[10];
	printf("%zd\n",read(0, buf, 9));
	printf("%c\n", buf[0]);
}

#endif

#ifdef TEN
#include "minishell.h"

int main()
{
	int fd =  open("test1.txt", O_RDWR | O_APPEND | O_CREAT , S_IRWXU);
	write(fd, "test\n", 5);
}
#endif

#ifdef READ
#include "minishell.h"
int main()
{
	char buf[5];
	int stdout;

	stdout = dup(1);
	close(1);
	dup2(1, 0);
	write(1, "1234", 5);
	read(0, buf, 5);
	dup2(stdout, 1);

	printf("%s\n", buf);
}

#endif

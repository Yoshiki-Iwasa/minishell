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

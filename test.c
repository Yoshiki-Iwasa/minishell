#ifdef TEST
#include <stdio.h>
#include <unistd.h>
int main()
{
	char buf[10];
	read(0, buf, 9);
}

#endif

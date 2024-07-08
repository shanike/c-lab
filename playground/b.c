#include <stdlib.h>

int main()
{
	char *s;
	s = (char *)malloc(15);
	s = "hello world";
	free(s);
	return 0;
}

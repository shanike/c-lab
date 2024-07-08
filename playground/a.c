#include <stdio.h>

int main2() {
	int arr[10] = {1, 2, 3};
	char *p;

	p = arr;
	
	printf("%c\n", p);
	return 0;
}

int main () {
	struct A { int a; };
	struct B { int b; };
	struct A a;
	struct B b;
	a = b;
	return 0;
}


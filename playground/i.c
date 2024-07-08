#include <stdio.h>
typedef struct o {
	int *a1;
	double c3;
} T;

#define getfield(t) ((t)->c3)

int test(T *n, T *m)
{
	return (getfield(n)==getfield(m));
}

int main()
{
	int a=1, b=2,*p1 = &a, *p2=&b;
	T n;
	T m;
	n.a1=p1;
	m.a1=p2;
	n.c3=11;
	m.c3=11;
	printf("res=%d\n",test(&n,&m));
	return 0;
}

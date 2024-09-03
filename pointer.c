#include<stdio.h>

int main()
{
	int a = 10;
	int *p = &a;
	
	printf("a = %d\np = %u\n", a, p);
	return 0;
}

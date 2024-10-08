#include<stdio.h>
#include"ops.h"

int add(int x, int y){
	printf("%d + %d = ", x, y);
	return x+y;
}

int sub(int x, int y){
	printf("%d - %d = ", x, y);
	return x-y;
}

int mul(int x, int y){
	printf("%d * %d = ", x, y);
	return x*y;
}

int div(int x, int y){
	if (y == 0){
		printf("Can't divide with 0\n");
		return 0;
	}
	
	printf("%d / %d = ", x, y);
	return x/y;
}

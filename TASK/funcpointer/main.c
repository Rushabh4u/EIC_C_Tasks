#include<stdio.h>
#include "ops.h"

int main(){
	int (*ops)(int, int);
	
	void *arr[4] = {&add, &sub, &mul, &div};
	int a = 50, b = 10;
	int ans;

	for(int i=0; i<4; i++){
		ops = arr[i];
		ans = ops(a, b);
		printf("%d\n", ans);
	}
	return 0;
}

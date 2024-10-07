#include "operations.h"

int main(){
	int (*ops)(int, int);
	
	int *arr[4] = {&add, &sub, &mul, &div};
	int a = 50, b = 10;
	
	for(int i=0; i<4; i++){
		ops = arr[i];
		ops(a, b);
	}
	return 0;
}

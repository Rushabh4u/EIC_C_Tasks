/*
*AIM: Verify that the expression getchar() != EOF is 0 or 1.
*Author: Rushabh Goswami
*Created: 22/7/2024
*/

//Required Libraries
#include<stdio.h>

int main(){

	int Ic;
	Ic = getchar();
	while(Ic != EOF){
		printf("1\n");
		Ic = getchar();
	}
	printf("0\n");
	return 0;
}

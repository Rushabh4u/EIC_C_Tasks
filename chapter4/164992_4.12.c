/*
* Adapt the ideas of printd to write a recursive version of itoa; that is, convert an integer into a string by calling a recursive routine.
*Author: Rushabh Goswami
*Create: 28/8/2024
*/


#include <stdio.h> 
#include<math.h>
#include "error_handling.h"

#define MAXIMUM 100
static int index = 0;
void itoa(int n, char arr[]);

int main()
{
	int choice;
	do
	{
		int num;
		char arr[MAXIMUM];
		
		printf("\nEnter a valid integer number to convert it into the string: ");
		if (scanf("%d", &num) != 1)
		{
			handle_error(ERROR_INVALID_INPUT);
			return 1;
		}
		
		if (num < 0) 
		{ 
			arr[index++] = '-'; 
			num = -num; 
		}
		int digit = log10(num);
		
		
		itoa(num, arr);
		printf("The number converted into string is:\n");
		if(num == 0)
			printf("%c", num + '0');
		for(int i =0; i<=digit; i++)
			printf("%c", arr[i]);
		if(arr[0] == '-')
			printf("%c", arr[digit+1]);
	
		index=0;
		printf("\nRe-Run? (1 for yes/ 0 fro no): ");
		if (scanf("%d", &choice) != 1)
		{
			handle_error(ERROR_INVALID_INPUT);
			return 1;
		}
	}while(choice == 1);
}

 /* printd: print n in decimal */ 
void itoa(int n, char arr[]) 
{ 
	//static char arr[MAXIMUM];
	//int index = 0;
	
	
	if (n / 10 >0)  
		itoa(n / 10, arr);  
	arr[index++] = (n % 10 + '0'); 
	return;
}

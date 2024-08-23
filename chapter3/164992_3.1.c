/*
*AIM: Rewrite the function lower, which converts upper case letters to lower case, with a conditional expression instead of if-else. 
*Author: Rushabh Goswami 
*Created: 20/8/2024
*/

/* Required Libraries */
#include <stdio.h> 
#include "error_handling.h"

int binsearch(int x, int v[], int n);

int main()
{
	int iChoice; /* user choice to re-run the program */
	
	do
	{
		int arr[50];
		int n;
		printf("Enter the size of the aray: ");
		scanf("%d", &n);
		
		printf("Enter %d sorted elements (in accending order):\n", n);
		for (int i = 0; i < n; i++)
		{
			scanf("%d", &arr[i]);
			if(i > 0 && arr[i] < arr[i-1])
			{
				printf("Please enter sorted elements as instructed. Please listen carefully!!!\n");
				goto lable;
			}
		}
		int x;
		printf("Enter the element you want to find: ");
		scanf("%d", &x);
		
		printf("%d", binsearch(x, arr, n));
		putchar('\n');
		
		lable:
		printf("Re-Run? (1 for yes/0 for no): ");
		scanf("%d", &iChoice);
		if( iChoice != 1 && iChoice != 0 )
		{
			handle_error(ERROR_INVALID_INPUT);
			return 1;
		}
	}while(iChoice == 1);
	
	return 0;
}


int binsearch(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;

	mid = (low + high) / 2;

	while (low < high && x != v[mid]) 
	{
		if (x > v[mid])
		    low = mid + 1;
		else
		    high = mid - 1;

		mid = (low + high) / 2;
	}

	if (x == v[mid])
		return mid;
	else
		return -1;
}

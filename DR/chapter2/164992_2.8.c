/*
*AIM: Write a function rightrot(x,n) that returns the value of the integer x rotated to the right by n positions.
*Author: Rushabh Goswami 
*Created: 8/8/2024
*/

/* Required Libraries */
#include <stdio.h> 
#include <math.h>
#include "../error_handling.h"

/* Function that returns the value of the integer x rotated by n positions */
int rightrot(int x, int n);

int main()
{
	int iChoice; /* To store user choice to re run the program */
	
	do
	{
		int iX; /* to take the integer number on which operation has to be performed */
		int iN; /* to take the number of bits has to be rotated */
		
		printf("Enter the integer number to rotate bits (Value of x): ");
		if(scanf("%d", &iX) != 1)
		{
			handle_error(ERROR_INVALID_INPUT);
			return 1;
		}

		printf("Enter the integer number that indicate how many bits you want to rotate? (Value of n): ");
		if(scanf("%d", &iN) != 1)
		{
			handle_error(ERROR_INVALID_INPUT);
			return 1;
		}
		
		if(iX < 0)
		{
			printf("Enter positive value\n");
			return 0;
		}
		
		printf("%d becomes -----> %d <----- after rotating %d bits\n\n", iX, rightrot(iX, iN), iN);
		
		
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


/*
* Function to rotate n bits in the binary representation of x.
* NOTE: This function rotating the bits in circular manner.
* Author : Rushabh Goswami
* Created : 8/8/2024
*/

int rightrot(int x, int n)
{
	if (x == 0)
		return 0;
		
	if (n == 0)
		return x;
		
	int iRotated; /* to store the number of rotated bits so we can directly return this varible without affecting the x */
	int iBits; /* to check that how many bits are required to take as total bits to represent that number */
	
	for(int i = 0; i < 32; i++)
	{
		if (x < (int)pow(2, i))
		{
			iBits = i;
			break;
		}
	}
		
	if(n > iBits)
		n = n % iBits;	
	
	iRotated = (x >> n) | ((x & ( (int)pow(2, n)-1) ) << (iBits-n));
	
	return iRotated;
}

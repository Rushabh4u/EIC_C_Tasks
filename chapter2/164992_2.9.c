/*
*AIM: In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit in x. Explain why. Use this observation to write a faster version of bitcount.
*Author: Rushabh Goswami 
*Created: 20/8/2024
*/

/* Required Libraries */
#include <stdio.h> 
#include <ctype.h>
#include "error_handling.h"

int BitCount(int x);

int main()
{
	int iChoice; /* user choice to re-run the program */
	
	do
	{
		int iX; /* to sore the number of which bits are supposed to be count */
		
		printf("Enter a positive non zero number: ");
		if(scanf("%d", &iX) != 1 || iX < 1)
		{
			handle_error(ERROR_INVALID_INPUT);
			return 1;
		}
		printf("The number of 1's in the binary representation of %d is %d\n", iX, BitCount(iX));
		
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
*This function takes an integer unsigned number
 and returns the count the number of 1's 
 in the binary representation of that number.
*Author: Rushabh Goswami
*Created: 20/8/2024
*/
int BitCount(int x)
{
	int count; /* to store the number of 1's */
	
	for(count = 0; x != 0; x &= (x - 1))
		count++;
		
	return count;
}

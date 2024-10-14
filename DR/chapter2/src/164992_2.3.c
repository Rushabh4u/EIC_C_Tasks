/*
*AIM: Write a function htoi(s), which converts a string of hexadecimal digits (including an optional 0x or 0X) into its equivalent integer value. The allowable digits are 0 through 9, a through f, and A through F.
*Author: Rushabh Goswami 
*Created: 6/8/2024
*/

/* Required Libraries */
#include <stdio.h> 
#include <math.h>
#include "error_handling.h"

int htoi(char cHex[], int iPower);
int main()
{
	char cChoice; /* to take user's choice to re run the program */
	
	do
	{
		printf("Enter a valid hexadecimal number: ");
		
		char cHex[20]; /* to store hexadecimal number entered from user */
		
		int iIndex = 0; /* to keep track of the index of the array */
		
		char iC; /* to get characters from user and store it in the array */
		
		int iAnswer; /* Indicates the final integere answer of our program */
		
		
		/* take character from user till he presses Enter or EOF */
		while ((iC = getchar()) != '\n' && iC != EOF)
		{
			if ( (iC >= '0' && iC <= '9') || (iC >= 'A' && iC <= 'F') || (iC >= 'a' && iC <='f') || iC == 'x' || iC == 'X' )
			{
				cHex[iIndex++] = iC; /* store character in the array */
			}
			else
			{
				printf("1st\n");
				handle_error(ERROR_INVALID_INPUT);
				return 1;
			}
			
		}
		
		
		cHex[iIndex] = '\0'; /* end the array with null to find its ending point */
		int iPower = iIndex-1; /* to take power for the conversion of the number system ( HEX to DEC ) */
		
		iAnswer = htoi(cHex, iPower);
		
		/* print the output message and answer */
		printf("The decimal equivalent of given number is -----> %d", iAnswer);
		
		
		
		
		/* print message for user */
        printf("\nDo you want to enter 1 more string? (y / n): ");
        
        /* take choice of user to rerun the program */
        scanf(" %c", &cChoice);  // The space before %c ignores any whitespace characters
        
        /* check if it's valid or not */
        if(cChoice != 'y' && cChoice != 'Y' && cChoice != 'n' && cChoice != 'N')
        {
            /* handle the error if input is not valid */
            handle_error(ERROR_INVALID_INPUT);
            return 1;
        }
        while ((iC = getchar()) != '\n' && iC != EOF);
    } while(cChoice == 'y' || cChoice == 'Y');

}


int htoi(char cHex[], int iPower)
{

	int iIndex = 0; /* reset the iIndex to start the loop from the this index... this will help us to skip the first 2 characters if they are 0x. */
	
	
	
		/* to skip the initial blank spaces and decrement the power by 1 per blank space*/
	while(cHex[iIndex] == ' ')
	{
		iIndex++;
		iPower--;
		
	}
	
	
	
	
		/* ignore 0x or 0X and decrement the power by 2 */
	if ( (cHex[iIndex] == '0' && cHex[iIndex+1] == 'x') || (cHex[iIndex] == '0' && cHex[iIndex+1] == 'X') )
	{
		iIndex += 2;
		iPower -= 2;
	}
		
		
		
		
		/* to handle a test case where user enters x0 or X0 instead of 0x or 0X. Which is an invali input */
	if ( (cHex[iIndex] == '0' && cHex[iIndex+1] == 'x') || (cHex[iIndex] == '0' && cHex[iIndex+1] == 'X') )
	{
		handle_error(ERROR_INVALID_INPUT);
		return 1;
	}
	
	
	
	
	
	int iDec = 0; /* to store the final result */
	while(cHex[iIndex] != '\0')
	{
		/* handle the lower case latters */
		if ( (cHex[iIndex] >= 'a' && cHex[iIndex] <= 'f') )
		{
			/* decrement the characters ascii to 87 because ascii of a is 97 and 97 - 87 = 10 
			and we want to start the counting of a to f is from 10 to 15 */
			iDec += (cHex[iIndex] - 87) * pow(16, iPower--);	
		}
		
		
		/* handle the lower case latters */
		if ( (cHex[iIndex] >= 'A' && cHex[iIndex] <= 'F') )
		{
			/* decrement the characters ascii to 55 because ascii of A is 65 and 65 - 55 = 10 
			and we want to start the counting of A to F is from 10 to 15 */
			iDec += (cHex[iIndex] - 55) * pow(16, iPower--);
		}
		
		
		/* handle the lower case latters */
		if ( (cHex[iIndex] >= '0' && cHex[iIndex] <= '9') )
		{
			/* decrement the characters ascii to 48 because ascii of 0 is 48 and 48 - 48 = 0 
			and we want to start the counting of 0 to 9 is from 0 to 9 */
			iDec += (cHex[iIndex] - 48) * pow(16, iPower--);
		}
		
		/* decrement the iIndex */
		iIndex++;
	}
	return iDec;

}

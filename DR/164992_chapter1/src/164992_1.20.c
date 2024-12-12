/*
*AIM: Write a program detab that replaces tabs in the input with the proper number of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns. Should n be a variable or a symbolic parameter?
*Author: Rushabh Goswami 
*Created: 2/8/2024
*Modified: 2/8/2024
*/

/* Required Libraries */
#include <stdio.h> 
#include "error_handling.h"
#define MX 1000

int main()
{
	char cChoice; /* stores the users choice for re run the program */
	
	do
	{
		int iC; /* for geting character stream from user */
		int iIndex = 0; /* to keep track on the index of character */
		
		printf("\nEnter a string: \n");
		
		while((iC = getchar()) != '\n' && iC != EOF)
		{
			if(iC == '\t')
			{
				int iIncrement = 8 - (iIndex%8); /* this variable helps iIndex to increment specific amount of times that for loop s executed */
				for(int i = 0; i < iIncrement; i++)
				{
					putchar('*');
				}
				iIndex+=iIncrement;
			}   	
			else
			{
				putchar(iC);
				iIndex++;
			}
		}
		
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

    return 0;
}

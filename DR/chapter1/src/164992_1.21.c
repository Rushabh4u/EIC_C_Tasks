/*
*AIM: Write a program entab that replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing. Use the same tab stops as for detab. When either a tab or a single blank would suffice to reach a tab stop, which should be given preference?
*Author: Rushabh Goswami 
*Created: 2/8/2024
*Modified: 2/8/2024
*/

/* Required Libraries */
#include <stdio.h> 
#include "error_handling.h"

int main()
{
	char cChoice; /* stores the users choice for re run the program */
	
	do
	{
		char iC; /* to get character stream from the user as input */
		int iCounter = 0; /* to calculate the number of total countinuous spaces */

		/* print message for user */
		printf("Enter String to replace spaces to tabs if 8 spaces are there: \n");
		while ((iC = getchar()) != '\n' && iC != EOF)
		{
			if(iC == ' ')
			{
				while(iC == ' ')
				{
					iCounter++;
					iC = getchar();
					
					if(iCounter == 8)
					{
						putchar('\t');
						iCounter = 0;
					}
				}
							
				while(iCounter > 0)
				{
					putchar('*');
					iCounter--;
				}	
				putchar(iC);
			}
			else
			{
				putchar(iC);
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

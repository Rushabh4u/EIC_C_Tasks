/*
*AIM: Write a program to "fold" long input lines into two or more shorter lines after the last non-blank character that occurs before the n-th column of input. Make sure your program does something intelligent with very long lines, and if there are no blanks or tabs before the specified column. 
*Author: Rushabh Goswami 
*Created: 4/8/2024
*/

/* Required Libraries */
#include <stdio.h> 
#include "error_handling.h"

#define LEN_OF_LINE 10
#define IN 1
#define OUT 0

int main()
{
	char cChoice; /* stores the users choice for re run the program */
	
	do
	{
		int iC;  /* to get character stream from user */
		
		int interval_counter = 0; /* keeps track on the character counter and it resets after max line length is reached */
		
		/* state indicates that whethere the cursour is inside the word or outside the word 
		( Note: The cursor is said to be outside a word if it encounters the blank space or tab. ) */
		int state = OUT; 
		
		/* print message for user */
		printf("\nEnter a string to fold it after interval of 10 characters: \n");
		
		/* start tacking character stream and apply logic of the program */
		while((iC = getchar()) != '\n' && iC!= EOF)
		{
			if (iC != '\n')
				interval_counter++; /* after every character increment the counter if it is not newline character	*/
			
			/* change the state from in to out if any valid character is entered */
			if (iC != ' ' && iC != '\t' && iC != '\n' && state == OUT)
				state = IN;
			
			/* change the state from out to in if any blank space or tab or newline character is entered */
			if ((iC == ' ' || iC == '\t' || iC == '\n') && (state == IN))
				state = OUT;
				
			/*  */
			if(state == OUT && interval_counter >= LEN_OF_LINE)
			{
				putchar('\n');
				interval_counter = 0;
			}
			else
				putchar(iC);
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
    } while (cChoice == 'y' || cChoice == 'Y');

    return 0;
}


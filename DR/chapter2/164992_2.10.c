/*
*AIM: Rewrite the function lower, which converts upper case letters to lower case, with a conditional expression instead of if-else. 
*Author: Rushabh Goswami 
*Created: 20/8/2024
*/

/* Required Libraries */
#include <stdio.h> 
#include "error_handling.h"


int main()
{
	int iChoice; /* user choice to re-run the program */
	
	do
	{
		int iC=0;
		printf("Enter Sentence to convert it into lower case:\n");
		while((iC = getchar()) != '\n' && iC != EOF)
		{
			(iC >= 'A' && iC <= 'Z')? putchar(iC + 'a' - 'A'): putchar(iC);
		}
		putchar('\n');
		
		printf("Re-Run? (1 for yes/0 for no): ");
		scanf("%d", &iChoice);
		if( iChoice != 1 && iChoice != 0 )
		{
			handle_error(ERROR_INVALID_INPUT);
			return 1;
		}
		while((iC = getchar() != '\n') && iC != EOF);
	}while(iChoice == 1);
	
	return 0;
}



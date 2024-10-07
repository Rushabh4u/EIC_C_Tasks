/*
*AIM: Verify that the expression getchar() != EOF is 0 or 1.
*Author: Rushabh Goswami
*Created: 22/7/2024
*/

/* Required Libraries */
#include<stdio.h>
#include "error_handling.h"

int main(){

	int iC; /* to store every character enter by user from keyboard */
	
	
	
	/* Iterate while current character is not end of file */
	while((iC = getchar()) != EOF)
	{
		/* if we submit the expresion by pressing Enter button that \n character should not be counted and loop might continue */
		if(iC == '\n')
			continue;
			
		/* Notify user that the condition is true by printing 1 on the screen */
		printf("\ngetchar() != EOF is 1\n\n");
	}
	/* Notify user that the condition is false and character is end of file by printing 0 on the screen */
	printf("\ngetchar() != EOF is 0\n");
	
	return 0;
}

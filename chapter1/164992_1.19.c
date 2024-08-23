/*
*AIM: Write a function reverse(s) that reverses the character string s. Use it to write a program that reverses its input a line at a time.
*Author: Rushabh Goswami
*Created: 30/7/2024
*/

/* Required Libraries */
#include <stdio.h> 
#include "error_handling.h"
#define MAXIMUM 500 /* defining maximum limit of the character array to store */

/* function to print reversed string */
void reverse(char cArray[], int iIndex)
{
	
	/* printig the output message a=for the user */
	printf("\nReversed string is ----> ");
	
	for(int i = iIndex-1; i >= 0; i--)
	{
		printf("%c", cArray[i]);
	}
}

int main()
{		
		char iC; /* to get character stream */
		char cArray[MAXIMUM]; /* to steore the entire string in the array and later on we will simply print this array in reverse */
		int iIndex = 1; /* to keep track of the index of the array */
		
		/* add new line at the starting of the array for better UI */
		cArray[0] = '\n';
		
		/* print the message for user */
		printf("\nEnter the string to reverse it: ");
		
		/* get all characters and store then inside the array until user presses ENTER */
		while((iC = getchar()) != '\n')
		{
			cArray[iIndex++] = iC;
		}		
		
		/* Call reverse function once the string is taken from the user */
		reverse(cArray, iIndex);
		
		
		
	return 0;
}

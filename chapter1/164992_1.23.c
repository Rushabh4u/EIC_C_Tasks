/*
*AIM: Write a program detab that replaces tabs in the input with the proper number of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns. Should n be a variable or a symbolic parameter?
*Author: Rushabh Goswami 
*Created: 2/8/2024
*/

/* Required Libraries */
#include <stdio.h> 
#include "error_handling.h"

#define MAXSIZE 20000

int main()
{
		char iC; /* to take character stream entered from the user */
		
		char cArr[MAXSIZE]; /* To store the input program and give a proper output to the user */
		
		int iIndex = 0; /* to iterathe the cArray */
		
				 /* print message for user */
        	printf("Enter your code below to remove all the comments from it: \n ");
	
		while ((iC = getchar()) != EOF)
		{
			cArr[iIndex++] = iC;
		}
		
		/* print message for user */
		printf("<==================== Code without comments ====================>\n");
		
		
		/* copy the index to find the length of the code so we can run the for loop accordingly */
		int iLength_of_cArray = iIndex-1;

		/* run this for loop till entered code ends */
		for(iIndex = 0; iIndex <= iLength_of_cArray; iIndex++)
		{
			/* handle the strings... print all the comments if they are inside the string */
			if (cArr[iIndex] == '\"' ) /* if string is started */
			{
				while(cArr[iIndex] != '\"') /* till string ends */
					printf("%c", cArr[iIndex++]); /* print all the character and then increment the for loop variable */
				printf("%c", cArr[iIndex]); /* also print the " when string ends */
			}
			/* handle the multi-line comment */
			else if (cArr[iIndex] == '/') /* if comment starts */
			{	
				if(cArr[iIndex+1] == '*')
				{	
					while(1)
					{
						if( (cArr[iIndex-1] == '*') && (cArr[iIndex] == '/'))
							break;
						else
							iIndex++; /* skip all the characters inside the comment */
					}
				}
				else if (cArr[iIndex+1] == '/')
				{
					while(cArr[iIndex] != '\n')
					{
						iIndex++; /* skip all the characters inside the comment */
					}
				}
					
			}
			/* if it is code component and not a comment */
			else
				printf("%c", cArr[iIndex]);
		}
        

    return 0;
}


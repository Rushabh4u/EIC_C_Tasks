/*
*AIM: Write a program to print a histogram of the frequencies of different characters in its input.
*Author: Rushabh Goswami
*Created: 29/7/2024
*Modified: 29/7/2024
*/

/* Required Libraries */
#include<stdio.h>

#define SIZE 97 /* maximum size of the cArray */

int main(){
	
	char iC;
	char cArr[SIZE] = {0}; /* character cArray to store distinct characters in the given string */
	int iTab, iSpace, iNl;
	iTab = iSpace = iNl = 0;
	
	printf("Enter the string to print the histogram of character frequency:\n");
	while((iC = getchar()) != EOF)
		if(iC == "\t")
			iTab++;
		else if(iC == " ")
			iSpace++;
		else if(iC == "\n")
			iNl++;
		else 
			cArr[iC - 33]++; /* convert ascii of the characters to the index by subtracting it with 33 */
	/* Traverse through the entire array */
	for(int iIndex = 0; iIndex < SIZE; iIndex++)
	{
		/* check if character is present in the string.
		---> the character is said to be present if its index is non zero */
		if(iTab > 0)
		{
			printf("\n\\t : ", 9);
			while(iTab != 0)
			{
				putchar('*');
				iTab--;
			}
		}
		
		else if(iSpace > 0)
		{
			printf("\n\s : ", 32);
			while(iSpace != 0)
			{
				putchar('*');
				iSpace--;
			}
		}
		else if(iNl > 0)
		{
			printf("\n\\n : ", 10);
			while(iNl != 0)
			{
				putchar('*');
				iNl--;
			}
		}
		if(cArr[iIndex] > 0)
		{
			/* if character is present print it by adding 33 which leads us to its original ascii value */
			printf("\n%c : ", iIndex+33);
			
			/* now start decrementing the number untill its becomes zero and print * parallaly */
			while(cArr[iIndex] != 0)
			{
				putchar('*');
				cArr[iIndex]--;
			}
		}
	}	
	putchar('\n');
	return 0;
}

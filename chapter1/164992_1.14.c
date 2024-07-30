/*
*AIM: Write a program to print a histogram of the frequencies of different characters in its input.
*Author: Rushabh Goswami
*Created: 23/7/2024
*/

/* Required Libraries */
#include<stdio.h>

#define SIZE 94 /* maximum size of the cArray */

int main(){
	
	int iC;
	char cArr[SIZE] = {0}; /* character cArray to store distinct characters in the given string */
	
	printf("Enter the string to print the histogram of character frequency:\n");
	while((iC = getchar()) != EOF) 
		cArr[iC - 33]++; /* convert ascii of the characters to the index by subtracting it with 33 */
	/* Traverse through the entire array */
	for(int iIndex = 0; iIndex < SIZE; iIndex++)
	{
		/* check if character is present in the string.
		---> the character is said to be present if its index is non zero */
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

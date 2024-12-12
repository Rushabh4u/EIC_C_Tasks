/*
*AIM: Write a program that prints its input one word per line 
*Author: Rushabh Goswami
*Created: 22/7/2024
*Modified: 22/7/2024
*/

/* Required Libraries */
#include<stdio.h>

int main(){
	
	int iC; /* to iterate through the given string */
	int iCount = 0; /* to count the sum of ascii of the continuous tabs or spaces. */
	
	printf("Enter the string to print its words line by line:\n");
	while((iC = getchar()) != EOF){
		/* check if it is space or tab */
		if(iC == ' ' || iC == '\t'){
			iCount += iC; /* count the sum of ascii of spaces and tabs */
		}
		else{
			/* check if the iCount's value is greater than the ascii of tab (ASCII of tab is 9 and ASCII of blank space is 32). */
			if(iCount >= 9){
				putchar('\n'); /* if multiple tabs or spaces are there only 1 blank space will be printed. */
				iCount = 0; /* reset the count */
			}
			putchar(iC); /* print if it's a character */
		}
	}
	return 0;
}

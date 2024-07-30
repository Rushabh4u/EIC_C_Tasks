/*
*AIM: Write a program to print a histogram of the lengths of words in its input. 
*Author: Rushabh Goswami
*Created: 
*/

/* Required Libraries */
#include<stdio.h>

int main(){
	
	int iC;
	int iCount = 0; /* to count the sum of ascii of the continuous tabs or spaces. */
	
	printf("Enter the string to print the histogram of the lenghth of words:\n");
	while((iC = getchar()) != EOF){
		/* check if it is space or tab */
		if(iC == ' ' || iC == '\t' || iC == '\n'){
			iCount += iC; /* count the sum of ascii of spaces and tabs */
		}
		else{
			/* check if the iCount's value is greater than the ascii of tab (ASCII of tab is 9 and ASCII of blank space is 32). */
			if(iCount >= 9){
				putchar('\n'); /* if multiple tabs or spaces are there only 1 blank space will be printed. */
				iCount = 0; /* reset the count */
			}
			putchar('*'); /* print if it's a character */
		}
	}
	putchar('\n');
	return 0;
}

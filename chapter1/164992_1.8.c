/*
*AIM: Write a program to count blanks, tabs, and newlines.
*Author: Rushabh Goswami
*Created: 22/7/2024
*/

/* Required Libraries */
#include<stdio.h>
#include "error_handling.h"

int main(){
	
	int iC; /* to iterate every character of the given string */
	int iTabs = 0; /* To store the count of tabs */
	int iSpaces = 0; /* To store the count of spaces */
	int iNew_Lines = 0; /* To store the count of New Lines */
	
	printf("Enter text to calculate blanks, tabs and new lines in it: \n\n");
	while((iC = getchar()) != EOF){
		/* Check if character is tab */
		if(iC == '\t'){
			iTabs++; /* if character is tab simply increment the variable which represents the tab */
		}
		/* Check if character is balnk space */
		else if(iC == ' '){
			iSpaces++; /* if character is blank space simply increment the variable which represents the blank space */
		}
		/* Check if character is new line */
		else if(iC == '\n'){
			iNew_Lines++; /* if character is new line simply increment the variable which represents the new line */
		}
		/* if character is a alphanumeric or special character */
		else{ 
			continue; /* if character is a alphanumeric or special character simply continue the loop */
		}
	}
		/* Print the result after calculating all blanks tabs and new lines */
		printf("\nBlanks are %d\nTabs are %d\nNew Lines are %d\n", iSpaces, iTabs, iNew_Lines);
		
		return 0;
}

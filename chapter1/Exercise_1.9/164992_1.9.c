/*
*AIM: Write a program to copy its input to its output, replacing each string of one or more blanks by a single blank.
*Author: Rushabh Goswami
*Created: 22/7/2024
*/

//Required Libraries
#include<stdio.h>

int main(){
	
	int iC; // to iterate through the given string
	int iCount = 0; // to count the sum of ascii of the continuous tabs or spaces.
	
	while((iC = getchar()) != EOF){
		//check if it is space or tab
		if(iC == ' ' || iC == '\t'){
			iCount += iC; // count the sum of ascii of spaces and tabs
		}
		else{
			// check if the iCount's value is greater than the ascii of tab (ASCII of tab is 9 and ASCII of blank space is 32).
			if(iCount >= 9){
				putchar(' '); // if multiple tabs or spaces are there only 1 blank space will be printed.
				iCount = 0; // reset the count
			}
			putchar(iC); // print if it's a character
		}
	}
	return 0;
}

/*
*AIM: Write a program to copy its input to its output, replacing each tab by \t and each backslash by \\. This makes tabs and backspaces visible in an unambiguous way. 
*Author: Rushabh Goswami
*Created: 22/7/2024
*/

/* Required Libraries */
#include<stdio.h>

int main(){
	
	int iC; /* To iterate through the given string. */
	
	printf("Enter string to convert tabs and back slash into their respective escape sequence characters:\n");
	while((iC = getchar()) != EOF){
		/* check if character is tab */
		if(iC == '\t'){
			/* put back slash there */
			putchar('\\');
			/* put t there */
			putchar('t');
		}
		/* check if character is backspace */
		else if(iC == '\b'){
			/* put backslash */
			putchar('\\');
			/* put b */
			putchar('b');
		}
		/* check if character is backslash */
		else if(iC == '\\'){
			/* put \ */
			putchar('\\');
			/* put \ */
			putchar('\\');
			
		}
		/* put other character as it is */
		else{
			putchar(iC);
		}
	}
	return 0;
}

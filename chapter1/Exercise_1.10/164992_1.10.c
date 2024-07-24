/*
*AIM: Write a program to copy its input to its output, replacing each tab by \t and each backslash by \\. This makes tabs and backspaces visible in an unambiguous way. 
*Author: Rushabh Goswami
*Created: 22/7/2024
*/

//Required Libraries
#include<stdio.h>

int main(){
	
	int iC; // To iterate through the given string.
	
	while((iC = getchar()) != EOF){
		if(iC == '\t'){
			putchar('\\');
			putchar('t');
		}
		else if(iC == '\b'){
			putchar('\\');
			putchar('b');
		}
		else if(iC == '\\'){
			putchar('\\');
			putchar('\\');
			
		}
		else{
			putchar(iC);
		}
	}
	return 0;
}

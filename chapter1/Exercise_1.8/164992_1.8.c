/*
*AIM: Write a program to count blanks, tabs, and newlines.
*Author: Rushabh Goswami
*Created: 22/7/2024
*/

//Required Libraries
#include<stdio.h>

int main(){
	
	int iC; //to iterate every character of the given string
	int iTabs = 0; // To store the count of tabs
	int iSpaces = 0; // To store the count of spaces
	int iNew_Lines = 0; // To store the count of New Lines
	
	while((iC = getchar()) != EOF){
		if(iC == '\t'){
			iTabs++;
		}
		else if(iC == ' '){
			iSpaces++;
		}
		else if(iC == '\n'){
			iNew_Lines++;
		}
		else{ 
			continue;
		}
	}
		printf("Blanks are %d\nTabs are %d\nNew Lines are %d\n", iSpaces, iTabs, iNew_Lines);
	
}

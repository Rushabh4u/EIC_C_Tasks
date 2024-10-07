/*
*AIM: Write a program to print all input lines that are longer than 8 characters.
*Author: Rushabh Goswami
*Created: 31/7/2024
*/

/* Required Libraries */
#include <stdio.h> 
#define MAXLINE 1000 /* maximum input line length */ 

int main() 
{
	char iC; /* current line length */ 
	/*int max;  maximum length seen so far */ 
	char cLine[MAXLINE]; /* current input line */ 
	int iLonger_then_8[MAXLINE]; /* longest line saved here */ 
	int iStart = 0; /* to start index of string */
	int iEnd = 0; /* to store end index of string */
	
	/* to keep track on integere array and 
	it also indicates that hoe many strings are there which are longer than 8 chars 
	and should be printd */
	int iCounter = 0; 
	
	/* print message */
	printf("Enter Text to find which line is has more than 8 characters:\n");
	
	/* Take input character by character using getchar */
	while ((iC = getchar()) != EOF)
	{
		/* check if character is newline character */
		if(iC == '\n')
		{
			/* check if line is grater than 8 characters or not */
			if(iEnd - iStart > 8)
				iLonger_then_8[iCounter++] = iStart; /* if line is longer than 8 chars then store its starting index in an integere array */
			iStart = iEnd + 1; /* set start pointer to next strings starting point */
		}
		/* add a character in string array */
		cLine[iEnd++] = iC;
	}
	/* add a new line character after input is taken and End of File character is encountered */
	cLine[iEnd] = '\n';
	
	/* again check if last line taken as input is greater than 8 chars and take starting index if it is */
	if(iEnd - iStart > 8)
		iLonger_then_8[iCounter++] = iStart;
		
	/* add new line for better output format */
	printf("\n");
	printf("\nlines that longer then 8 characters are:\n"); /* Print message */
	
	/* itrate the integer array to find all the starting index of that strings which has more than 8 chars */
	for(int iIndex = 0; iIndex < iCounter; iIndex++)
	{
		/* take a flag that takes the value of every index one by one */
		int iFlag = iLonger_then_8[iIndex];
		/* iterate from that index untill a new line character encountered */
		while(cLine[iFlag] != '\n')
		{
			/* print the string */
			printf("%c", cLine[iFlag]);
			iFlag++; /* increment to access next character of string */
		}
		/* for printing every line of output in new line */
		printf("\n");
	}
	/* when program terminates add new line */
	printf("\n");
	return 0; 
}


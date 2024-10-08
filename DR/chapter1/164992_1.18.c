/*
*AIM: Write a program to remove trailing blanks and tabs from each line of input, and to delete entirely blank lines..
*Author: Rushabh Goswami
*Created: 31/7/2024
*Modifoed: 31/7/2024
*/

/* Required Libraries */
#include <stdio.h> 
#define MAXIMUM 1000

int main()
{
	char iC;
	char cArr[MAXIMUM]; /* to store the unwanted blanks */
	int iIndex = 0; /* to iterate through array */
	int iIndex_of_Last_Word = 0; /* To keep track on last word */
	int iNLFlag = 0; /* To remove all unneccesary blank lines */
	
	/* print the message */
	printf("Enter the text to remove trailing blanks and tabs from each line:\n");
	while((iC = getchar()) != EOF)
	{
		if(iC == '\n')
		{
			
			if(iNLFlag == 0)
			{
				cArr[iIndex] = iC;
				iNLFlag = 1;
			}
			iIndex++;
			if(iNLFlag == 1)
				continue;
		}
		else
		{
			iNLFlag = 0;
			cArr[iIndex] = iC;
			if((iC == ' ' || iC == '\t') && (cArr[iIndex-1]!=' ' && cArr[iIndex-1]!='\t'))
			{
			iIndex_of_Last_Word = iIndex-1;		
			}
			iIndex++;
		}
	}
	if ((cArr[iIndex-1] != ' ') && (cArr[iIndex-1] != '\t'))
		iIndex_of_Last_Word = iIndex-1;
		
	for (iIndex = 0; iIndex <= iIndex_of_Last_Word; iIndex++)
	{
		printf("%c", cArr[iIndex]);
	}
	/* just remove this printf to see that if this code is working or not */

	return 0;
}

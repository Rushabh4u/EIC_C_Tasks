/*
Our binary search makes two tests inside the loop, when one would suffice (at the price of more tests outside.) Write a version with only one test inside the loop and measure the difference in run-time. 
Author : Rushabh Goswami
Created : 20/8/24
*/
 
/** required header files */
#include <stdio.h>
#define MAXLINE 1000

void mygetline(char cLine[], int iLineSize);

void escape(char s[], char t[]);

/** main function */
int main()
{

     char cInput[MAXLINE], cOutput[MAXLINE];

	printf("Enter String: ");		/* input message */

     mygetline(cInput, MAXLINE);	/* Input */

     escape(cInput,cOutput);		/* Function call of escape */

     printf("Escaped String: ");		/* output message */
     
     printf("\n%s\n", cOutput);		/* Print Output */
	
  return 0;
}


/*
* escape: converts characters like newline and tab into visible escape sequences like \n and \t as it copies the string Input to Output
* Author: Harsh Patel (164975)
* Created: 20/8/24
*/
void escape(char cInput[], char cOutput[]) {

    int iInputIndex = 0;		/* input array index */
    int iOutputindex = 0;	/* output array index */

    while (cInput[iInputIndex] != '\0') {	
        switch (cInput[iInputIndex]) {
        case '\t':						/* replace tab with \t */
            cOutput[iOutputindex] = '\\';	
            ++iOutputindex;
            cOutput[iOutputindex] = 't';
            break;
        case '\n':						/* replace newline with \n */
            cOutput[iOutputindex] = '\\';
            ++iOutputindex;
            cOutput[iOutputindex] = 'n';
            break;
        default:						/* for normal character */
            cOutput[iOutputindex] = cInput[iInputIndex];
            break;
        }
        ++iInputIndex;
        ++iOutputindex;
    }

    cOutput[iOutputindex] = '\0';
}

/*
* mygetline: get whole string line as input
* Author: Rushabh Goswami
* Created: 20/8/24
*/

void mygetline(char cLine[], int iLineSize) {
    int iCounter, iInput;

    for (iCounter = 0; iCounter < iLineSize - 1 && (iInput = getchar()) != EOF; ++iCounter)
        cLine[iCounter] = iInput;

    cLine[iCounter] = '\0';
}



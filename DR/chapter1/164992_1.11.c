/*
*AIM: How would you test the word count program? What kinds of input are most likely to uncover bugs if there are any? 
*Author: Rushabh Goswami
*Created: 22/7/2024
*/

/* Required Libraries */
#include <stdio.h> 

#define IN 1 /* inside a word */ 
#define OUT 0 /* outside a word */ 
 /* count lines, words, and characters in input */ 
int main() { 
	 int iC; /* for storing a single character */
	 int iNewLine; /* to store the total count of new lines */
	 int iNewWord; /* to store the total count of new words */
	 int iNewCharacter; /* to sore the total count of new characters */
	 int iState; /* it indicates the state of the cursor if its inside a word or outside */
	 
	 
/*
*****Test Cases*****
1. Add more than one space between two words
2. Add more than one newline between two words
3. Add more than one tab between two words
4. don't write anything
5. just wirte blanks
6. just wirte tabs
7. just wirte newlines
*/
	 	 
	 /* initially state is out */
	 iState = OUT; 
	 /* initially all counters are zero */
	 iNewLine = iNewWord = iNewCharacter = 0; 
	 
	 /* take input from user */
	 printf("Enter string to calculte words in it:\n\n");
	 while ((iC = getchar()) != EOF) { 
		 ++iNewCharacter; 
		 /* check if its new line */
		 if (iC == '\n') 
		 	++iNewLine; /* add a new line */
		 
		 /* check if it is outside of the word */
		 if (iC == ' ' || iC == '\n' || iC == '\t') 
		 	iState = OUT; /* change the state to out */
		 else if (iState == OUT) { /* if not outside and state is set as out */
			 iState = IN; /* change state to in */
			 ++iNewWord; /* as state changes to in add a new word */
		 }
	 }
	 /* print the output */
	 printf("nl = %d\nnw = %d\nnc = %d\n", iNewLine, iNewWord, iNewCharacter); 
	 return 0;
}


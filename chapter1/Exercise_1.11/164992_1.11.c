/*
*AIM: How would you test the word count program? What kinds of input are most likely to uncover bugs if there are any? 
*Author: Rushabh Goswami
*Created: 22/7/2024
*/

//Required Libraries
#include <stdio.h> 

#define IN 1 /* inside a word */ 
#define OUT 0 /* outside a word */ 
 /* count lines, words, and characters in input */ 
int main() { 
	 int c, nl, nw, nc, state; 
	 state = OUT; 
	 nl = nw = nc = 0; 
	 while ((c = getchar()) != EOF) { 
		 ++nc; 
		 if (c == '\n') 
		 	++nl; 
		 if (c == ' ' || c == '\n' || c == '\t') 
		 	state = OUT; 
		 else if (state == OUT) { 
			 state = IN; 
			 ++nw; 
		 }
	 }
	 printf("nl = %d\nnw = %d\nnc = %d\n", nl, nw, nc); 
	 return 0;
}

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

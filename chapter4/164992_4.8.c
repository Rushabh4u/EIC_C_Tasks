/*
* Suppose that there will never be more than one character of pushback. Modify getch and ungetch accordingly. 

*Author : Rushabh Goswami
*Created:27/8/24
*/
 
/** required header files */
#include <stdio.h>
#include <string.h>
#define MAXLINE 100
#define MAXBUF 100

void ungets(char cInput[]);
void ungetch(int iChar);
int getch();


char iBuf = '\0';			/* buffer store */

/** main function */
int main()
{
  int iRunAgain=0;      	    /* for code run again or not */

  
 do{
	
	char cInput;
	int iInpChar;
	iBuf = '\0';

	printf("Enter Input Character : ");		/* input */
	scanf("%c",&cInput);
	
	ungetch(cInput);					
	
	while ((iInpChar = getch()) != '\n')
        putchar(iInpChar);
	
	printf("\n");
	printf("Do you want to Run Again [1 for YES / 0 for NO] : "); /* Ask for code run again*/
	scanf("%d",&iRunAgain);
	getchar();
  
  }while(iRunAgain);

  return 0;
}


/*
*ungetch : removes one character and puts them into a the buffer iBuf
*Author : Harsh Patel (164975)
*Created:27/8/24
*/
void ungetch(int iChar) {
    if (iBuf)
        printf("ungetch: too many characters\n");
    else
        iBuf = iChar;
}


/*
*ungetch : the character from the buffer is read first and it is output on the screen.
*Author : Harsh Patel (164975)
*Created:27/8/24
*/
int getch(){ 
	int iChar = ((iBuf != '\0') ? iBuf : getchar());
	iBuf='\0';
	return iChar;
}





/*
*Our getch and ungetch do not handle a pushed-back EOF correctly. Decide what their properties ought to be if an EOF is pushed back, then implement your design. 

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

int iBufp = 0;				/* buffer pointer */
int iBuf[MAXBUF];			/* buffer store */

/** main function */
int main()
{
  int iRunAgain=0;      	    /* for code run again or not */

  
 do{
	
	char cInput[MAXLINE];
	int iInpChar;
	iBufp = 0;

	printf("Enter Input String : ");		/* input */
	fgets(cInput,MAXLINE,stdin);
	
	ungets(cInput);					
	
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
*ungets :  takes a string as an input and and removes one character at a time from the back of the string and puts them into a the buffer iBufp
*Author : Rushabh Goswami
*Created:27/8/24
*/
void ungets(char cInput[]) {
    int iInputIndex;

    iInputIndex = strlen(cInput);

    while (iInputIndex > 0)
        ungetch(cInput[--iInputIndex]);
}

/*
*ungetch : removes one character at a time and puts them into a the buffer iBufp
*Author : Rushabh Goswami
*Created:27/8/24
*/
void ungetch(int iChar) {
    if (iBufp >= MAXBUF)
        printf("ungetch: too many characters\n");
    else
        iBuf[iBufp++] = iChar;
}


/*
*ungetch : the characters from the buffer are read first and it is output on the screen.
*Author : Rushabh Goswami
*Created:27/8/24
*/
int getch() { return (iBufp > 0) ? iBuf[--iBufp] : getchar(); }





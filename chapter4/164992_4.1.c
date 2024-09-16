/*
*Write the function strindex(s,t) which returns the position of the rightmost occurrence of t in s, or -1 if there is none. 
*Author : Rushabh Goswami
*Created : 23/8/24
*/
 
/** required header files */
#include <stdio.h>
#define MAXLINE 1000	/* maximum input line length */
#include <ctype.h>

int mystrindex(char s[],char t[]);

/** main function */
int main()
{
  int iRunAgain=0;      	    /* for code run again or not */
  
 do{
	char cInputString[MAXLINE]={0}; 	    /* input string */
	char cInputPattern[MAXLINE]={0}; 	    /* input pattern */
	
	
	printf("Enter Input String : ");
	fgets(cInputString,MAXLINE,stdin);
	printf("Enter Input pattern : ");
	fgets(cInputPattern,MAXLINE,stdin);
	
	
	
	printf("String %s found in %s at position : %d",cInputPattern,cInputString,mystrindex(cInputString,cInputPattern));	/* function call and output */
	
	printf("\n");
	printf("Do you want to Run Again [1 for YES / 0 for NO] : "); /* Ask for code run again*/
	scanf("%d",&iRunAgain);
	getchar();
  
  }while(iRunAgain);

  return 0;
}


/* strindex: return index of t in s, -1 if none 
* Author: Rushabh Goswami
*Created : 23/8/24
*/
int mystrindex(char s[],char t[])
{
    int iSindex,iTindex,iCounter, iResult;

    iResult = -1;

    for(iSindex=0;s[iSindex]!='\n';iSindex++)
    {
        for(iTindex=iSindex,iCounter=0;t[iCounter]!='\n' && tolower(s[iTindex])==tolower(t[iCounter]);iTindex++,iCounter++);	/* increment counter uptill whole pattern get matched */
        
        if(iCounter>0 && t[iCounter] == '\n')	
            iResult = iSindex;
    }
    return iResult;
}

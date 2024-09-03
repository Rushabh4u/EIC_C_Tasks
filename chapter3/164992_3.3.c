/*
*Write a function expand(s1,s2) that expands shorthand notations like a-z in the string s1 into the equivalent complete list abc...xyz in s2. Allow for letters of either case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken literally
*Author : Rushabh Goswami
*Created : 20/8/24
*/
 
/** required header files */
#include <stdio.h>
#include <string.h>
#define INPUT_SIZE 1000

void expand(char cInput[],char cOutput[]);

/** main function */
int main()
{
  int iRunAgain=0;      	    /* for code run again or not */
  
 do{
	char cInput[INPUT_SIZE]={0}; 	    /* input array */
	char cOutput[INPUT_SIZE]={0}; 	    /* Output array */
	
	printf("Enter Input : ");
	fgets(cInput,INPUT_SIZE,stdin);
	
	
	expand(cInput,cOutput);
	
	printf("Output : %s",cOutput);
	
	printf("\n");
	printf("Do you want to Run Again [1 for YES / 0 for NO] : "); /* Ask for code run again*/
	scanf("%d",&iRunAgain);
	getchar();
  
  }while(iRunAgain);

  return 0;
}



/*
* max: expands shorthand notations like a-z in the string Input into the equivalent complete list abc...xyz in Output.
* Author: Harsh Patel (164975)
* Created: 23/7/24
* Modified: 23/7/24
*/
void expand(char cInput[],char cOutput[]){

	int iInputIndex = 0;
	int iOutputIndex = 0;
	
	while((cInput[iInputIndex]<48 || (cInput[iInputIndex]>=58 && cInput[iInputIndex]<=64) || (cInput[iInputIndex]>=91 && cInput[iInputIndex]<=96) || cInput[iInputIndex]>122) && cInput[iInputIndex]!='\n')
		iInputIndex++;				/* skip leading '-' */
	
	
	while(cInput[iInputIndex]!='\n'){
	
		int iStart = cInput[iInputIndex++];   /* for start */
		
		while(((cInput[iInputIndex]=='-' && cInput[iInputIndex+1]!='-') || (cInput[iInputIndex]!='-' && cInput[iInputIndex+1]=='-')) && cInput[iInputIndex+1]!='\n')
			iInputIndex++;					/* for end */
			
		int iEnd = cInput[iInputIndex++];
	
		while(iStart<=iEnd){				/* store from start to end */
			cOutput[iOutputIndex]=iStart;
			iOutputIndex++;
			iStart++;
		}

	
	}

}

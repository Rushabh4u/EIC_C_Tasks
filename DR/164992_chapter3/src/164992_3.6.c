/*
*In a two's complement number representation, our version of itoa does not 
handle the largest negative number, that is, the value of n equal to -(2wordsize-1). Explain why 
not. Modify it to print that value correctly, regardless of the machine on which it runs. 
*Author : Rushabh Goswami
*Created:21/8/24
*/
 
/** required header files */
#include <stdio.h>
#include <string.h>
#define MAX_SIZE 1000
void reverse(char cStr[]);
void itoa(int n, char s[],int iMinFieldWidth);

/** main function */
int main()
{
  int iRunAgain=0;      	    /* for code run again or not */
  
 do{
 
 	int iInput;			/* Input  */
 	char cOutput[MAX_SIZE];	/* Output  */
 	int iMinFieldWidth;
	
	printf("Enter Number  : ");	
	scanf("%d",&iInput);
	printf("Enter Min Field width  : ");	
	scanf("%d",&iMinFieldWidth);
	
	itoa(iInput,cOutput,iMinFieldWidth);	/* Function call of itoa */
	
	printf("Ans : %s",cOutput);
	
	printf("\n");
	printf("Do you want to Run Again [1 for YES / 0 for NO] : "); /* Ask for code run again*/
	scanf("%d",&iRunAgain);
	getchar();
  
  }while(iRunAgain);

  return 0;
}


/*reverse: reverse string s in place 
* Author: Rushabh Goswami
*Created:21/8/24
*/
void reverse(char cStr[]) {
    int i, j;
    char cTemp;
    for (i = 0, j = strlen(cStr)-1; i < j; i++, j--) {
        cTemp = cStr[i];
        cStr[i] = cStr[j];
        cStr[j] = cTemp;
    }
}


/* itoa: convert n to characters in s 
* Author: Rushabh Goswami
*Created:21/8/24
*/
void itoa(int iInput, char cOutput[],int iMinFieldWidth) {
    int iCounter, isign;
    unsigned int uinum;

    isign = iInput;
    if (iInput < 0) {
        uinum = -iInput; // Convert to positive using unsigned int
    } else {
        uinum = iInput;
    }

    iCounter = 0;
    do {
        cOutput[iCounter++] = uinum % 10 + '0'; // Get next digit
    } while ((uinum /= 10) > 0); // Delete it

    if (isign < 0) {
        cOutput[iCounter++] = '-'; // Add sign
    }
    
    while(iCounter<iMinFieldWidth){
    		cOutput[iCounter++] = ' ';
    }
    
    cOutput[iCounter] = '\0';
    reverse(cOutput); // Reverse the string
}

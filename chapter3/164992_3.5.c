/*
*Write the function itob(n,s,b) that converts the integer n into a base b
character representation in the string s. In particular, itob(n,s,16) formats s as a 
hexadecimal integer in s. 
*Author : Rushabh Goswami
*Created:21/8/24
*/
 
/** required header files */
#include <stdio.h>
#include <string.h>
#define MAX_SIZE 1000
void reverse(char cStr[]);
void itob(int n, char s[],int iBase);

/** main function */
int main()
{
  int iRunAgain=0;      	    /* for code run again or not */
  
 do{
 
 	int iInput;			/* Input  */
 	int iBase;			/* Input  */
 	char cOutput[MAX_SIZE];	/* Output  */
	
	printf("Enter Number  : ");	
	scanf("%d",&iInput);
	printf("Enter Base  : ");	
	scanf("%d",&iBase);
	
	if(iBase<=0){
		printf("\nERROR : Enter valid Base");
		return 0;
	}
	
	itob(iInput,cOutput,iBase);	/* Function call of itoa */
	
	printf("String Number : %s",cOutput);
	
	printf("\n");
	printf("Do you want to Run Again [1 for YES / 0 for NO] : "); /* Ask for code run again*/
	scanf("%d",&iRunAgain);
	getchar();
  
  }while(iRunAgain);

  return 0;
}


/*reverse: reverse string s in place 
* Author: Harsh Patel (164975)
* Created: 23/7/24
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


/* itob: convert n to characters in s with base b
* Author: Harsh Patel (164975)
* Created: 23/7/24
*/
void itob(int iInput, char cOutput[],int iBase) {
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
        cOutput[iCounter++] = ((uinum % iBase) <=9)?(uinum % iBase + '0'):(uinum % iBase + 'A' - 10); // Get next digit
        
    } while ((uinum /= iBase) > 0); // Delete it

    if (isign < 0) {
        cOutput[iCounter++] = '-'; // Add sign
    }
    cOutput[iCounter] = '\0';
    reverse(cOutput); // Reverse the string
}

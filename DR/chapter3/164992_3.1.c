/**Our binary search makes two tests inside the loop, when one would suffice (at the price of more tests outside.) Write a version with only one test inside the loop and measure the difference in run-time. 
Author : Rushabh Goswami
Created : 20/8/24
*/
 
/* required header files */
#include <stdio.h>
#include <ctype.h>
#include "error_handling.h"
#define MAX_SIZE 100

int binsearch(int iX, int iInput[], int iN);

/* main function */
int main()
{
  	int choice;
  	do
  	{
		int iInput[MAX_SIZE];	    /* value of x input*/
		int index;
		int n; 
		int extra;
		int counter = 0;
		
		printf("How many elements do you want to enter? (max size is %d): ", MAX_SIZE);
		if( scanf("%d", &n) != 1 )
		{
			handle_error(ERROR_INVALID_INPUT);
			return -1;
		}
		while((extra = getchar()) != '\n')
		{
			if(extra != ' ')
				counter--;
		}
		
		if(counter < 0)
		{
			handle_error(ERROR_MORE_THAN_EXPECTED);
			printf("\nPLease listen carefully!!!\n");
			return -1;
		}
		counter = n;
		if(n < 1 || n > MAX_SIZE)
		{
			handle_error(ERROR_OUT_OF_RANGE);
			printf("\nPLease listen carefully!!!\n");
			return -1;
		}
		
		printf("Enter %d space separated elements in sorted manner: ", n);
		for(index = 0; index < n; index++)
		{
			
			if( scanf("%d", &iInput[index]) != 1 )
			{
				handle_error(ERROR_INVALID_INPUT);
				return -1;
			}
			counter--;
			if(index>0 && iInput[index] < iInput[index-1])
			{
				printf("The elements are not sorted. Please listen carefully!!!\n");
				return -1;
			} 
			
		}
		
		while((extra = getchar()) != '\n')
		{
			if(extra != ' ')
				counter--;
		}
		
		if(counter < 0)
		{
			handle_error(ERROR_MORE_THAN_EXPECTED);
			printf("\nPLease listen carefully!!!\n");
			return -1;
		}
		
		printf("Array : [");
		for(int iCounter = 0; iCounter < n-1; iCounter++){
			printf("%d, ",iInput[iCounter]);
		}
		printf("%d]\n", iInput[n-1]);
		
		int iFindNum;
		printf("Enter Num : ");
		if(scanf("%d",&iFindNum) != 1)
		{
			handle_error(ERROR_INVALID_INPUT);
			return -1;
		}
		
		counter = 0;
		while((extra = getchar()) != '\n')
		{
			if(extra != ' ')
				counter--;
		}
		
		if(counter < 0)
		{
			handle_error(ERROR_MORE_THAN_EXPECTED);
			printf("\nPLease listen carefully!!!\n");
			return -1;
		}
		
		int ans = binsearch(iFindNum, iInput, n) ;
		(ans != -1) ? printf("%d is Present in Array at position %d\n",iFindNum, ans+1) : printf("%d is Not Present in Array\n",iFindNum);
		
		
		
	printf("\nRe-Run? (1 for yes/ 0 fro no): ");
		if (scanf("%d", &choice) != 1)
		{
			handle_error(ERROR_INVALID_INPUT);
			return 1;
		}
	}while(choice == 1);

  return 0;
}


int binsearch(int iX, int iInput[], int iN) {
    int iLow, iHigh, iMid;

    iLow = 0;
    iHigh = iN - 1;

    iMid = (iLow + iHigh) / 2;

    while (iLow < iHigh && iX != iInput[iMid]) {
        if (iX > iInput[iMid])
            iLow = iMid + 1;
        else
            iHigh = iMid - 1;

        iMid = (iLow + iHigh) / 2;
    }

    if (iX == iInput[iMid])
        return iMid;
    else
        return -1;
}

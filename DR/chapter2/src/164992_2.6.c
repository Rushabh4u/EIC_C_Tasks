/*
*AIM : Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p set to the rightmost n bits of y, leaving the other bits unchanged.
*Author : Rushabh Goswami
*Created : 7/8/2024
*/

/* required header files */
#include <stdio.h>

#define INPUT_SIZE 50
 
int setbits(int iX, int iP, int iN, int iY);	
 
/** main function */
int main()
{
  int iRunAgain=0;      	    /* for code run again or not */

 
do{
	int iX;	    /* value of x */
	int iY;	    /* value of y */
	int iP;	    /* value of position */
	int iN;	    /* value of xnumber of bits */
	
	/* Input */
	printf("Enter X : ");
	scanf("%d",&iX);
	
	printf("Enter Y : ");
	scanf("%d",&iY);	
	
	printf("Enter P : ");
	scanf("%d",&iP);	
	
	printf("Enter N : ");
	scanf("%d",&iN);
	
	
	if(iX<0 || iY<0)
	{
		printf("Enter positive value \n");
	}
	else if(iP-iN<0)
	{
		printf("Insufficient bits. N should be >= P + 1 \n");
	}
	else
	{
	/* function call */
	printf("New X : %d",setbits(iX,iP,iN,iY));	
	}
	printf("\n");
	
	printf("Do you want to Run Again [1 for YES / 0 for NO] : "); /* Ask for code run again*/
	scanf("%d",&iRunAgain);
	
	getchar();
  }while(iRunAgain);
 
  return 0;
}
 
 
int setbits(int iX,int iP,int iN,int iY){	/* function deffination */
 
	int iMask = (1 << iN) - 1;        
	int iNbitofy = iY & iMask;	
		
	iNbitofy = iNbitofy << (iP-1);
		
	int iMaskOfX = ~(iMask<<(iP-1));	
	
	iX = iX & iMaskOfX;				
	iX = iX | iNbitofy;	
	printf("--------------\n");
	
	return iX;
}

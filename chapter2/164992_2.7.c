/*
*AIM : Write a function invert(x,p,n) that returns x with the n bits that begin at position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.
*Author : Rushabh Goswami
*Created : 7/8/24
*/


/* required header files */
#include <stdio.h>
#define INPUT_SIZE 50
 
int invert(int iX,int iP,int iN);
 
/* main function */
int main()
{
  int iRunAgain=0;      	    /* for code run again or not */

 
do{
	int iX;	    /* value of x input*/
	int iP;	    /* value of position*/
	int iN;	    /* value of number of bits */
	
	
	printf("Enter X : ");
	scanf("%d",&iX);
	
	printf("Enter P : ");
	scanf("%d",&iP);	
	
	printf("Enter N : ");
	scanf("%d",&iN);
	
	
	/* input validation */
	if(iX<0)
	{
		printf("Enter positive value \n");
	}else if(iP-iN<0)
	{
		printf("Insufficient bits. N should be >= P + 1 \n");
	}else
	{
		printf("New X : %d",invert(iX,iP,iN));	
	}
	printf("\n"); 
	
	printf("Do you want to Run Again [1 for YES / 0 for NO] : "); /* Ask for code run again*/
	scanf("%d",&iRunAgain);
	
	getchar();
  }while(iRunAgain);
 
  return 0;
}
 
 
int invert(int iX,int iP,int iN){
 
	int iMask = (1 << iP) - 1;				/* mask for extract iN bit from iN at position iP */
	iMask = iMask << iN;					/* add padding */
	int iInvertBitsofx = ~(iX & iMask);		/* extract bits of iX using mask and invert it */
 
	iInvertBitsofx = iInvertBitsofx & iMask;	/* set off extra bits using mask*/
 
	iX = iX & ~(iMask);						/* set off bits using mask */
 
	iX = iX | iInvertBitsofx;				/* add inverted bits */
	printf("--------------\n");
	
	return iX;
 
}

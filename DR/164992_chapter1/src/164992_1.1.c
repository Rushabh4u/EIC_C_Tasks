/*
*This program is just for Experiment with leaving out parts of the Hello World! program, to see what error messages we get.
*Author: Rushabh Goswami
*Created: 18/7/2024
*Modified: 18/7/2024
*/

/* Required libraries */
#include<stdio.h>

int main(){
	char cChoice; /* for tacking user's concern to run the the function or not. */
	
	
		printf("Do you want to execute this Hello World! program (y/n): "); /* UI instruction */
		scanf("%c", &cChoice); /* Taking user input either y for Yes or n for No. */
		if(cChoice == 'y'){
			printf("\nHello World!\n\n"); /* Prints the message whatever you want */
		}
		else if(cChoice == 'n'){
			printf("\nProgram terminated\n\n");
		}
		else{
			printf("\nInvalide input!!! Please enter valid choice.\n\n");	
		}
		return 0;
}	

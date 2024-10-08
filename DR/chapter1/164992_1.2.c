/*
*Experiment to find out what happens when prints's argument string contains \c, where c is some character not listed above.
*Author: Rushabh Goswami
*Created: 18/7/2024
*Modified: 18/7/2024
*/

//Required Libraries
#include<stdio.h>

int main(){

	char cChoice; /* For storing user's choice */
	
	printf("Do you want to check what happens when printf's argument string contains \c? (y/n): ");
	scanf("%c", &cChoice);
	
	if(cChoice == 'y')
		printf("\nit simply prints \c \n\n");
	else if(cChoice == 'n')
		printf("\nProgram terminated.\n\n");
	else
		printf("\nInvalid input!!! PLease enter valid input.\n\n");
	return 0;
}

/*
*AIM: Program to print the corresponding Celsius to Fahrenheit table. 
*Author: Rushabh Goswami
*Created: 22/7/2024
*/

/* Required Libraries */
#include<stdio.h>
#include "error_handling.h"

	/*Print Fahrenheit-Celsius table*/
int main(){
	

	
	
	 float fFahr, fCelsius; /* to storing temparature */
	 int iChoice; /* indicates the choice of the user whethere hi/she is want to rerun the program or not. */
	 
	 do
	 {
	 	/* take input and check if it valid or not */
		 printf("C = ");
		 if(scanf("%f", &fCelsius) != 1) /*  CHecks if the given input is valid or not */ 
		 {
		 	handle_error(ERROR_INVALID_INPUT);
		 	return 1;
		 } 
		 
		 
		/* Logic of temparature conversion */
		 fFahr = ((9.0/5.0) * (fCelsius))+32; 
		 printf("F = %3.0f\n", fFahr); 

		/* Taking user concern to re-run the program */
		 printf("\nDo you want to Re-run the program? Press(1 for yes/0 for no): ");
		 if(scanf("%d", &iChoice) != 1)
		 {
		 	handle_error(ERROR_INVALID_INPUT);
		 	return 1;
		 }
	} 
	while(iChoice == 1);

	return 0;
}

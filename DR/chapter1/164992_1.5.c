/*
*AIM: Modify the temperature conversion program to print the table in reverse order, that is, from upperbond to lower bond. 
*Author: 
*Created: 
*/

//Required Libraries
#include<stdio.h>
#include "error_handling.h"
	/*Print the table in reverse order. */
int main(){
	
	float fFahr; /* indicates the respective fahrenheit */
	float fUpper; /* indicates upper bound of the temparature */
	float fLower; /* indicates the lower bound of the temparature */
	float fSteps; /* indicate the steps to jump from starting point to the ending point of the program */
	int iChoice; /* indicates the choice of the user whethere hi/she is want to rerun the program or not. */
	 
	 do
	 {
	 
		 printf("Enter the lower value of the table: ");
		 if(scanf("%f", &fLower) != 1) /*  CHecks if the given input is valid or not */ 
		 {
		 	handle_error(ERROR_INVALID_INPUT);
		 	return 1;
		 } 
		 
		 printf("Enter the upper value of the table: ");
		 if(scanf("%f", &fUpper) != 1) /*  CHecks if the given input is valid or not */ 
		 {
		 	handle_error(ERROR_INVALID_INPUT);
		 	return 1;
		 } 
		 
		 printf("Enter the value of the steps you want to jump: ");
		 if(scanf("%f", &fSteps) != 1) /* CHecks if the given Step size is valid or not */
		 {
		 	handle_error(ERROR_INVALID_INPUT);
		 	return 1;
		 } 
		 if(fSteps <= 0) /* check if steps are 0 because it leads to infinite execution of the code */
		 {
		 	handle_error(ERROR_INVALID_INPUT);
		 	return 1;
		 }
		 
		 if(fUpper < fLower) /* check if upper value is less than the lower value. If it is then reverse jump is not allowed in this program */
		 {
		 	handle_error(ERROR_INVALID_INPUT);
		 	return 1;
		 }
		 
		 if(fSteps > (fUpper - fLower)) /* Checks if step count is greater than the range of lower bound and upper bound */
		 {
		 	handle_error(ERROR_STEP_TOO_LARGE);
		 	return 1;
		 }
		 
		 fFahr = fLower; 
		 
		 /*  */
		 printf("Fahrenheit\t\tCelsius\n");
		for(fFahr = fUpper; fFahr >= fLower; fFahr -= fSteps){
			printf("%.2f\t\t\t%.2f\n", fFahr, (5.0/9.0)*(fFahr-32));
		
		}
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

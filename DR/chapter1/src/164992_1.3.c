/*
*Modify the temperature conversion program to print a heading above the table.
*Author: Rushabh Goswami
*Create: 18/7/2024
*Modified: 18/7/2024
*/

/*Required libraries*/
#include <stdio.h> 
#include "error_handling.h"
 /* print Fahrenheit-Celsius table 
 for fFahr = 0, 20, ..., 300; floating-point version */ 
 int main() 
 { 
	 float fFahr, fCelsius; /* to storing temparature */
	 float fLower;/* fLower indicates from where the table starts */
	 float fUpper;/* fUpper indicates from where the table ends */
	 float fStep; /* fStep indicates how many jumps of number should be there */
	 int iChoice; /* indicates the choice of the user whethere hi/she is want to rerun the program or not. */
	 
	 do
	 {
	 
		 printf("Enter the lower value of Lowerthe table: ");
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
		 if(scanf("%f", &fStep) != 1) /* CHecks if the given Step size is valid or not */
		 {
		 	handle_error(ERROR_INVALID_INPUT);
		 	return 1;
		 } 
		 if(fStep <= 0) /* check if steps are 0 because it leads to infinite execution of the code */
		 {
		 	handle_error(ERROR_INVALID_INPUT);
		 	return 1;
		 }
		 
		 if(fUpper < fLower) /* check if upper value is less than the lower value. If it is then reverse jump is not allowed in this program */
		 {
		 	handle_error(ERROR_INVALID_INPUT);
		 	return 1;
		 }
		 
		 if(fStep > (fUpper - fLower)) /* Checks if step count is greater than the range of lower bound and upper bound */
		 {
		 	handle_error(ERROR_STEP_TOO_LARGE);
		 	return 1;
		 }
		 
		 fFahr = fLower; 
		 
		 printf("Fahrenheit\tCelsius\n");
		 
		 while (fFahr <= fUpper) { 
			 fCelsius = (5.0/9.0) * (fFahr-32.0); 
			 printf("%3.0f\t\t%6.1f\n", fFahr, fCelsius); 
			 fFahr = fFahr + fStep; 
		 }
		 printf("\nDo you want to Re-run the program? Press(1 for yes/0 for no): ");
		 if(scanf("%d", &iChoice) != 1)
		 {
		 	handle_error(ERROR_INVALID_INPUT);
		 	return 1;
		 }
	} 
	while(iChoice == 1);
	 
 } 

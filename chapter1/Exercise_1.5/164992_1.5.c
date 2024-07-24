/*
*AIM: Modify the temperature conversion program to print the table in reverse order, that is, from 300 degrees to 0. 
*Author: 
*Created: 
*/

//Required Libraries
#include<stdio.h>
	/*Defining some constants*/
#define STEP 20 //step size to jump
#define UPPER 300 //Upper limit
#define LOWER 0 //Lower limit
	/*Print the table in reverse order. */
int main(){
	
	int Ifahr;
	
	printf("Fahrenheit\tCelsius\n");
	for(Ifahr = UPPER; Ifahr >= LOWER; Ifahr -= STEP){
		printf("%3d\t\t%6.2f\n", Ifahr, (5.0/9.0)*(Ifahr-32));
	}
	return 0;
}

/*
*AIM: Program to print the corresponding Celsius to Fahrenheit table. 
*Author: Rushabh Goswami
*Created: 22/7/2024
*/

//Required Libraries
#include<stdio.h>

	/*Print Fahrenheit-Celsius table*/
int main(){
	
	int Ifahr;
	printf("Fahrenheit\tCelsius\n");
	for(Ifahr = 0; Ifahr <= 300; Ifahr += 20){
		printf("%3d\t\t%6.1f\n", Ifahr, (5.0/9.0)*(Ifahr-32));
	}
	return 0;
}

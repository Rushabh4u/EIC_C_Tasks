/*
*AIM: Write a program to print a histogram of the frequencies of different characters in its input.
*Author: Rushabh Goswami
*Created: 23/7/2024
*/

//Required Libraries
#include<stdio.h>

#define SIZE 94 // maximum size of the array

int main(){
	
	int iC;
	char arr[SIZE] = {0}; // character array to store distict characters in the given string
	int iCount = 0; // to count the frequency of character
	
	while((iC = getchar()) != EOF)
		arr[iC - 33]++;
	
	for(int i = 0; i < SIZE; i++){
		if(arr[i] > 0){
			printf("\n%c : ", i+33);
			while(arr[i] != 0){
				putchar('*');
				arr[i]--;
			}
		}
	}	
	putchar('\n');
	return 0;
}

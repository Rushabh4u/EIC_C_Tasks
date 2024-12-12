/* 
*this program made for recresive form of reverse str
Author: Rushabh Goswami
created date: 29/8/2024
*/
 
/*required header files*/
/*stdio for input output function*/
#include <stdio.h>
#include <string.h>
#define INPUT_SIZE 1000
/*MAIN function*/
 
void reverse(char* cInput,int start,int end){
char temp;
temp=cInput[end];
cInput[end]=cInput[start];
cInput[start]=temp;
if(start>=end)
  return;
else
  reverse(cInput,start+1,end-1);   
}
 
int main(){ /*main function start*/
 
  char cInput[INPUT_SIZE];
  printf("Enter String:");
  fgets(cInput,INPUT_SIZE,stdin);
  reverse(cInput,0,strlen(cInput) - 1);
  printf("AFter Reversing String:");
  printf("%s",cInput);

 
}/*main function end*/
 
/*program end*/

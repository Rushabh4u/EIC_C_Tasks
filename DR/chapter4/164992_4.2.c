/*
*Extend atof to handle scientific notation of the form 123.45e-6 where a floating-point number may be followed by e or E and an optionally signed exponent.  
*Author : Rushabh Goswami
*Created : 23/8/24
*/
 
/** required header files */
#include <stdio.h>
#define MAXLINE 1000	/* maximum input line length */
#include <ctype.h>
#include <math.h>


double atof(char s[]);

/** main function */
int main()
{
  int iRunAgain=0;      	    /* for code run again or not */
  
 do{
	char cInputString[MAXLINE]={0}; 	    /* input string */
	printf("Enter Input : ");
	fgets(cInputString,MAXLINE,stdin);	
	
	printf("Output : %f",atof(cInputString));
	
	printf("\n");
	printf("Do you want to Run Again [1 for YES / 0 for NO] : "); /* Ask for code run again*/
	scanf("%d",&iRunAgain);
	getchar();
  
  }while(iRunAgain);

  return 0;
}


/* atof: converts the string s to its double precision floating-point equivalent.
* Author: Rushabh Goswami
*Created : 23/8/24
*/
double atof(char s[]) 
{ 
	 double val, power=1.0; 
	 int i, sign=1; 
	 
	 for (i = 0; isspace(s[i]); i++); /* skip white space */ 
	  
	 sign = (s[i] == '-') ? -1 : 1; 	/* sign of number */
	 
	 if (s[i] == '+' || s[i] == '-') 	/* skip the sign */
	 	i++; 
	 	
	 for (val = 0.0; isdigit(s[i]); i++)	/* char to int */
	 	val = 10.0 * val + (s[i] - '0'); 
	 
	 	
	 if (s[i] == '.') 				/* skip '.' */
	 	i++; 
	 	
	 for (power = 1.0; isdigit(s[i]); i++) {  /* after '.' convertion */
	 	val = 10.0 * val + (s[i] - '0'); 
	 	power *= 10; 
	 }
	 
	 if(s[i]=='e'){				/* after 'e' portion */
	 	i++;
	 	if(s[i]=='+'){
	 		i++;
	 		power/=pow(10,s[i]-'0');
	 	}else if(s[i]=='-'){
	 	    i++;
	 		power*=pow(10,s[i]-'0');
	 	
	 	}else{
	 	    power/=pow(10,s[i]-'0');
	 	}
	 }
	
	 return sign * val / power; 
}

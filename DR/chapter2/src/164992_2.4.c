/*
*AIM: Write an alternative version of squeeze(s1,s2) that deletes each character in s1 that matches any character in the string s2.
*Author: Rushabh Goswami 
*Created: 7/8/2024
*/

/* Required Libraries */
#include <stdio.h> 
#include <string.h>
#include "error_handling.h"


#define MAKS 500



/* squeeze: delete all c from s */ 
 void squeeze(char s1[], char s2[]) 
{ 
	 int i, j; 
	int iSkip[127] = {0};
	int iChange;
	 
	 for (i = 0; s2[i] != '\0'; i++)
	 	
	 {
	 	for(j = 0; s1[j] != '\0'; j++) 
		{
			 if (s2[i] == s1[j]) 
			{
				if (s2[i] >= 'A' && s2[i]<= 'Z')
				{
					iChange = s2[i];
					iSkip[iChange] = 1;
					iSkip[iChange+32] = 1;
				}
				else if (s2[i] >= 'a' && s2[i] <= 'z')
				{
					iChange = s2[i];
					iSkip[iChange] = 1;
					iSkip[iChange-32] = 1;
				}
				else
				{
					iChange = s2[i];
					iSkip[iChange] = 1;
				}
			}	 
		} 
	}
		int len = strlen(s1);
		i = 0;
		while (i < len)
		{
			iChange = s1[i];
			if ( iSkip[iChange] == 0  )
			{
				printf("%c", s1[i]);
			}
			i++;
		}
}


int main()
{
		char cS1[MAKS];
		char cS2[MAKS];
		//int iIndex = 0;
		
		printf("Enter Firest String: ");
		fgets(cS1, MAKS, stdin);
		
		printf("Enter Sencond String: ");
		fgets(cS2, MAKS, stdin);
		
		squeeze(cS1, cS2);
		printf("\n");
		 

    return 0;
}


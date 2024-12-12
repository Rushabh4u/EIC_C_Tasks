/*
*Write a program to check a C program for rudimentary syntax errors like unmatched parentheses, brackets and braces. Don't forget about quotes, both single and double, escape sequences, and comments
*Author : Rushabh Goswami
*Created : 31/7/24
*Modified: 31/7/2024
 */
 
 
/* required header file */
#include <stdio.h>
#include <stdbool.h>
#define MAXcInput 1000
 
void check_syntax(char cInput[]);
 
/* main function */
int main(void)
{
  char cInput[MAXcInput];           /* input array */
  printf("Enter Input : ");
  fgets(cInput,MAXcInput,stdin);
  check_syntax(cInput);
 
  return 0;
}
 
/*
* check_syntax : check weather given string have balanced parentheses, brackets and braces or not
* author : Rushabh Goswami
* Created : 31/7/24
*/
 
void check_syntax(char cInput[])
{
  int iParentheses = 0;			/* parentheses count () */
  int iBrackets = 0;			/* brackets count [] */
  int iBraces = 0;				/* braces count {} */
 
  bool bSingle_quotes = false;	/* single_quotes flag */
  bool bDouble_quotes = false;	/* double_quotes flag */
 
  bool bBlock_comment = false;	/* block_comment flag */
  bool bLine_comment = false;		/* line_comment flag */
 
  int iCounter = 0;				/* string traversal */
  while (cInput[iCounter] != '\0' && iParentheses >= 0 && iBrackets >= 0 && iBraces >= 0)		/* loop until end of string */
  {
    /* for non-comment and non-quoted line */
    if (!bLine_comment && !bBlock_comment && !bSingle_quotes && !bDouble_quotes)	
    {
    	 /* count parentheses */
      if (cInput[iCounter] == '(')
      {
        ++iParentheses;
      }
      else if (cInput[iCounter] == ')')
      {
        --iParentheses;
      }
 
      if (cInput[iCounter] == '[')
      {
        ++iBrackets;
      }
      else if (cInput[iCounter] == ']')
      {
        --iBrackets;
      }
 
      if (cInput[iCounter] == '{')
      {
        ++iBraces;
      }
      else if (cInput[iCounter] == '}')
      {
        --iBraces;
      }
    }
    /* for quoted strings */
    if (!bLine_comment && !bBlock_comment)
    {
      if (cInput[iCounter] == '\'' && !bSingle_quotes && !bDouble_quotes)	/* single quote start flag */
      {
        bSingle_quotes = true;
      }
      else if (bSingle_quotes && cInput[iCounter] == '\'')	/* single quote end flag */
      {
        bSingle_quotes = false;
      }
 
      if (cInput[iCounter] == '"' && !bSingle_quotes && !bDouble_quotes)	/* double quote start flag */
      {
        bDouble_quotes = true;
      }
      else if (bDouble_quotes && cInput[iCounter] == '"')	/* double quote end flag */
      {
        bDouble_quotes = false;
      }
    }

    /* for commented string */
    if (!bSingle_quotes && !bDouble_quotes)
    {
      if (cInput[iCounter] == '/' && cInput[iCounter + 1] == '*' && !bLine_comment)	/* block comment start flag */
      {
        bBlock_comment = true;
      }
      else if (cInput[iCounter] == '*' && cInput[iCounter + 1] == '/')	/* block comment end flag */
      {
        bBlock_comment = false;
      }
 
      if (cInput[iCounter] == '/' && cInput[iCounter + 1] == '/' && !bBlock_comment)	/* line comment start flag */
      {
        bLine_comment = true;
      }
      else if (cInput[iCounter] == '\n')	/* line comment end flag */
      {
        bLine_comment = false;
      }
    }
 
    ++iCounter;
  }
 
 
  /* check for accrued errors */
  if (iParentheses)
  {
    printf("\nError: unbalanced parentheses.");
  }
 
  if (iBrackets)
  {
    printf("\nError: unbalanced brackets.");
  }
 
  if (iBraces)
  {
    printf("\nError: unbalanced braces.");
  }
 
  if (bSingle_quotes)
  {
    printf("\nError: unbalanced single quotes.");
  }
 
  if (bDouble_quotes)
  {
    printf("\nError: unbalanced double quotes.");
  }
 
  if (bBlock_comment)
  {
    printf("\nError: block comment not closed.");
  }
}

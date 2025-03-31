/*
 * Program: String Concatenation
 * Author: 164993_faizan_momin
 * Created Date: 16/12/2024
 * Description: This program demonstrates a simple string concatenation operation using custom functions.
 *              The user is prompted to input two strings, which are then concatenated and printed.
 */

/* Required header files */
#include <stdio.h>  /* For input/output functions */

/* Constant definition */
#define MAXLINE 1000 /* Maximum line length */

/* Function prototypes */
int mgetline(char line[], int lim);   /* Read a line of input */
void mystrcat(char *s, char *t);      /* Concatenate string t to string s */

/* Main function */
int main(void) {
    
    char s[MAXLINE], t[MAXLINE];  /* Arrays to hold input strings */

    /* Prompt user for the first string */
    putchar('s');
    putchar(':');
    mgetline(s, MAXLINE);  /* Read the first string into s */

    /* Prompt user for the second string */
    putchar('t');
    putchar(':');
    mgetline(t, MAXLINE);  /* Read the second string into t */

    /* Concatenate the strings */
    mystrcat(s, t);

    /* Print the concatenated result */
    printf("%s\n", s);

    return 0;  /* Exit the program successfully */
}

/*
 * mgetline: Read a line from input and store it in `line[]`.
 * Arguments:
 *   line - Array to store the input string
 *   lim - Maximum number of characters to read
 * Returns:
 *   The number of characters read
 */
int mgetline(char line[], int lim) {
    int c, i;

    /* Read characters until the limit or end of input is reached */
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        line[i] = c;

   
  

    /* Null-terminate the string */
    line[i] = '\0';

    return i;  /* Return the number of characters read */
}

/*
 * mystrcat: Concatenate string t to the end of string s.
 * Arguments:
 *   s - The destination string
 *   t - The string to append to s
 */
void mystrcat(char *s, char *t) {
    /* Move to the end of the first string s */
    while (*s != '\0')
        s++;

    /* Append string t to the end of s */
    while ((*s = *t) != '\0') {
        s++;  /* Move to the next character in s */
        t++;  /* Move to the next character in t */
    }
}


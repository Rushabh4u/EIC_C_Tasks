/*
 * This program prints arbitrary input in a sensible way. Non-graphic characters 
 * are printed in octal format, and long text lines are broken sensibly.
 * Create by: Rushabh Goswami
 * Created on : 10/12/2024
 */

/* Required Libraries */
#include <ctype.h>  /* Character type handling library */
#include <stdio.h>  /* Standard Input/Output library */

/* Defining constants */
#define MAXLINE 100 /* Maximum number of characters in one line */
#define OCTLEN 6    /* Length of an octal value */

/* Function to increment the position counter for output */
int inc(int iPosition, int iCount)
{
    if (iPosition + iCount < MAXLINE)
        return iPosition + iCount;
    else
    {
        putchar('\n'); /* Break the line */
        return iCount;
    }
}

/* Main function */
int main(void)
{
    int iChar, iPosition; /* Variables to store character and position */

    iPosition = 0; /* Initialize position in the line */

    printf("Enter text (Press Ctrl+D to end):\n");

    /* Process input characters until EOF */
    while ((iChar = getchar()) != EOF)
    {
        if (iscntrl(iChar) || iChar == ' ')
        {
            /* Handle non-graphic or blank character */
            iPosition = inc(iPosition, OCTLEN);
            printf("\\%03o", iChar); /* Print character in octal format */
            if (iChar == '\n')       /* Handle newline character */
                iPosition = 0;
        }
        else
        {
            /* Handle graphic character */
            iPosition = inc(iPosition, 1);
            putchar(iChar);
        }
    }

    return 0;
}


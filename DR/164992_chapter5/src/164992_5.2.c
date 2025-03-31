/*
 * Program: Get Next Float from Input
 * Author: 164993_faizan_momin
 * Created Date: 16/12/2024
 * Description: This program defines a function `getfloat` that reads the next floating-point number from the input
 *              and stores it in the provided pointer. The program also handles handling input characters using a buffer.
 */

/* Required header files */
#include <stdio.h>  /* For input/output functions */
#include <ctype.h>  /* For character classification functions */

/* Constant definitions */
#define SIZE 1000   /* Maximum size of the array to store floats */

/* Function prototypes */
int getch(void);            /* Get the next character from input */
void ungetch(int c);        /* Push a character back into the input buffer */
int getfloat(float *pn);    /* Read the next float from input */

/* Main function */
int main(void) {
    int n;               /* Loop counter */
    float array[SIZE];   /* Array to store the floats */

    /* Read floats into the array */
    int last_char;
    for (n = 0; n < SIZE; n++) {
        /* Print the floats in reverse order */
        last_char=getfloat(&array[n]) ;
    	if(last_char==-1){
    			printf("Invalid Input Enter.");
    			return -1;
    	}
    	if(last_char==EOF) break;
        
        for (; n >= 0; n--)
            printf("%f\n", array[n]);
    }
    return 0; /* Exit the program successfully */
}

/*
 * getfloat: Get the next floating-point number from input and store it in *pn.
 * Arguments:
 *   pn - Pointer to a float where the value will be stored.
 * Returns:
 *   0 if a valid float is read, or EOF if end of input is reached.
 */
int getfloat(float *pn) {
    int c, sign;
    float power;

    /* Skip any whitespace characters */
    while (isspace(c = getch()));

    /* Check for invalid characters */
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c);  /* Not a valid number, push it back */
        return -1;    /* Return 0 to signal invalid input */
    }

    /* Determine the sign of the float */
    sign = (c == '-') ? -1 : 1;

    /* Handle the optional sign (+ or -) */
    if (c == '+' || c == '-')
        c = getch();

    /* Read the integer part of the float */
    for (*pn = 0.0; isdigit(c); c = getch())
        *pn = 10.0 * *pn + (c - '0');

    /* If a decimal point is encountered, process the fractional part */
    if (c == '.') 
        c = getch();

    /* Read the fractional part of the float */
    for (power = 1.0; isdigit(c); c = getch()) {
        *pn = 10.0 * *pn + (c - '0');  /* Add fractional digits */
        power *= 10.0;                  /* Update the power of 10 */
    }

    /* Apply the sign and adjust for the decimal point */
    *pn *= sign / power;

    /* If a non-digit character is encountered after the float, push it back */
    if (c != EOF)
        ungetch(c);

    return c; /* Return the last character read (EOF or non-digit) */
}

/* Buffer and buffer pointer for ungetch functionality */
#define BUFSIZE 100  /* Size of the buffer */

char buf[BUFSIZE];  /* Input buffer */
int bufp = 0;       /* Buffer pointer */

/*
 * getch: Get the next character from input, using a buffer if available.
 * Returns:
 *   The next character from the input or EOF if the end of input is reached.
 */
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/*
 * ungetch: Push a character back into the input buffer.
 * Arguments:
 *   c - The character to be pushed back into the buffer.
 */
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");  /* Error handling if the buffer is full */
    else
        buf[bufp++] = c;  /* Push character back into the buffer */
}


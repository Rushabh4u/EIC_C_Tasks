/*
 * Program: Reverse Polish Notation (RPN) Evaluator
 * Author: 164993_faizan_momin
 * Created Date: 16/12/2024
 * Description: This program evaluates a Reverse Polish Notation (RPN) expression
 *              from the command line, where each operand or operator is a separate argument.
 *              It uses a stack-based approach to evaluate expressions like:
 *              "expr 2 3 4 + *" which evaluates to 2 * (3 + 4).
 */

#include <ctype.h>   /* For character classification functions like isdigit */
#include <stdio.h>   /* For standard input/output functions */
#include <stdlib.h>  /* For atof (string to double) */
#include <string.h>  /* For string manipulation functions */

/* Constants */
#define MAXOP 100  /* maximum size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define BUFSIZE 100  /* buffer size for ungetch */
#define MAXVAL 100  /* maximum depth of value stack */

/* Function Prototypes */
int getop(char []);          /* Get next operator or numeric operand */
void ungets(char []);        /* Push string back onto input buffer */
void push(double);           /* Push a value onto the stack */
double pop(void);            /* Pop a value from the stack */
int getch(void);             /* Get a (possibly pushed back) character */
void ungetch(int);           /* Push character back onto input */

/* Global Variables */
int sp = 0;            /* Next free stack position */
double val[MAXVAL];    /* Value stack */
char buf[BUFSIZE];     /* Buffer for ungetch */
int bufp = 0;          /* Next free position in buffer */

/* Main Function */
int main(int argc, char *argv[]) {
    char s[MAXOP];    /* String to store operand/operator */
    double op2;        /* Operand for arithmetic operations */

    /* Process each command line argument */
    while (--argc > 0) {
        ungets(" ");  /* Push space to indicate end of argument */
        ungets(*++argv);  /* Push argument onto the buffer */

        switch (getop(s)) {
            case NUMBER:
                push(atof(s));  /* Convert string to number and push onto stack */
                break;
            case '+':
                push(pop() + pop());  /* Pop two values, add, and push result */
                break;
            case '*':
                push(pop() * pop());  /* Pop two values, multiply, and push result */
                break;
            case '-':
                op2 = pop(); 
                push(pop() - op2);  /* Pop two values, subtract, and push result */
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);  /* Pop two values, divide, and push result */
                else
                    printf("error: zero divisor\n");  /* Error handling for division by zero */
                break;
            default:
                printf("error: unknown command %s\n", s);  /* Handle unknown commands */
                argc = 1;  /* Exit the loop if an unknown command is found */
                break;
        }
    }

    /* Print the final result */
    printf("%.8g\n", pop());  /* Pop and print the final result from the stack */
    return 0;
}

/* getop: Get the next operator or numeric operand */
int getop(char s[]) {
    int i, c;

    /* Skip spaces and tabs */
    while ((s[0] = c = getch()) == ' ' || c == '\t');

    s[1] = '\0';  /* Null-terminate the string */

    if (!isdigit(c) && c != '.')  /* If it's not a number or dot, return the operator */
        return c;

    i = 0;

    /* If it's a number, collect integer part */
    if (isdigit(c)) 
        while (isdigit(s[++i] = c = getch()));

    /* If it's a decimal point, collect fractional part */
    if (c == '.') 
        while (isdigit(s[++i] = c = getch()));

    s[i] = '\0';  /* Null-terminate the string */

    if (c != EOF)
        ungetch(c);  /* Push the last character back into the buffer if it's not EOF */

    return NUMBER;  /* Return signal for number */
}

/* getch: Get a (possibly pushed back) character */
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: Push character back onto the input */
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");  /* Error handling for buffer overflow */
    else
        buf[bufp++] = c;  /* Store character in buffer */
}

/* ungets: Push a string back onto the input */
void ungets(char s[]) {
    int len = strlen(s);  /* Get the length of the string */

    /* Push the string back into the buffer */
    while (len > 0)
        ungetch(s[--len]);
}

/* push: Push a value onto the stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;  /* Push value if there is space in the stack */
    else
        printf("error: stack full, can't push %g\n", f);  /* Error handling for stack overflow */
}

/* pop: Pop and return the top value from the stack */
double pop(void) {
    if (sp > 0)
        return val[--sp];  /* Pop and return top value if stack is not empty */
    else {
        printf("error: stack empty\n");  /* Error handling for stack underflow */
        return 0.0;  /* Return 0 if stack is empty */
    }
}


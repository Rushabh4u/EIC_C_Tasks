/*
 * Program: Pattern Matching and Reverse Polish Calculator
 * Author: 164993_faizan_momin
 * Created Date: 17/12/2024
 * Description: This program demonstrates pattern matching, stack manipulation, reverse polish
 *              calculator, and string operations. It reads lines of input, searches for a specific 
 *              pattern, converts strings to integers, reverses strings, and performs basic mathematical 
 *              operations on input values. The operations are selected from a menu-driven interface.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100 /* maximum depth of val stack */
#define BUFSIZE 100
#define MAXLINE 1000
#define MAXOP 100

/* Function prototypes */
int getch(void);            /* Get the next character from input */
void ungetch(int);          /* Push a character back into the input buffer */
int getop(char *);          /* Get the next operator or numeric operand */
void push(double);          /* Push a value onto the stack */
double pop(void);           /* Pop and return the top value from the stack */
int mgetline(char *s, int lim);  /* Get a line of input with a limit */
int strindex(char *s, char *t); /* Find the index of pattern in string */
int atoiv2(char *s);        /* Convert string to integer */
void itoav2(int n, char *s); /* Convert integer to string */
void reverse(char *s);      /* Reverse a string */

/* Global variables */
int sp = 0;                  /* Stack pointer */
int bufp = 0;                /* Buffer pointer */
double val[MAXVAL];          /* Stack to store values */
char buf[BUFSIZE];           /* Input buffer */
char pattern[] = "ould";     /* Pattern to search for */

/* Function to show the menu */
void show_menu() {
    printf("\nMenu:\n");
    printf("1. Get line and search for a pattern\n");
    printf("2. Convert string to integer\n");
    printf("3. Convert integer to string and reverse it\n");
    printf("4. Find pattern index in string\n");
    printf("5. Reverse Polish Notation calculator\n");
    printf("6. Exit\n");
    printf("Enter your choice (1-6): ");
}

/* Main function: Process lines, perform calculations, and operations */
int main(void) {
    char line[MAXLINE];
    int choice;

    
    while (1) {
        show_menu();  /* Display menu */
        scanf("%d", &choice);  /* Get user's choice */

        switch (choice) {
            case 1: {
                /* Read input lines and search for the pattern */
                printf("Enter a line: ");
                mgetline(line, MAXLINE);
                if (strindex(line, pattern) >= 0) {
                    printf("Pattern '%s' found in: %s\n", pattern, line);
                } else {
                    printf("Pattern '%s' not found.\n", pattern);
                }
                break;
            }
            case 2: {
                /* Convert string to integer and print */
                char *s = "1234";
                int ret = atoiv2(s);
                printf("String '%s' converted to integer: %d\n", s, ret);
                break;
            }
            case 3: {
                /* Convert integer to string, reverse it, and print */
                char s1[100];
                int i = -12345;
                itoav2(i, s1);
                reverse(s1);
                printf("Integer %d converted to string and reversed: %s\n", i, s1);
                break;
            }
            case 4: {
                /* Find pattern index in string */
                char *s2 = "This is a line";
                char *t = "is";
                int ret = strindex(s2, t);
                if (ret >= 0) {
                    printf("Pattern '%s' found at position %d in: %s\n", t, ret, s2);
                } else {
                    printf("Pattern '%s' not found in: %s\n", t, s2);
                }
                break;
            }
            case 5: {
                /* Reverse Polish calculator */
                int type;
                double op2;
                char s3[MAXOP];
                
                printf("Enter Reverse Polish Notation expression (e.g., 2 3 4 + *):\n");

                while ((type = getop(s3)) != EOF) {
                    switch (type) {
                        case NUMBER:
                            push(atof(s3));
                            break;
                        case '+':
                            push(pop() + pop());
                            break;
                        case '*':
                            push(pop() * pop());
                            break;
                        case '-':
                            op2 = pop();
                            push(pop() - op2);
                            break;
                        case '/':
                            op2 = pop();
                            if (op2 != 0.0)
                                push(pop() / op2);
                            else
                                printf("error: zero divisor\n");
                            break;
                        case '\n':
                            printf("Result: %.8g\n", pop());
                            break;
                        default:
                            printf("error: unknown command %s\n", s3);
                            break;
                    }
                }
                break;
            }
            case 6:
                printf("Exiting program...\n");
                return 0;  /* Exit the program */
            default:
                printf("Invalid choice! Please select a valid option (1-6).\n");
        }
    }

    return 0;
}

/* Convert string to integer (alternative version) */
int atoiv2(char *s) {
    int n, sign;

    /* Skip white space */
    for (; isspace(*s); s++);

    /* Determine sign */
    sign = (*s == '-') ? -1 : 1;

    if (*s == '+' || *s == '-')
        s++;

    /* Convert string to integer */
    for (n = 0; isdigit(*s); s++)
        n = 10 * n + *s - '0';

    return sign * n;
}

/* Reverse Polish calculator functions */

/* Push a value onto the stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* Pop and return the top value from the stack */
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* Get the next operator or numeric operand */
int getop(char *s) {
    int c;

    /* Skip whitespace characters */
    while ((*s = c = getch()) == ' ' || c == '\t');
    *(s + 1) = '\0';

    /* Return non-number characters */
    if (!isdigit(c) && c != '.') 
        return c;

    /* Read integer part of number */
    if (isdigit(c))
        while (isdigit(*++s = c = getch()));

    /* Read fractional part of number if present */
    if (c == '.')
        while (isdigit(*++s = c = getch()));

    *s = '\0';

    /* Push last character back to the buffer if not EOF */
    if (c != EOF)
        ungetch(c);

    return NUMBER;
}

/* Get the next character from input, using buffer if available */
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* Push a character back into the input buffer */
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* Convert integer to string */
void itoav2(int n, char *s) {
    int sign;

    if ((sign = n) < 0)
        n = -n;

    do {
        *s++ = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0)
        *s++ = '-';
    *s = '\0';
}

/* Reverse a string */
void reverse(char *s) {
    int c;
    char *t;

    for (t = s + (strlen(s) - 1); s < t; s++, t--) {
        c = *s;
        *s = *t;
        *t = c;
    }
}

/* Get a line of input */
int mgetline(char *s, int lim) {
    char c;
    char *t = s;
    while (--lim>0 &&(c = getchar()) !='\n'){
        *s++ = c;
      
        }

    if (c == '\n')
        *s++ = c;
    *s = '\0';

    return s - t;
}

/* Find the index of the first occurrence of t in s */
int strindex(char *s, char *t) {
    char *b = s;
    char *p, *r;

    for (; *s != '\0'; s++) {
        for (p = s, r = t; *r != '\0' && *p == *r; p++, r++);

        if (r > t && *r == '\0')
            return s - b;
    }
    return -1;
}


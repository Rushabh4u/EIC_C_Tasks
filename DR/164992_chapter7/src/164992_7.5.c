/*
 * Postfix Calculator using scanf and sscanf for input and number conversion.
 * The program evaluates expressions written in reverse Polish notation.
 * Created By : Rushabh Goswami
 * Created On : 10/12/2024
 */

/* Required Libraries */
#include <stdio.h>
#include <stdlib.h> /* For atof() to convert string to double */

/* Constants and Macros */
#define MAX_OP 100   /* Max size of operand or operator */
#define NUMBER '0'   /* Signal that a number was found */
#define MAX_VAL 100  /* Max size of the value stack */
#define BUF_SIZE 100 /* Buffer size for ungetch */

/* Function Prototypes */
int getOp(char cBuffer[]); /* Get next operator or operand */
void push(double dValue);  /* Push value onto the stack */
double pop(void);          /* Pop value from the stack */

/* Stack */
int iStackPointer = 0;         /* Stack pointer */
double dValueStack[MAX_VAL];   /* Value stack */

/* Buffer for getch and ungetch */
char cBuffer[BUF_SIZE]; /* Buffer array */
int iBufferPointer = 0; /* Buffer pointer */

/* Main function */
int main(void)
{
    int iOperatorType;         /* Operator type */
    double dOperand2;          /* Second operand */
    char cInput[MAX_OP];       /* Input buffer */

    /* Reverse Polish notation evaluation loop */
    while ((iOperatorType = getOp(cInput)) != EOF)
    {
        switch (iOperatorType)
        {
        case NUMBER: /* If a number is found */
            push(atof(cInput)); /* Convert string to double and push */
            break;
        case '+': /* Addition operator */
            push(pop() + pop());
            break;
        case '*': /* Multiplication operator */
            push(pop() * pop());
            break;
        case '-': /* Subtraction operator */
            dOperand2 = pop();
            push(pop() - dOperand2);
            break;
        case '/': /* Division operator */
            dOperand2 = pop();
            if (dOperand2 != 0.0)
                push(pop() / dOperand2);
            else
                printf("error: zero divisor\n");
            break;
        case '\n': /* End of input line */
            printf("\t%.8g\n", pop()); /* Display result */
            break;
        default: /* Unknown command */
            printf("error: unknown command %s\n", cInput);
            break;
        }
    }
    return 0;
}

/* Push value onto the stack */
void push(double dValue)
{
    if (iStackPointer < MAX_VAL)
        dValueStack[iStackPointer++] = dValue;
    else
        printf("error: stack full, cannot push %g\n", dValue);
}

/* Pop value from the stack */
double pop(void)
{
    if (iStackPointer > 0)
        return dValueStack[--iStackPointer];
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* Get next operator or operand */
int getOp(char cBuffer[])
{
    int iIndex, cChar;

    /* Skip whitespace and tabs */
    while ((cBuffer[0] = cChar = getch()) == ' ' || cChar == '\t')
        ;
    cBuffer[1] = '\0';

    /* Not a number */
    if (!isdigit(cChar) && cChar != '.' && cChar != '-')
        return cChar;

    iIndex = 0;
    if (cChar == '-') /* Check for negative numbers */
    {
        if (isdigit(cChar = getch()) || cChar == '.')
            cBuffer[++iIndex] = cChar;
        else
        {
            if (cChar != EOF)
                ungetch(cChar);
            return '-';
        }
    }

    if (isdigit(cChar)) /* Collect integer part */
        while (isdigit(cBuffer[++iIndex] = cChar = getch()))
            ;

    if (cChar == '.') /* Collect fractional part */
        while (isdigit(cBuffer[++iIndex] = cChar = getch()))
            ;

    cBuffer[iIndex] = '\0';
    if (cChar != EOF)
        ungetch(cChar);

    return NUMBER;
}

/* Get a (possibly pushed-back) character */
int getch(void)
{
    char cChar;
    if (iBufferPointer > 0)
        return cBuffer[--iBufferPointer];
    else
    {
        scanf("%c", &cChar);
        return cChar;
    }
}

/* Push character back onto input */
void ungetch(int cChar)
{
    if (iBufferPointer >= BUF_SIZE)
        printf("ungetch: too many characters\n");
    else
        cBuffer[iBufferPointer++] = cChar;
}


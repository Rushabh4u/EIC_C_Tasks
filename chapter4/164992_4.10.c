/**
*  An alternate organization uses getline to read an entire input line; this makes getch and ungetch unnecessary. Revise the calculator to use this approach.
*Author : Rushabh Goswami
*Created : 27/8/24
*/

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define MAXLINE 100

int sp = 0;
double val[MAXVAL];

int getop(char[]);

void push(double);

double pop(void);

int mgetline(char s[], int lim);

int iLi = 0;  /* input line index */
char cLine[MAXLINE];  /* one input line */

/* reverse polish calculator */

int main(void) {
    int type;
    char s[MAXOP];
	double op2,op1;
	printf("Enter operands and a operator (in postfix manner): ");
    while ((type = getop(s)) != EOF) {

        switch (type) {
            case NUMBER:
                push(atof(s));
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
                if (op2 != 0.0){
                    push(pop() / op2);

                }else
                    printf("error:zero divisor\n");
                break;
            case '%':
                op2 = pop();
                op1 = pop();
                if (op2 != 0.0)
                {
                	if((op1 < 0 && op2 > 0) || (op1 > 0 && op2 < 0))
                	{
                		push(fmod(op1, op2) + op2);
                	}
                	else
                    		push(fmod(op1, op2));
             	
                }
                else
                    printf("erro:zero divisor\n");
                break;
            case '\n':
                printf("Ans : %.8g\n", pop());
                printf("Enter operands and a operator (in postfix manner): ");
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}

void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error:stack full, cant push %g\n", f);
}

double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

int getop(char s[]) {
    int c, i;

    if (cLine[iLi] == '\0'){
        if (mgetline(cLine, MAXLINE) == 0)
            return EOF;
        else
            iLi = 0;
    }
	
    while ((s[0] = c = cLine[iLi++]) == ' ' || c == '\t');

    s[1] = '\0';

    if (!isdigit(c) && c != '.')
        return c;

    i = 0;

    if (isdigit(c))
        while (isdigit(s[++i] = c = cLine[iLi++]));
    if (c == '.')
        while (isdigit(s[++i] = c = cLine[iLi++]));

    s[i] = '\0';

    iLi--;

    return NUMBER;
}

int mgetline(char s[], int lim) {
    int i, c;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';

    return i;
}

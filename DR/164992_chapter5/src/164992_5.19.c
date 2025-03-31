/**
 * Modify undcl so that it does not add redundant parenthesis to declarations.
 **/

#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAXTOKEN 100

/* Token types */
enum {NAME, PARENS, BRACKETS};
/* Boolean values */
enum {NO, YES};

/* Function prototypes */
void dcl(void);
void dirdcl(void);
void errmsg(char *);
int gettoken(void);

/* Global variables */
int tokentype;          /* Type of last token */
char token[MAXTOKEN];   /* Last token string */
char name[MAXTOKEN];    /* Identifier name */
char out[1000];         /* Output string */
char datatype[MAXTOKEN];/* Data type */
int prevtoken = NO;     /* Flag for ungetting token */

int main(void) {
    int i;

    printf("Enter a declaration: \n");
    while (gettoken() != EOF) {
        strcpy(datatype, token);
        out[0] = '\0';

        dcl();

        if (tokentype != '\n') {
            printf("Syntax error.\n");
        }

        printf("Parsed declaration:\n");
        printf("%s: %s %s\n", name, out, datatype);

        /* Reset buffers for the next declaration */
        for (i = 0; i < MAXTOKEN; i++) {
            datatype[i] = '\0';
            out[i] = '\0';
            name[i] = '\0';
        }

        printf("\nEnter another declaration or press Ctrl+D to exit:\n");
    }

    return 0;
}

/* gettoken: Retrieves the next token from input */
int gettoken(void) {
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    if (prevtoken == YES) {
        prevtoken = NO;
        return tokentype;
    }

    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; )
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); )
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else {
        return tokentype = c;
    }
}

/* dcl: Parse a declarator */
void dcl(void) {
    int ns;

    for (ns = 0; gettoken() == '*'; ) /* Count '*' */
        ns++;

    dirdcl();

    while (ns-- > 0) {
        strcat(out, " pointer to");
    }
}

/* dirdcl: Parse a direct declarator */
void dirdcl(void) {
    int type;

    if (tokentype == '(') { /* (dcl) */
        dcl();
        if (tokentype != ')') {
            errmsg("Error: Missing ')'.\n");
        }
    } else if (tokentype == NAME) { /* Variable name */
        strcpy(name, token);
    } else {
        errmsg("Error: Expected name or (dcl).\n");
    }

    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS) {
            strcat(out, " function returning");
        } else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}

/* errmsg: Print error message and set prevtoken flag */
void errmsg(char *msg) {
    printf("%s", msg);
    prevtoken = YES;
}

#define BUFSIZE 100

/* Buffer for ungetch */
char buf[BUFSIZE];
int bufp = 0; /* Next free position in buf */

/* getch: Get a (possibly pushed back) character */
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: Push a character back on input */
void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("ungetch: Too many characters.\n");
    } else {
        buf[bufp++] = c;
    }
}


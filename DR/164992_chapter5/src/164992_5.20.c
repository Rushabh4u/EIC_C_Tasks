/**
 * Expand dcl to handle declarations with function argument types, qualifiers like const, and so on.
 **/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 500
#define MAXOUTPUT 5000 // Maximum size for output buffer
#define BUFSIZE MAXTOKEN * 2 // Buffer size for pushed-back characters
#define NUMOFSTORAGECLASSES 5
#define NUMOFTYPEQUALIFIERS 4
#define NUMOFTYPESPECIFIERS 11

/* Enum definitions for token types and return statuses */
enum tokentype { VARIABLE, BRACKETS, STORAGECLASS, TYPEQUALIFIER, TYPESPECIFIER };
enum returnstatus { OK, ERROR };
enum boolean { FALSE, TRUE };

/* Function prototypes */
int processDeclaration(char *declaration, char expectParameter);
int dcl(char *name, char *out, char expectParameter);
int dirdcl(char *name, char *out, char expectParameter);
int parameters(char *out);
int gettoken(void);
int getch(void);
void ungetch(int c);
int contains(char **strs, char *name, int strCount);
char *saferstrcat(char *dst, const char *str, size_t dstsize);
int error(char *msg);

/* Global variables */
int tokentype;
char token[MAXTOKEN];
int buf[BUFSIZE];
int bufp = 0;

/* Storage classes, type qualifiers, and specifiers */
static char *storageClasses[NUMOFSTORAGECLASSES] = { "_Thread_local", "auto", "extern", "register", "static" };
static char *typeQualifiers[NUMOFTYPEQUALIFIERS] = { "_Atomic", "const", "restrict", "volatile" };
static char *typeSpecifiers[NUMOFTYPESPECIFIERS] = { "_Bool", "_Complex", "char", "double", "float", "int", "long", "short", "signed", "unsigned", "void" };

/* Main function */
int main(void)
{
    char out[MAXOUTPUT];
    printf("Enter declarations (Ctrl+D to end):\n");

    while (gettoken() != EOF)
    {
        if (processDeclaration(out, FALSE) == ERROR)
        {
            printf("Error processing declaration.\n");
        }
        for (int c = tokentype; c != '\n' && c != EOF; ) // Discard rest of line
        {
            if ((c = getch()) == EOF)
                break;
        }
    }
    return 0;
}

/* Process a single declaration */
int processDeclaration(char *declaration, char expectParameter)
{
    char datatype[MAXTOKEN] = ""; // Store type information
    char name[MAXTOKEN] = "";    // Store variable or function name
    char out[MAXOUTPUT] = "";    // Temporary output buffer

    if (!(tokentype == STORAGECLASS || tokentype == TYPEQUALIFIER || tokentype == TYPESPECIFIER))
        return error("Expected a type.");

    while (tokentype == STORAGECLASS || tokentype == TYPEQUALIFIER || tokentype == TYPESPECIFIER)
    {
        if (saferstrcat(datatype, " ", MAXTOKEN) == NULL || saferstrcat(datatype, token, MAXTOKEN) == NULL)
            return error("Buffer overflow in datatype.");
        gettoken();
    }

    for (int i = strlen(token) - 1; i >= 0; i--)
        ungetch(token[i]);

    do
    {
        out[0] = '\0'; // Reset output buffer
        if (dcl(name, out, expectParameter) == ERROR)
            return ERROR;

        if (tokentype != ';' && tokentype != ',' && tokentype != ')' && tokentype != '\n')
            return error("Syntax error.");

        if (!expectParameter)
        {
            printf("Declaration: %s: %s %s\n", name, out, datatype);
        }
    } while (!expectParameter && tokentype == ',');

    return OK;
}

/* Parse a declaration */
int dcl(char *name, char *out, char expectParameter)
{
    int numPointers = 0;
    while (gettoken() == '*')
        numPointers++;

    if (dirdcl(name, out, expectParameter) == ERROR)
        return ERROR;

    while (numPointers-- > 0)
        if (saferstrcat(out, " pointer to", MAXOUTPUT) == NULL)
            return error("Buffer overflow in dcl.");

    return OK;
}

/* Parse a direct declaration */
int dirdcl(char *name, char *out, char expectParameter)
{
    if (tokentype == '(')
    {
        if (dcl(name, out, expectParameter) == ERROR)
            return ERROR;
        if (tokentype != ')')
            return error("Missing closing parenthesis.");
    }
    else if (tokentype == VARIABLE)
    {
        snprintf(name, MAXTOKEN, "%s", token);
    }
    else
    {
        return error("Expected variable name or (dcl).\n");
    }

    while (gettoken() == '(' || tokentype == BRACKETS)
    {
        if (tokentype == '(')
        {
            if (parameters(out) == ERROR)
                return ERROR;
        }
        else
        {
            if (saferstrcat(out, " array", MAXOUTPUT) == NULL || saferstrcat(out, token, MAXOUTPUT) == NULL || saferstrcat(out, " of", MAXOUTPUT) == NULL)
                return error("Buffer overflow in brackets.");
        }
    }

    return OK;
}

/* Parse function parameters */
int parameters(char *out)
{
    char declaration[MAXOUTPUT];
    int parameterCount = 0;

    if (gettoken() == ')')
    {
        if (saferstrcat(out, " function with no parameters returning", MAXOUTPUT) == NULL)
            return error("Buffer overflow in parameters.");
        return OK;
    }

    if (saferstrcat(out, " function with parameters:", MAXOUTPUT) == NULL)
        return error("Buffer overflow in parameters.");

    do
    {
        if (parameterCount++ > 0)
            gettoken();

        if (processDeclaration(declaration, TRUE) == ERROR)
            return ERROR;

        if (saferstrcat(out, " ", MAXOUTPUT) == NULL || saferstrcat(out, declaration, MAXOUTPUT) == NULL)
            return error("Buffer overflow in parameters.");
    } while (tokentype == ',');

    if (tokentype != ')')
        return error("Missing closing parenthesis for parameters.");

    if (saferstrcat(out, " returning", MAXOUTPUT) == NULL)
        return error("Buffer overflow in parameters.");

    return OK;
}

/* Get the next token */
int gettoken(void)
{
    int c;
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (c == '(' || c == '[' || c == ']')
    {
        *p++ = c;
        if (c == '[')
            while ((*p++ = getch()) != ']')
                ;
        *p = '\0';
        return tokentype = (c == '(') ? '(' : BRACKETS;
    }
    else if (isalpha(c) || c == '_')
    {
        *p++ = c;
        while (isalnum(c = getch()) || c == '_')
            *p++ = c;
        *p = '\0';
        ungetch(c);
        if (contains(typeSpecifiers, token, NUMOFTYPESPECIFIERS))
            return tokentype = TYPESPECIFIER;
        if (contains(storageClasses, token, NUMOFSTORAGECLASSES))
            return tokentype = STORAGECLASS;
        if (contains(typeQualifiers, token, NUMOFTYPEQUALIFIERS))
            return tokentype = TYPEQUALIFIER;
        return tokentype = VARIABLE;
    }

    *p++ = c;
    *p = '\0';
    return tokentype = c;
}

/* Get a character from input */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* Push character back to input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        fprintf(stderr, "ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* Check if a string is in a list */
int contains(char **strs, char *name, int strCount)
{
    for (int i = 0; i < strCount; i++)
        if (strcmp(strs[i], name) == 0)
            return TRUE;
    return FALSE;
}

/* Safely concatenate strings */
char *saferstrcat(char *dst, const char *str, size_t dstsize)
{
    size_t dstLen = strlen(dst), strLen = strlen(str);
    if (dstLen + strLen >= dstsize)
        return NULL;
    strcpy(dst + dstLen, str);
    return dst;
}

/* Print error message */
int error(char *msg)
{
    fprintf(stderr, "%s\n", msg);
    return ERROR;
}


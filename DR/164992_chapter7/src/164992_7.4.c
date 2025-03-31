/*
 * This program demonstrates a minimalistic scanf function, `minscanf`,
 * to take multiple types of input and display their respective representations.
 * Created By : Rushabh Goswami
 * Created On : 10/12/2024
 */

/* Required Libraries */
#include <stdarg.h> /* Library for variable argument handling */
#include <stdio.h>  /* Standard Input/Output library */
#include <stdlib.h> /* Standard library for memory allocation */

/* Function declarations */
void minscanf(char *cFormat, ...); /* Minimalistic scanf function */

/* Main function */
int main(void)
{
    int iNum;                     /* Integer input */
    float fDnum;                  /* Float input */
    double dDoub;                 /* Double input */
    unsigned int uUnint;          /* Unsigned integer input */
    char cCharacter;              /* Character input */
    char sStr[100];               /* String input */

    /* Prompt and take inputs */
    printf("Enter integer number: ");
    minscanf("%d", &iNum);

    printf("Enter float number: ");
    minscanf("%f", &fDnum);

    printf("Enter double number: ");
    minscanf("%lf", &dDoub);

    printf("Enter unsigned integer number: ");
    minscanf("%u", &uUnint);

    printf("Enter character: ");
    minscanf(" %c", &cCharacter); /* Space before %c to handle newline */

    printf("Enter string: ");
    minscanf("%s", sStr);

    /* Display the entered values */
    printf("\nYou have entered:\n");
    printf("Integer iNum: %d\n", iNum);
    printf("Float fDnum: %f\n", fDnum);
    printf("Double dDoub: %lf\n", dDoub);
    printf("Unsigned integer uUnint: %u\n", uUnint);
    printf("Character cCharacter: %c\n", cCharacter);
    printf("String sStr: %s\n", sStr);

    /* Display additional representations */
    printf("Octal representation of iNum: %o\n", iNum);
    printf("Hexadecimal representation of iNum: %x\n", iNum);
    printf("Pointer pPointer: %p\n", (void *)&iNum);

    return 0;
}

/* Minimalistic scanf function to handle basic formatted input */
void minscanf(char *cFormat, ...)
{
    va_list vArgs;          /* Points to each unnamed argument in turn */
    char *pFormatChar;      /* Pointer to traverse the format string */
    int *pIntInput;         /* Pointer for integer input */
    float *pFloatInput;     /* Pointer for float input */
    double *pDoubleInput;   /* Pointer for double input */
    unsigned int *pUintInput; /* Pointer for unsigned integer input */
    char *pCharInput;       /* Pointer for character input */
    char *pStringInput;     /* Pointer for string input */

    va_start(vArgs, cFormat); /* Initialize argument pointer */

    /* Traverse the format string */
    for (pFormatChar = cFormat; *pFormatChar; pFormatChar++)
    {
        if (*pFormatChar != '%') /* Skip non-format characters */
        {
            continue;
        }

        /* Handle format specifiers */
        switch (*++pFormatChar)
        {
            case 'd': /* Integer input */
                pIntInput = va_arg(vArgs, int *);
                scanf("%d", pIntInput);
                break;
            case 'f': /* Float input */
                pFloatInput = va_arg(vArgs, float *);
                scanf("%f", pFloatInput);
                break;
            case 'l': /* Double input (long float) */
                if (*++pFormatChar == 'f')
                {
                    pDoubleInput = va_arg(vArgs, double *);
                    scanf("%lf", pDoubleInput);
                }
                break;
            case 'u': /* Unsigned integer input */
                pUintInput = va_arg(vArgs, unsigned int *);
                scanf("%u", pUintInput);
                break;
            case 'c': /* Character input */
                pCharInput = va_arg(vArgs, char *);
                scanf(" %c", pCharInput); /* Space handles preceding newline */
                break;
            case 's': /* String input */
                pStringInput = va_arg(vArgs, char *);
                scanf("%s", pStringInput);
                break;
            default: /* Any unrecognized specifier */
                putchar(*pFormatChar);
                break;
        }
    }

    va_end(vArgs); /* Clean up when done */
}


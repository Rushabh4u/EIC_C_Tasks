/*
 * This program implements a minimalistic printf function, `minprintf`, 
 * to demonstrate formatted output using variable argument lists.
 * Created By : Rushabh Goswami
 * Created On : 10/12/2024
 */

/* Required Libraries */
#include <stdarg.h> /* Library for variable argument handling */
#include <stdio.h>  /* Standard Input/Output library */

/* Function declarations */
void minprintf(char *cFormat, ...); /* Minimalistic printf function */

/* Main function */
int main(void)
{
    int iInt;             /* Integer variable */
    float fFloat;         /* Float variable */
    double dDouble;       /* Double variable */
    unsigned int uInt;    /* Unsigned integer variable */
    char cChar;           /* Character variable */
    char cString[100];    /* String variable */

    /* Prompt and read inputs */
    printf("Enter integer number: ");
    scanf("%d", &iInt);

    printf("Enter float number: ");
    scanf("%f", &fFloat);

    printf("Enter double number: ");
    scanf("%lf", &dDouble);

    printf("Enter unsigned integer number: ");
    scanf("%u", &uInt);

    printf("Enter character: ");
    scanf(" %c", &cChar);

    printf("Enter string: ");
    scanf(" %[^\n]s", cString);

    /* Print the output using minprintf */
    minprintf("You entered:\n");
    minprintf("Integer: %d\n", iInt);
    minprintf("Float: %f\n", fFloat);
    minprintf("Double: %f\n", dDouble);
    minprintf("Unsigned Integer: %u\n", uInt);
    minprintf("Character: %c\n", cChar);
    minprintf("String: %s\n", cString);

    return 0;
}

/* Minimalistic printf function to handle basic formatted output */
void minprintf(char *cFormat, ...)
{
    va_list vArgs;      /* Points to each unnamed argument in turn */
    char *pFormatChar;  /* Pointer to traverse the format string */
    char *cStringValue; /* Pointer to string argument */
    int iIntValue;      /* Integer argument */
    unsigned int uIntValue; /* Unsigned integer argument */
    char cCharValue;    /* Character argument */
    double dDoubleValue; /* Double argument */

    va_start(vArgs, cFormat); /* Initialize argument pointer */

    /* Traverse the format string */
    for (pFormatChar = cFormat; *pFormatChar; pFormatChar++)
    {
        if (*pFormatChar != '%')
        {
            putchar(*pFormatChar); /* Print regular characters */
            continue;
        }

        /* Handle format specifiers */
        switch (*++pFormatChar)
        {
            case 'd': /* Integer in decimal format */
                iIntValue = va_arg(vArgs, int);
                printf("%d", iIntValue);
                break;
            case 'f': /* Floating-point number */
                dDoubleValue = va_arg(vArgs, double);
                printf("%f", dDoubleValue);
                break;
            case 'u': /* Unsigned integer */
                uIntValue = va_arg(vArgs, unsigned int);
                printf("%u", uIntValue);
                break;
            case 'c': /* Character */
                cCharValue = (char)va_arg(vArgs, int);
                putchar(cCharValue);
                break;
            case 's': /* String */
                for (cStringValue = va_arg(vArgs, char *); *cStringValue; cStringValue++)
                    putchar(*cStringValue);
                break;
            default: /* Any unrecognized specifier */
                putchar(*pFormatChar);
                break;
        }
    }
    va_end(vArgs); /* Clean up when done */
}


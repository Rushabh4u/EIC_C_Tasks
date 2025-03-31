/*
 * Program: String Suffix Comparison
 * Author: 164993_faizan_momin
 * Created Date: 16/12/2024
 * Description: This program compares the suffix of two strings. It checks whether string `t` is a suffix of string `s`.
 *              It uses the functions `strend` to determine if string `t` is at the end of string `s`.
 */

/* Required header files */
#include <stdio.h>  /* For input/output functions */

/* Constant definitions */
#define MAXLINE 1000  /* Maximum length of input string */

/* Function prototypes */
int mgetline(char s[], int lim);    /* Read a line of input */
int strend(char *s, char *t);       /* Check if t is a suffix of s */
int mystrlen(char *t);              /* Calculate the length of a string */

/* Main function */
int main(void) {
    char s[MAXLINE], t[MAXLINE];  /* Arrays to hold the input strings */
    int ret;                       /* Variable to store result of strend */

    /* Read two strings */
    mgetline(s, MAXLINE);
    mgetline(t, MAXLINE);

    /* Check if t is a suffix of s */
    ret = strend(s, t);

    /* Output the result */
    printf("%d", ret);

    return 0;  /* Exit the program successfully */
}

/*
 * mgetline: Read a line from input and store it in `s[]`.
 * Arguments:
 *   s - Array to store the input string
 *   lim - Maximum number of characters to read
 * Returns:
 *   The number of characters read
 */
int mgetline(char s[], int lim) {
    int c, i;

    /* Read characters until the limit or end of input is reached */
    for (i = 0; i < lim - 1 && ((c = getchar()) != EOF) && c != '\n'; ++i)
        s[i] = c;

    /* If a newline character is encountered, store it */
    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    /* Null-terminate the string */
    s[i] = '\0';

    return i;  /* Return the number of characters read */
}

/*
 * strend: Check if string `t` is a suffix of string `s`.
 * Arguments:
 *   s - The string to check against
 *   t - The string to check as a suffix
 * Returns:
 *   1 if `t` is a suffix of `s`, 0 otherwise
 */
int strend(char *s, char *t) {
    int len = mystrlen(t);  /* Get the length of string t */
    char *s_end = s;

    /* Move pointer `s_end` to the end of string s */
    while (*s_end != '\0')
        ++s_end;

    /* Move pointer `t` to the end of string t */
    while (*t != '\0')
        ++t;

    /* Compare characters from the end of both strings */
    while (len > 0) {
        if (*--s_end != *--t)  /* Check corresponding characters from the end */
            return 0;  /* Not a match */
        --len;  /* Decrease length of string t */
    }

    return 1;  /* If all characters match, t is a suffix of s */
}

/*
 * mystrlen: Calculate the length of the string `t`.
 * Arguments:
 *   t - The string whose length is to be calculated
 * Returns:
 *   The length of string `t`
 */
int mystrlen(char *t) {
    char *p = t;

    /* Move pointer p until we reach the null terminator */
    while (*p != '\0')
        ++p;

    return p - t;  /* Return the difference between the pointers (length) */
}


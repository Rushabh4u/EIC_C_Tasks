/**
 * Program: Custom String Functions: mystrncpy, mystrncat, mystrncmp
 * Author: 164993_faizan_momin
 * Created Date: [Insert Date Here]
 * Description: This program implements custom versions of the string manipulation functions:
 *              mystrncpy (copy n characters), mystrncat (concatenate n characters), and
 *              mystrncmp (compare first n characters). These functions are used to manipulate 
 *              strings with a limit on the number of characters (n) processed.
 */

/* Required header files */
#include <stdio.h>    /* For input/output functions */
#include <stdlib.h>   /* For memory allocation */
#include <string.h>   /* For standard string functions */

/* Define maximum size for arrays */
#define MAXSIZE 1000

/*
 * mystrncpy: Copy at most `n` characters from `source` to `dest`.
 * Arguments:
 *   dest - The destination string where the characters are copied.
 *   source - The source string from which characters are copied.
 *   n - The maximum number of characters to copy.
 * Returns: None
 */
void mystrncpy(char *dest, char *source, int n) {
    /* Copy n characters from source to dest */
    while (*source && n-- > 0)
        *dest++ = *source++;

    /* If source is shorter than n, fill remaining space in dest with null characters */
    while (n-- > 0)
        *dest++ = '\0';

    /* Ensure null-termination */
    *dest = '\0';
}

/*
 * mystrncat: Concatenate at most `n` characters from `str2` to the end of `str1` and store in `dest`.
 * Arguments:
 *   str1 - The first string (destination).
 *   str2 - The second string (source).
 *   dest - The destination string where the result is stored.
 *   n - The maximum number of characters to append from str2 to str1.
 * Returns: None
 */
void mystrncat(char *str1, char *str2, char *dest, int n) {
    /* Copy str1 to dest */
    while (*str1) {
        *dest++ = *str1++;
    }

    /* Append at most n characters from str2 to dest */
    while (n-- > 0 && *str2) {
        *dest++ = *str2++;
    }

    /* Null-terminate the resulting string */
    *dest = '\0';
}

/*
 * mystrncmp: Compare the first `n` characters of strings `lhs` and `rhs`.
 * Arguments:
 *   lhs - The left-hand string to compare.
 *   rhs - The right-hand string to compare.
 *   n - The maximum number of characters to compare.
 * Returns:
 *   - A negative value if lhs < rhs,
 *   - 0 if lhs == rhs,
 *   - A positive value if lhs > rhs.
 */
int mystrncmp(char *lhs, char *rhs, int n) {
    /* Compare characters up to n characters or until a mismatch is found */
    for (; *lhs == *rhs; lhs++, rhs++) {
        if (*lhs == '\0' || --n <= 0)
            return 0;  /* Strings are equal up to n characters */
    }
    return *lhs - *rhs;  /* Return difference if strings are not equal */
}

/*
 * mystrnlen: Calculate the length of string `s`.
 * Arguments:
 *   s - The string whose length is to be calculated.
 * Returns:
 *   The length of string `s` (number of characters before null-termination).
 */
int mystrnlen(char *s) {
    char *p = s;  /* Pointer to the beginning of string s */
    
    /* Traverse the string to count characters */
    while (*s != '\0') {
        s++;  /* Move to next character */
    }

    return s - p;  /* Return the difference in pointers to get the length */
}

/* Main function */
int main(void) {
    char dest[MAXSIZE] ; /* Initial string to demonstrate mystrncpy */
    char source[MAXSIZE];         /* Source string to copy from */

    /* Call mystrncpy to copy 4 characters from source to dest */
    mystrncpy(dest, source, 4);
    printf("Result of mystrncpy: %s\n", dest);  /* Expected: "GHIJEF" */

    /* Allocate memory for the result of mystrncat */
    char s1[] = "ABCD";
    char t1[] = "EFGHIJ";
    char *d;

    /* Allocate enough memory to hold the concatenated result */
    if ((d = (char *) malloc(sizeof(char) * (strlen(s1) + 4 + 1))) == NULL) {
        printf("Unable to allocate memory\n");
        return -1;
    }

    /* Call mystrncat to concatenate 4 characters from t1 to s1 */
    mystrncat(s1, t1, d, 4);
    printf("Result of mystrncat: %s\n", d);  /* Expected: "ABCDEFGH" */

    free(d);  /* Free allocated memory */

    /* Test mystrncmp to compare the first 3 characters of two strings */
    char s2[] = "ABCDEF";
    char t2[] = "ABC";
    int result;

    result = mystrncmp(s2, t2, 3);
    printf("Result of mystrncmp: %d\n", result);  /* Expected: 0 (equal) */

    return 0;  /* Exit the program successfully */
}


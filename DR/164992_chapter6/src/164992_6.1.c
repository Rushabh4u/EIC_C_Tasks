/*
 * Program to  properly handle underscores, string constants, comments, or preprocessor control lines.
 * 
 * Author: Rushabh Goswami - 164992
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

/* Structure to hold keywords and their counts */
struct key {
    char *word; /* Keyword string */
    int count;  /* Count of occurrences */
} keytab[] = {
    "auto", 0, "break", 0, "case", 0, "char", 0,
    "const", 0, "continue", 0, "default", 0, "do", 0,
    "double", 0, "else", 0, "enum", 0, "extern", 0,
    "float", 0, "for", 0, "goto", 0, "if", 0,
    "int", 0, "long", 0, "register", 0, "return", 0,
    "short", 0, "signed", 0, "sizeof", 0, "static", 0,
    "struct", 0, "switch", 0, "typedef", 0, "union", 0,
    "unsigned", 0, "void", 0, "volatile", 0, "while", 0
};

/* Function declarations */
int mygetword(char *, int);
int binsearch(char *, struct key *, int);
#define NKEYS (sizeof(keytab) / sizeof(keytab[0])) /* Total keywords in keytab */
#define MAXWORD 10000 /* Maximum word size */

/* Main Function: Counts occurrences of C keywords in input */
int main(int argc, char *argv[]) {
    int n;                 /* Index variable */
    char word[MAXWORD];    /* Buffer to store words */

    printf("Keyword Counter Program\n");
    printf("Please enter the input text (Ctrl+D to terminate input on Unix-like systems):\n\n");

    /* Process each word in the input */
    while (mygetword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            /* Perform binary search for the word in keytab */
            if ((n = binsearch(word, keytab, NKEYS)) >= 0) {
                keytab[n].count++; /* Increment the keyword count */
            }
        }
    }

    /* Print the results */
    printf("\nKeyword Counts:\n");
    printf("--------------------\n");
    for (n = 0; n < NKEYS; n++) {
        if (keytab[n].count > 0) {
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
        }
    }
    printf("--------------------\n");
    printf("Processing Complete.\n");

    return 0;
}

/* Binary Search Function: Search for a word in the keytab */
int binsearch(char *word, struct key lkeytab[], int n) {
    int cond; /* Result of string comparison */
    int low, high, mid;

    low = 0;
    high = n - 1;

    /* Perform binary search */
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, lkeytab[mid].word)) < 0) {
            high = mid - 1; /* Search in the left half */
        } else if (cond > 0) {
            low = mid + 1; /* Search in the right half */
        } else {
            return mid; /* Match found */
        }
    }
    return -1; /* Word not found */
}

/* mygetword: Get the next word or character from input */
int mygetword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word; /* Pointer to the current word buffer */
    int t;

    /* Skip whitespace characters */
    while (isspace(c = getch()));

    if (c != EOF) {
        *w++ = c; /* Store the first character */
    }

    /* Handle non-alphabetic characters */
    if (!isalpha(c)) {
        if (c == '\"') {
            /* Skip string constants */
            for (c = getch(); c != '\"'; c = getch());
        } else if (c == '#') {
            /* Skip preprocessor directives */
            for (c = getch(); c != '\n'; c = getch());
        } else if (c == '/') {
            /* Handle comments */
            if ((c = getch()) == '/') {
                /* Skip single-line comments */
                for (c = getch(); c != '\n'; c = getch());
            } else if (c == '*') {
                /* Skip multi-line comments */
                for (c = getch(), t = getch(); c != '*' || t != '/'; c = getch(), t = getch()) {
                    ungetch(t); /* Return the second character if needed */
                }
            } else {
                ungetch(c); /* Return character if not a comment */
            }
        } else {
            for (; !isspace(c) && c != EOF; c = getch());
        }
        *w = '\0'; /* Null-terminate the word */
        return c;
    }

    /* Read alphabetic characters */
    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    }
    *w = '\0'; /* Null-terminate the word */
    return word[0];
}

#define BUFSIZE 100 /* Buffer size for getch and ungetch */
char buf[BUFSIZE];  /* Buffer for ungetch */
int bufp = 0;       /* Next free position in buf */

/* getch: Get a character from input or buffer */
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: Push character back to the input buffer */
void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}


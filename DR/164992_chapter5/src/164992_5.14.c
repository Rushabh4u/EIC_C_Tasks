/*
 * This is the enhanced sort program with support for numeric and reverse sorting.
 * Usage: sort -n -r
 * -n: Numeric sorting
 * -r: Reverse (decreasing) order
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMERIC   1    /* Numeric sort */
#define DECR      2    /* Sort in decreasing order */
#define LINES    100   /* Maximum number of lines to sort */

/* Function declarations */
int numcmp(char *, char *);
int readlines(char *lineptr[], int maxlines);
void myqsort(void *v[], int left, int right, int (*comp)(void *, void *));
void writelines(char *lineptr[], int nlines, int decr);

/* Global variable to track options */
static char option = 0;

/*
 * Main function: Processes arguments, reads lines, and sorts them based on options.
 */
int main(int argc, char *argv[]) {
    char *lineptr[LINES];
    int nlines; /* Number of input lines read */
    int c, rc = 0; /* Return code */

    printf("\nSort Program\n");
    printf("-----------------------------------\n");
    printf("This program sorts lines in alphabetical or numeric order.\n");
    printf("Options:\n  -n: Numeric sort\n  -r: Reverse order\n\n");

    /* Parse command-line options */
    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0])) {
            switch (c) {
                case 'n':
                    option |= NUMERIC;
                    break;
                case 'r':
                    option |= DECR;
                    break;
                default:
                    printf("Error: Illegal option '%c'\n", c);
                    argc = 1;
                    rc = -1;
                    break;
            }
        }
    }

    if (argc) {
        printf("Usage: sort -n -r\n");
    } else if ((nlines = readlines(lineptr, LINES)) > 0) {
        /* Perform the sort */
        if (option & NUMERIC) {
            myqsort((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))numcmp);
        } else {
            myqsort((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))strcmp);
        }

        /* Write the sorted lines */
        writelines(lineptr, nlines, option & DECR);
    } else {
        printf("Error: Input too large to sort.\n");
        rc = -1;
    }

    return rc;
}

/*
 * writelines: Writes sorted lines to standard output.
 * @lineptr: Array of pointers to lines.
 * @nlines: Number of lines to write.
 * @decr: Flag for reverse order.
 */
void writelines(char *lineptr[], int nlines, int decr) {
    int i;
    if (decr) {
        printf("\nSorted lines in reverse order:\n-----------------------------------\n");
        for (i = nlines - 1; i >= 0; i--) {
            printf("%s\n", lineptr[i]);
        }
    } else {
        printf("\nSorted lines:\n-----------------------------------\n");
        for (i = 0; i < nlines; i++) {
            printf("%s\n", lineptr[i]);
        }
    }
}

/*
 * numcmp: Compares two strings numerically.
 * @s1: First string.
 * @s2: Second string.
 * @return: Negative if s1 < s2, positive if s1 > s2, zero if equal.
 */
int numcmp(char *s1, char *s2) {
    double v1 = atof(s1);
    double v2 = atof(s2);

    if (v1 < v2) {
        return -1;
    } else if (v1 > v2) {
        return 1;
    } else {
        return 0;
    }
}

#define MAXLEN 1000 /* Maximum length of any input line */

/* Function to get a line from input */
int mgetline(char *, int);
char *alloc(int);

/*
 * readlines: Reads input lines and stores them in an array.
 * @lineptr: Array to store pointers to lines.
 * @maxlines: Maximum number of lines to read.
 * @return: Number of lines read.
 */
int readlines(char *lineptr[], int maxlines) {
    int len, nlines = 0;
    char *p, line[MAXLEN];

    while ((len = mgetline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
        } else {
            line[len - 1] = '\0'; /* Remove newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

#define ALLOCSIZE 1000 /* Size of available storage */
static char allocbuf[ALLOCSIZE]; /* Storage for alloc */
static char *allocp = allocbuf;  /* Next free position */

/*
 * alloc: Allocates memory from a static buffer.
 * @n: Number of characters to allocate.
 * @return: Pointer to allocated memory, or NULL if not enough space.
 */
char *alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else {
        return NULL;
    }
}

/*
 * mgetline: Reads a line into a buffer.
 * @s: Buffer to store the line.
 * @lim: Maximum buffer size.
 * @return: Length of the line read.
 */
int mgetline(char s[], int lim) {
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

/*
 * myqsort: Sorts an array using quicksort.
 * @v: Array to sort.
 * @left: Left index.
 * @right: Right index.
 * @comp: Comparison function.
 */
void myqsort(void *v[], int left, int right, int (*comp)(void *, void *)) {
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right) {
        return;
    }

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++) {
        if ((*comp)(v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }

    swap(v, left, last);
    myqsort(v, left, last - 1, comp);
    myqsort(v, last + 1, right, comp);
}

/*
 * swap: Swaps two elements in an array.
 * @v: Array.
 * @i: First index.
 * @j: Second index.
 */
void swap(void *v[], int i, int j) {
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}


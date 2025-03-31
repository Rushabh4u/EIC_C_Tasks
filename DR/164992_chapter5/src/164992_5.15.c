/*
 * Enhanced Sort Program with Case Folding Support
 * This program sorts lines based on user-defined options:
 * - Numeric sort (-n)
 * - Reverse order (-r)
 * - Fold case (ignore case distinctions, -f)
 * Usage: sort -fnr
 * 
 */

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define NUMERIC 1    /* Numeric sort */
#define DECR    2    /* Sort in decreasing order */
#define FOLD    4    /* Fold upper and lower cases */
#define LINES   100  /* Maximum number of lines to be sorted */

/* Function declarations */
int charcmp(char *, char *);
int numcmp(char *, char *);
int readlines(char *lineptr[], int maxlines);
void myqsort(char *v[], int left, int right, int (*comp)(void *, void *));
void writelines(char *lineptr[], int nlines, int order);

static char option = 0; /* Global variable to track options */

/* Main function: Parses options, reads lines, sorts, and displays results */
int main(int argc, char *argv[]) {
    char *lineptr[LINES];    /* Array of pointers to input lines */
    int nlines;              /* Number of input lines read */
    int c, rc = 0;           /* Option character and return code */

    printf("\nEnhanced Sort Program\n");
    printf("---------------------------\n");
    printf("Options:\n  -f: Ignore case\n  -n: Numeric sort\n  -r: Reverse order\n\n");

    /* Parse command-line options */
    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0])) {
            switch (c) {
                case 'f':
                    option |= FOLD;
                    break;
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
        printf("Usage: sort -fnr\n");
    } else {
        if ((nlines = readlines(lineptr, LINES)) > 0) {
            /* Sort the lines based on selected options */
            if (option & NUMERIC) {
                myqsort((char **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) numcmp);
            } else if (option & FOLD) {
                myqsort((char **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) charcmp);
            } else {
                myqsort((char **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) strcmp);
            }

            writelines(lineptr, nlines, option & DECR);
        } else {
            printf("Error: Input too large to sort.\n");
            rc = -1;
        }
    }
    return rc;
}

/*
 * charcmp: Compare two strings ignoring case differences
 * Returns:
 *   Negative value if s < t
 *   Zero if s == t
 *   Positive value if s > t
 */
int charcmp(char *s, char *t) {
    for (; tolower(*s) == tolower(*t); s++, t++) {
        if (*s == '\0') {
            return 0;
        }
    }
    return tolower(*s) - tolower(*t);
}

/*
 * numcmp: Compare two strings numerically
 * Returns:
 *   Negative value if s1 < s2
 *   Zero if s1 == s2
 *   Positive value if s1 > s2
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

int mgetline(char *, int);
char *alloc(int);

/*
 * readlines: Read input lines into an array
 * Returns:
 *   Number of lines read, or -1 if input is too large
 */
int readlines(char *lineptr[], int maxlines) {
    int len, nlines = 0;
    char *p, line[MAXLEN];

    while ((len = mgetline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
        } else {
            line[len - 1] = '\0'; /* Remove newline character */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

/*
 * myqsort: Sort an array using quicksort
 * Parameters:
 *   v: Array to sort
 *   left: Starting index
 *   right: Ending index
 *   comp: Comparison function
 */
void myqsort(char *v[], int left, int right, int (*comp)(void *, void *)) {
    int i, last;
    void swap(char *v[], int i, int j);

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
 * swap: Swap two elements in an array
 */
void swap(char *v[], int i, int j) {
    char *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/*
 * writelines: Print sorted lines to the console
 * Parameters:
 *   lineptr: Array of pointers to lines
 *   nlines: Number of lines
 *   decr: Flag for reverse order
 */
void writelines(char *lineptr[], int nlines, int decr) {
    printf("\nSorted lines:\n---------------------------\n");
    if (decr) {
        for (int i = nlines - 1; i >= 0; i--) {
            printf("%s\n", lineptr[i]);
        }
    } else {
        for (int i = 0; i < nlines; i++) {
            printf("%s\n", lineptr[i]);
        }
    }
}

#define ALLOCSIZE 1000 /* Size of available space */
static char allocbuf[ALLOCSIZE]; /* Storage for alloc */
static char *allocp = allocbuf;  /* Next free position */

/*
 * alloc: Allocate memory from static buffer
 * Returns:
 *   Pointer to allocated memory, or NULL if insufficient space
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
 * mgetline: Read a line from input
 * Returns:
 *   Length of the line read
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


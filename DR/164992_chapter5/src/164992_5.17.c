/**
 * Add a field handling capability, so sorting may be done on the fields within lines,
 * each field sorted according to an independent set of options.
 * The index for the KnR Book was sorted with -df for the index category and -n for page number
 **/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUMERIC 1    /* Numeric sort */
#define DECR 2       /* Sort in decreasing order */
#define FOLD 4       /* Fold upper and lower case */
#define MDIR 8       /* Directory order */
#define LINES 100    /* Maximum number of lines to be sorted */
#define MAXLEN 1000  /* Max length of any input line */
#define ALLOCSIZE 10000 /* Size of available space */

static char allocbuf[ALLOCSIZE];    /* Storage for alloc */
static char *allocp = allocbuf;     /* Next free position */

int option = 0; /* Global variable to hold sorting options */
int pos1 = 0;   /* Field beginning with pos1 */
int pos2 = 0;   /* Field ending just before pos2 */

/* Function prototypes */
void readargs(int argc, char *argv[]);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines, int order);
void myqsort(void *v[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *s1, char *s2);
int charcmp(char *s1, char *s2);
void substr(char *s, char *t, int maxstr);
char *alloc(int n);
void afree(char *p);
void error(char *msg);
int mgetline(char s[], int lim);

/* Main function */
int main(int argc, char *argv[]) {
    char *lineptr[LINES];    /* Array of pointers to text lines */
    int nlines;              /* Number of input lines read */

    /* Read arguments to configure sorting options */
    readargs(argc, argv);

    printf("Sorting lines based on given options...\n");

    if ((nlines = readlines(lineptr, LINES)) > 0) {
        /* Perform sorting */
        if (option & NUMERIC) {
            printf("Sorting numerically.\n");
            myqsort((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))numcmp);
        } else {
            printf("Sorting lexicographically.\n");
            myqsort((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))charcmp);
        }

        /* Write sorted lines */
        writelines(lineptr, nlines, option & DECR);
    } else {
        printf("Error: Input too large to sort.\n");
        return -1;
    }

    return 0;
}

/* Parse command-line arguments */
void readargs(int argc, char *argv[]) {
    int c;
    while (--argc > 0 && ((c = (*++argv)[0]) == '-' || c == '+')) {
        if (c == '-' && !isdigit(*(argv[0] + 1))) {
            while ((c = *++argv[0])) {
                switch (c) {
                    case 'd':
                        option |= MDIR;
                        break;
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
                        printf("Error: Illegal option '%c'.\n", c);
                        error("Usage: sort -dfnr [+pos1] [-pos2]");
                        break;
                }
            }
        } else if (c == '-') {
            pos2 = atoi(argv[0] + 1);
        } else if ((pos1 = atoi(argv[0] + 1)) < 0) {
            error("Usage: sort -dfnr [+pos1] [-pos2]");
        }
    }

    if (argc || pos1 > pos2) {
        error("Usage: sort -dfnr [+pos1] [-pos2]");
    }
}

/* Read input lines */
int readlines(char *lineptr[], int maxlines) {
    int len, nlines = 0;
    char *p, line[MAXLEN];

    while ((len = mgetline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
        } else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }

    return nlines;
}

/* Write output lines */
void writelines(char *lineptr[], int nlines, int order) {
    printf("\nSorted lines:\n");
    for (int i = 0; i < nlines; i++) {
        printf("%s\n", order ? lineptr[nlines - i - 1] : lineptr[i]);
    }
}

/* Numeric comparison */
int numcmp(char *s1, char *s2) {
    double v1, v2;
    char str[MAXLEN];

    substr(s1, str, MAXLEN);
    v1 = atof(str);

    substr(s2, str, MAXLEN);
    v2 = atof(str);

    return (v1 < v2) ? -1 : (v1 > v2) ? 1 : 0;
}

/* Lexicographic comparison */
int charcmp(char *s1, char *s2) {
    char a, b;
    int i = pos1, j = pos1;

    while (i < pos2 && j < pos2 && s1[i] && s2[j]) {
        a = (option & FOLD) ? tolower(s1[i]) : s1[i];
        b = (option & FOLD) ? tolower(s2[j]) : s2[j];

        if (a != b) {
            return a - b;
        }
        i++;
        j++;
    }

    return 0;
}

/* Extract substring */
void substr(char *s, char *str, int maxstr) {
    int i, j = 0;

    for (i = pos1; i < pos2 && s[i] && j < maxstr - 1; i++) {
        str[j++] = s[i];
    }

    str[j] = '\0';
}

/* Allocate memory */
char *alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else {
        return NULL;
    }
}

/* Free allocated memory */
void afree(char *p) {
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE) {
        allocp = p;
    }
}

/* Print error message and exit */
void error(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

/* Read a line */
int mgetline(char s[], int lim) {
    int c, i = 0;
    while (i < lim - 1 && (c = getchar()) != EOF && c != '\n') {
        s[i++] = c;
    }
    if (c == '\n') {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

/* Quick sort implementation */
void myqsort(void *v[], int left, int right, int (*comp)(void *, void *)) {
    int i, last;
    void swap(void *v[], int i, int j);

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

/* Swap two elements */
void swap(void *v[], int i, int j) {
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}


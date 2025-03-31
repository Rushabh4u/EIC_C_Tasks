/*
 * Add the -d ("Directory option") which makes comparison only on letters, numbers and blanks.
 * Make sure it works in conjunction with -f
 * 
*/

#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

/* Constants for various options */
#define NUMERIC 1    /* Numeric sort */
#define DECR    2    /* Sort in decreasing order */
#define FOLD    4    /* Fold upper and lower cases */
#define MDIR    8    /* Directory order (letters, numbers, blanks only) */
#define LINES   100  /* Maximum number of lines to sort */
#define MAXLEN  1000 /* Maximum length of any input line */
#define ALLOCSIZE 10000 /* Size of available space for allocation */

/* Allocation buffer */
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

/* Option flags */
static char option = 0;

/* Function prototypes */
void swap(void *v[], int i, int j);
int mgetline(char s[], int lim);
char *alloc(int n);
void afree(char *p);
void myqsort(void *v[], int left, int right, int (*comp)(void *, void *));
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines, int order);
int numcmp(char *s1, char *s2);
int charcmp(char *s, char *t);

/* Main function to sort input lines */
int main(int argc, char *argv[]) {
    char *lineptr[LINES];
    int nlines;
    int c, rc = 0;

    printf("Sorting Program with Various Options\n");
    printf("Use '-d' for directory order, '-f' for folding cases, '-n' for numeric sort, and '-r' for reverse order.\n\n");

    /* Parse command-line arguments */
    while (--argc > 0 && (*++argv)[0] == '-') {
        while (c = *++argv[0]) {
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
                    printf("Error: Illegal option '%c'\n", c);
                    argc = 1;
                    rc = -1;
                    break;
            }
        }
    }

    /* Check for invalid usage */
    if (argc) {
        printf("Usage: sort -dfnr\n");
    } else {
        printf("Reading lines...\n");
        if ((nlines = readlines(lineptr, LINES)) > 0) {
            printf("Sorting lines...\n");
            if (option & NUMERIC) {
                myqsort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) numcmp);
            } else {
                myqsort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) charcmp);
            }
            printf("Writing sorted lines...\n");
            writelines(lineptr, nlines, option & DECR);
        } else {
            printf("Error: Input too large to sort.\n");
            rc = -1;
        }
    }

    return rc;
}

/* Swap two elements */
void swap(void *v[], int i, int j) {
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* Read a line into s, return its length */
int mgetline(char s[], int lim) {
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
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
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

/* Quick sort implementation */
void myqsort(void *v[], int left, int right, int (*comp)(void *, void *)) {
    int i, last;

    if (left >= right) /* No need to sort if array contains fewer than two elements */
        return;

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++) {
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    }

    swap(v, left, last);
    myqsort(v, left, last - 1, comp);
    myqsort(v, last + 1, right, comp);
}

/* Read lines from input */
int readlines(char *lineptr[], int maxlines) {
    int len, nlines = 0;
    char *p, line[MAXLEN];

    while ((len = mgetline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        line[len - 1] = '\0'; /* Remove newline character */
        strcpy(p, line);
        lineptr[nlines++] = p;
    }

    return nlines;
}

/* Write lines to output */
void writelines(char *lineptr[], int nlines, int order) {
    if (order) {
        for (int i = nlines - 1; i >= 0; i--)
            printf("%s\n", lineptr[i]);
    } else {
        for (int i = 0; i < nlines; i++)
            printf("%s\n", lineptr[i]);
    }
}

/* Compare numbers */
int numcmp(char *s1, char *s2) {
    double v1 = atof(s1);
    double v2 = atof(s2);

    if (v1 < v2) return -1;
    else if (v1 > v2) return 1;
    else return 0;
}

/* Compare characters with optional folding and directory order */
int charcmp(char *s, char *t) {
    char a, b;
    int fold = (option & FOLD) ? 1 : 0;
    int dir = (option & MDIR) ? 1 : 0;

    do {
        if (dir) {
            while (!isalnum(*s) && *s != ' ' && *s != '\0')
                s++;
            while (!isalnum(*t) && *t != ' ' && *t != '\0')
                t++;
        }

        a = fold ? tolower(*s) : *s;
        b = fold ? tolower(*t) : *t;

        s++;
        t++;

        if (a == b && a == '\0')
            return 0;
    } while (a == b);

    return a - b;
}


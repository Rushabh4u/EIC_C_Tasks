/*
 * Program: Line Sorting Program
 * Author: 164993_faizan_momin
 * Created Date: 17/12/2024
 * Description: This program reads lines of input, sorts them in lexicographical order using quicksort,
 *              and then prints the sorted lines. It includes functions for reading input lines, sorting,
 *              and managing memory with dynamic allocation.
 */

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000   /* max #lines to be sorted */
#define MAXLEN 1000     /* max length of any input line */
#define MAXSTOR 5000    /* maximum storage for lines */

char *lineptr[MAXLINES]; /* pointers to input lines */
char linestor[MAXSTOR];  /* storage for input lines */

/* function prototypes */
int readlines(char *lineptr[], char *linestor, int maxlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *v[], int left, int right);
int mgetline(char *s, int lim);
void swap(char *v[], int i, int j);

int main(void) {
    int nlines; /* number of input lines read */

    if ((nlines = readlines(lineptr, linestor, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines - 1);  /* sort lines */
        writelines(lineptr, nlines);    /* print sorted lines */
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

/* readlines: read input lines */
int readlines(char *lineptr[], char *linestor, int maxlines) {
    int len, nlines;
    char line[MAXLEN];
    char *p = linestor;  /* pointer to storage */
    char *linestop = linestor + MAXSTOR;
    
    nlines = 0;
    
    while ((len = mgetline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || p + len > linestop) {
            return -1;  /* error: too many lines or not enough space */
        } else {
            line[len - 1] = '\0';  /* remove newline */
            strcpy(p, line);  /* copy line into storage */
            lineptr[nlines++] = p;  /* save pointer to line */
            p += len;  /* move pointer to next available space */
        }
    }
    
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
    for (int i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);  /* print each line */
    }
}

/* qsort: sort v[left] ... v[right] into increasing order */
void qsort(char *v[], int left, int right) {
    int i, last;
    
    if (left >= right) return;
    
    swap(v, left, (left + right) / 2);  /* pivot element */
    
    last = left;
    
    for (i = left + 1; i <= right; i++) {
        if (strcmp(v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }
    
    swap(v, left, last);  /* move pivot to its final place */
    
    qsort(v, left, last - 1);  /* sort left half */
    qsort(v, last + 1, right);  /* sort right half */
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j) {
    char *temp;
    
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* mgetline: read a line into s, return length */
int mgetline(char *s, int lim) {
    int c;
    char *t = s;
    
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
        *s++ = c;  /* copy character to string */
    }
    
    if (c == '\n') {
        *s++ = c;  /* include the newline character */
    }
    
    *s = '\0';  /* null-terminate the string */
    
    return s - t;  /* return number of characters read */
}


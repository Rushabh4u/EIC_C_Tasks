/**
 * This program Prints the last n lines of its input.
 * By default, n is 10, but it can be changed using the optional argument -n.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFLINES 10 /* Default number of lines to print */
#define LINES    100 /* Maximum number of lines to print */
#define MAXLEN   100 /* Maximum length of an input line */

/* Function Declarations */
void error(const char *msg);
int mgetline(char *line, int maxlen);

/**
 * Main function: Reads input and prints the last n lines.
 * @argc: Argument count.
 * @argv: Argument values.
 */
int main(int argc, char *argv[]) {
    char *p;                 /* Pointer to the large buffer */
    char *buf;               /* Buffer for storing lines */
    char *bufend;            /* End of the buffer */
    char line[MAXLEN];       /* Temporary storage for an input line */
    char *lineptr[LINES];    /* Array of pointers to lines */

    int first, last, len, n, nlines, i;

    /* Display program info */
    printf("\nTail Program\n");
    printf("-----------------------------------\n");
    printf("This program prints the last n lines of input.\n");
    printf("Use '-n' to specify the number of lines. Default is %d.\n\n", DEFLINES);

    /* Determine the number of lines to print */
    if (argc == 1) {
        n = DEFLINES;
    } else if (argc == 2 && (*++argv)[0] == '-') {
        n = atoi(argv[0] + 1);
        if (n <= 0) {
            error("Invalid value for -n. Please specify a positive number.");
        }
    } else {
        error("Usage: tail [-n]");
    }

    if (n > LINES) {
        printf("Number of lines exceeds the maximum limit (%d). Using maximum value.\n", LINES);
        n = LINES;
    }

    for (i = 0; i < LINES; i++) {
        lineptr[i] = NULL;
    }

    if ((p = buf = malloc(LINES * MAXLEN)) == NULL) {
        error("Cannot allocate memory for buffer.");
    }
    bufend = buf + LINES * MAXLEN;

    last = 0;
    nlines = 0;

    /* Read lines and store them in a circular buffer */
    while ((len = mgetline(line, MAXLEN)) > 0) {
        if (p + len + 1 >= bufend) {
            p = buf; /* Wrap around */
        }
        lineptr[last] = p;
        strcpy(lineptr[last], line);

        if (++last >= LINES) {
            last = 0; /* Wrap around */
        }
        p += len + 1;
        nlines++;
    }

    /* Adjust n if the number of lines read is less */
    if (n > nlines) {
        n = nlines;
    }

    first = last - n;
    if (first < 0) {
        first += LINES;
    }

    printf("\nLast %d lines of input:\n-----------------------------------\n", n);

    for (i = first; n-- > 0; i = (i + 1) % LINES) {
        printf("%s", lineptr[i]);
    }

    /* Free allocated memory */
    free(buf);
    return 0;
}

/**
 * error: Prints an error message and exits the program.
 * @msg: The error message to display.
 */
void error(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(EXIT_FAILURE);
}

/**
 * mgetline: Reads a line from standard input into a buffer.
 * @line: Buffer to store the line.
 * @maxlen: Maximum length of the buffer.
 * @return: The length of the line read.
 */
int mgetline(char *line, int maxlen) {
    int c, i;

    for (i = 0; i < maxlen - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        line[i] = c;
    }
    if (c == '\n') {
        line[i++] = c;
    }
    line[i] = '\0';

    return i;
}


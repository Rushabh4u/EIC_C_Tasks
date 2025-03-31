/*
 * Program to print a set of files, starting each new one on a new page,
 * with a title and a running page count for each file.
 *
 * Created By: Rushabh Goswami
 * Created On: 12/22/2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 80   /* Maximum number of characters per line */
#define LINES_PER_PAGE 10    /* Number of lines per page */

/* Function Prototypes */
void printFilePages(FILE *inputFile, FILE *outputFile);

int main(int argc, char *argv[]) {
    FILE *filePointer;          /* Pointer for the file being processed */
    char *programName = argv[0]; /* Program name */
    
    /* If no files are provided, print an error message */
    if (argc == 1) {
        fprintf(stderr, "No files given\n");
        printFilePages(stdin, stdout);  /* Process standard input */
    } else {
        /* Loop through all the given file arguments */
        while (--argc > 0) {
            /* Try to open the current file */
            if ((filePointer = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "%s: can't open %s\n", programName, *argv);
                exit(1);
            } else {
                /* Print the file name as the title */
                fprintf(stdout, "\n\n\t\t\tFile: %s\n\n", *argv);
                /* Print the pages for this file */
                printFilePages(filePointer, stdout);
                fclose(filePointer); /* Close the file */
            }
        }
    }

    /* Check if there were any errors writing to stdout */
    if (ferror(stdout)) {
        fprintf(stderr, "%s: error writing stdout\n", programName);
        exit(2);
    }
    exit(0);
}

/*
 * Function: printFilePages
 * ------------------------
 * This function reads content from the input file and prints it to the output,
 * managing page breaks and line numbers. Each new page starts with a page count.
 *
 * Parameters:
 *   inputFile   - The file from which content is being read
 *   outputFile  - The file to which content is written (stdout in this case)
 */
void printFilePages(FILE *inputFile, FILE *outputFile) {
    int currentChar;          /* Current character being read from the input file */
    int lineCount = 0;        /* Tracks the number of lines on the current page */
    int pageNumber = 1;       /* Tracks the current page number */

    /* Read characters from the input file until the end of the file */
    while ((currentChar = getc(inputFile)) != EOF) {
        putc(currentChar, outputFile); /* Print the current character to the output file */

        if (currentChar == '\n') { /* If the character is a newline */
            lineCount++;  /* Increment the line count */
            /* If the line count reaches the lines per page, print a page break */
            if (lineCount == LINES_PER_PAGE) {
                fprintf(stdout, "\n\t\t\tPage %d End.\n\n", pageNumber);
                pageNumber++;  /* Increment the page number */
                lineCount = 0; /* Reset the line count */
            }
        }
    }
}


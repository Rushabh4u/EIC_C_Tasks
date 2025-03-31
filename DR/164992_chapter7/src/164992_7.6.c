/*
 * Program to compare two files and print the first line where they differ.
 * Created By: Rushabh Goswami
 * Created On: 12/22/2024
 */

#include <stdio.h>

/* Function Prototypes */
void compareTwoFiles(FILE *fileFirst, FILE *fileSecond);

int main(int argCount, char *argValues[]) {
    FILE *fileFirstPtr, *fileSecondPtr; /* File pointers for the two files to compare */

    /* Check if the user provided exactly two file arguments */
    if (argCount != 3) {
        printf("Usage: %s <fileFirst> <fileSecond>\n", argValues[0]);
        return 1; /* Exit with error code */
    }

    /* Attempt to open the first file in read mode */
    if ((fileFirstPtr = fopen(argValues[1], "r")) == NULL) {
        printf("Error: Unable to open file %s\n", argValues[1]);
        return 1; /* Exit with error code */
    }

    /* Attempt to open the second file in read mode */
    if ((fileSecondPtr = fopen(argValues[2], "r")) == NULL) {
        printf("Error: Unable to open file %s\n", argValues[2]);
        fclose(fileFirstPtr); /* Close the first file before exiting */
        return 1; /* Exit with error code */
    }

    /* Compare the two files line by line */
    compareTwoFiles(fileFirstPtr, fileSecondPtr);

    /* Close both file pointers after the comparison */
    fclose(fileFirstPtr);
    fclose(fileSecondPtr);

    return 0; /* Exit successfully */
}

/*
 * Function: compareTwoFiles
 * -------------------------
 * Compares two files line by line and prints the first line where they differ.
 *
 * Parameters:
 *   fileFirst - Pointer to the first file
 *   fileSecond - Pointer to the second file
 */
void compareTwoFiles(FILE *fileFirst, FILE *fileSecond) {
    int charFirstFile, charSecondFile; /* Characters read from each file */
    int lineCounter = 1;              /* Keeps track of the current line number */
    int columnCounter = 0;            /* Keeps track of the current column number within the line */

    /* Read characters from both files until EOF or a difference is found */
    while (1) {
        charFirstFile = getc(fileFirst);
        charSecondFile = getc(fileSecond);
        columnCounter++;

        /* Check if either file has reached EOF */
        if (charFirstFile == EOF || charSecondFile == EOF) {
            if (charFirstFile != charSecondFile) {
                printf("Files differ at line %d, column %d\n", lineCounter, columnCounter);
            } else {
                printf("Files are identical.\n");
            }
            break;
        }

        /* Check for new line characters */
        if (charFirstFile == '\n' && charSecondFile == '\n') {
            lineCounter++;  /* Increment the line counter */
            columnCounter = 0; /* Reset the column counter */
        }

        /* If characters differ, print the details and exit */
        if (charFirstFile != charSecondFile) {
            printf("Files differ at line %d, column %d\n", lineCounter, columnCounter);
            printf("FileFirst: '%c'\nFileSecond: '%c'\n", charFirstFile, charSecondFile);
            break;
        }
    }
}


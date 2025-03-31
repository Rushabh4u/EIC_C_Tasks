/*
 * Program to find a specific pattern in a single input file.
 * The pattern is provided by the user at runtime.
 * Created By: Rushabh Goswami
 * Created On: 12/22/2024
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000 /* Maximum length of a single input line */

/* Function Prototypes */
int readLine(char *inputBuffer, int maxLength, FILE *inputStream);
int findPatternIndex(char *mainString, char *searchPattern);

int main(int argc, char *argv[]) {
    char inputLine[MAX_LINE_LENGTH]; /* Array to hold the current input line */
    char searchPattern[MAX_LINE_LENGTH]; /* String to store the search pattern */
    int matchCount = 0;              /* Count of matching lines */

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        return 1; /* Return error if the file name is not provided */
    }

    // Open the file
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror(argv[1]);
        return 1; /* Return error if the file cannot be opened */
    }

    // Prompt the user for the search pattern
    printf("Enter the search pattern: ");
    if (fgets(searchPattern, MAX_LINE_LENGTH, stdin) == NULL) {
        fprintf(stderr, "Failed to read the search pattern.\n");
        fclose(file);
        return 1;
    }

    // Remove the trailing newline character from the search pattern
    searchPattern[strcspn(searchPattern, "\n")] = '\0';

    // Search for the pattern in the file
    while (readLine(inputLine, MAX_LINE_LENGTH, file) > 0) {
        if (findPatternIndex(inputLine, searchPattern) >= 0) {
            printf("%s\n", inputLine); /* Print the line if it contains the pattern */
            matchCount++;
        }
    }

    fclose(file);
    printf("Total matching lines: %d\n", matchCount);
    return matchCount; /* Return the count of matching lines */
}

/*
 * Function: readLine
 * ------------------
 * Reads a single line of input into a string.
 * Stops reading at a newline or when the limit is reached.
 *
 * Parameters:
 *   inputBuffer - Array to store the input line
 *   maxLength   - Maximum allowed length of the line
 *   inputStream - The input stream to read from (a file)
 *
 * Returns:
 *   The length of the line read (number of characters).
 */
int readLine(char *inputBuffer, int maxLength, FILE *inputStream) {
    int character;              /* Current character being read */
    char *lineStart = inputBuffer; /* Pointer to the start of the line */

    /* Read characters until the limit, EOF, or newline is reached */
    while (--maxLength > 0 && (character = fgetc(inputStream)) != EOF && character != '\n') {
        *inputBuffer++ = character;
    }

    /* If a newline is encountered, include it in the buffer */
    if (character == '\n') {
        *inputBuffer++ = character;
    }
    *inputBuffer = '\0'; /* Null-terminate the string */

    return inputBuffer - lineStart; /* Return the length of the line */
}

/*
 * Function: findPatternIndex
 * --------------------------
 * Searches for the first occurrence of a pattern in a string.
 *
 * Parameters:
 *   mainString     - The string to search in
 *   searchPattern  - The pattern to search for
 *
 * Returns:
 *   The starting index of the pattern if found, or -1 if not found.
 */
int findPatternIndex(char *mainString, char *searchPattern) {
    char *stringStart = mainString; /* Pointer to the start of the string */
    char *mainPtr, *patternPtr;
    /* Pointers for traversing the main string and the pattern */

    /* Traverse the main string */
    for (; *mainString != '\0'; mainString++) {
        /* Compare the current substring with the pattern */
        for (mainPtr = mainString, patternPtr = searchPattern;
             *patternPtr != '\0' && *mainPtr == *patternPtr;
             mainPtr++, patternPtr++);

        /* If the entire pattern matches, return the starting index */
        if (patternPtr > searchPattern && *patternPtr == '\0') {
            return mainString - stringStart;
        }
    }
    return -1; /* Return -1 if the pattern is not found */
}


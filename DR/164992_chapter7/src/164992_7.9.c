/*
 * Functions like isupper can be implemented to save space or to save time.
 * This program explores both possibilities.
 * Created by: Rushabh Goswami
 * Created on: 12/22/2024
 */

#include <stdio.h>
#include <stdlib.h>

/* Function Prototypes */
int isUpperCase(int);

/* Sample input string */
const char *testInput = "AbCdEfx";  /* String to check */
int inputIndex = 0;                  /* Index for reading through the testInput */

/* Custom getchar function to simulate input reading */
int customGetChar(void) {
    if (testInput[inputIndex] == '\0') { /* End of string */
        return EOF;  /* Return EOF when the string ends */
    } else {
        return testInput[inputIndex++]; /* Return the current character and move to the next */
    }
}

int main(void) {
    int currentChar;  /* Current character from input */

    /* Loop through the input string until 'x' is encountered */
    while ((currentChar = customGetChar()) != 'x') {
        if (currentChar == '\n') /* Skip newline characters */
            continue;

        /* Check if the current character is uppercase and print the result */
        if (isUpperCase(currentChar) == 1)
            printf("true\n");
        else
            printf("false\n");
    }
    return EXIT_SUCCESS;
}

/* Function to check if a character is uppercase */
int isUpperCase(int character) {
    if (character >= 'A' && character <= 'Z') /* Check if character is between 'A' and 'Z' */
        return 1; /* Return true if uppercase */
    else
        return 0; /* Return false otherwise */
}


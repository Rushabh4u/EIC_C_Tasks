#include <ctype.h>  /* Character type handling library */
#include <stdio.h>  /* Standard Input/Output library */
#include <string.h> /* String manipulation library */

/* Function to convert a string to uppercase */
void to_uppercase(const char *input) {
    while (*input) {
        putchar(toupper(*input));
        input++;
    }
    putchar('\n');
}

/* Function to convert a string to lowercase */
void to_lowercase(const char *input) {
    while (*input) {
        putchar(tolower(*input));
        input++;
    }
    putchar('\n');
}

/* Main function */
int main() {
    char input[256];  /* Buffer to hold the input string */
    int choice;       /* User's menu choice */

    printf("Enter a string (max 255 characters): ");
    fgets(input, sizeof(input), stdin);

    /* Remove newline character if present */
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    /* Display menu options */
    printf("\nMenu:\n");
    printf("1. Convert to Uppercase\n");
    printf("2. Convert to Lowercase\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    /* Perform conversion based on user's choice */
    switch (choice) {
        case 1:
            printf("\nUppercase: ");
            to_uppercase(input);
            break;
        case 2:
            printf("\nLowercase: ");
            to_lowercase(input);
            break;
        default:
            printf("\nInvalid choice. Please select 1 or 2.\n");
            break;
    }

    return 0;
}


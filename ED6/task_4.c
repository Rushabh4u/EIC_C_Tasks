/*
 * Created by Rushabh Goswami (164992)
 */
 
/* Required header files */
/* stdio for input-output functions, stdlib for memory allocation, and string.h for string operations */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    /* 
     * Open the file "OutPut.txt" in read mode 
     * If the file cannot be opened, display an error message and exit the program
     */
    FILE *file = fopen("OutPut.txt", "r");
    if (file == NULL) {
        /* If the file is not found, display an error message and return */
        printf("Error opening file");
        return 0;
    }

    /* 
     * Prompt the user to enter the name they want to search for 
     * The entered name is stored in the 'searchName' array 
     */
    printf("Enter the name which you want to search: ");
    char searchName[50]; /* Array to store the name entered by the user */
    scanf("%s", searchName); /* Read the user input for the name to search */

    /* Buffer to store each line read from the file */
    char line[256];

    /* 
     * Loop through each line in the file 
     * fgets reads each line from the file and stores it in the 'line' buffer
     */
    while (fgets(line, sizeof(line), file)) {

        /* 
         * Declare variables to store data parsed from each line 
         * iIndex - stores the index of the record
         * cName - stores the name of the person
         * cHomeTown - stores the hometown of the person
         * iAge - stores the age of the person
         * iSalary - stores the salary of the person
         */
        int iIndex;
        char cName[50], cHomeTown[50];
        int iAge, iSalary;

        /* 
         * Use sscanf to parse the data from the line 
         * The format string "%d %s %s %d %d" extracts index, name, hometown, age, and salary
         */
        sscanf(line, "%d %s %s %d %d", &iIndex, cName, cHomeTown, &iAge, &iSalary);

        /* 
         * Compare the name from the file with the name entered by the user 
         * If the names match (using strcmp), print the person's details
         */
        if (strcmp(cName, searchName) == 0) {
            /* Print the person's details if the name matches */
            printf("name : %s\n", cName);
            printf("town : %s\n", cHomeTown);
            printf("age : %d\n", iAge);
            printf("salary : %d\n\n", iSalary);
        }
    }

    /* 
     * Close the file after reading 
     * Closing the file releases system resources
     */
    fclose(file);
    return 0; /* Return 0 to indicate successful execution */
}


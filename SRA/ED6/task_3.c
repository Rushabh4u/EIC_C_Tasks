/*
 * Created by Rushabh Goswami (164992)
 */

/* Required header files */
/* stdio for input-output functions and stdlib for standard library functions */
#include <stdio.h>
#include <stdlib.h>

int main() {

    /* 
     * Open the file "OutPut.txt" in read mode 
     * If the file cannot be opened, display an error message and exit the program
     */
    FILE *file = fopen("OutPut.txt", "r");
    if (file == NULL) {
        /* If file is not found, display error and return */
        printf("Error opening file");
        return 0;
    }

    /* Buffer to store each line read from the file */
    char line[256];

    /* 
     * Loop through each line in the file 
     * fgets reads each line from the file until end of file (EOF) is reached
     */
    while (fgets(line, sizeof(line), file)) {

        /* 
         * Declare variables to store data from each line 
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
         * Use sscanf to parse data from the line 
         * The format string "%d %s %s %d %d" extracts index, name, hometown, age, and salary
         */
        sscanf(line, "%d %s %s %d %d", &iIndex, cName, cHomeTown, &iAge, &iSalary);

        /* 
         * Print the extracted data to the console 
         * Name, hometown, age, and salary are printed for each person
         */
        printf("name : %s\n", cName);
        printf("town : %s\n", cHomeTown);
        printf("age : %d\n", iAge);
        printf("salary : %d\n\n", iSalary);
    }

    /* 
     * Close the file after reading 
     * It's important to close the file to free system resources
     */
    fclose(file);
    return 0; /* Return 0 to indicate successful execution */
}


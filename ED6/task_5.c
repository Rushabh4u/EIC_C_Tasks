/*
 * Created by Rushabh Goswami (164992)
 */

/* Required header files */
/* stdio for input-output functions, stdlib for memory allocation, and string.h for string operations */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define maximum lengths for names, last names, and lines */
#define MAX_NAME_LENGTH 100
#define MAX_LAST_NAME_LENGTH 100
#define MAX_LINE_LENGTH 256

/* Structure to store a person's details including name, last name, age, and salary */
typedef struct {
    char name[MAX_NAME_LENGTH];
    char lastName[MAX_LAST_NAME_LENGTH];
    int age;
    int salary;
} Person;

/* 
 * Function to read the file "OutPut.txt", prompt the user to add last names, 
 * and save the updated data in a new file "OutPut_with_lastnames.txt" 
 */
void addLastNames() {
    /* Open the original file for reading and the new file for writing */
    FILE *file = fopen("OutPut.txt", "r");
    FILE *newFile = fopen("OutPut_with_lastnames.txt", "w");

    /* If either file fails to open, print an error message and exit the function */
    if (!file || !newFile) {
        perror("Failed to open file");
        return;
    }

    /* Buffer to store each line read from the file */
    char line[MAX_LINE_LENGTH];
    /* Structure to store the details of each person */
    Person person;
    int index = 0;  /* Index to track the number of entries */

    /* 
     * Read each line from the file 
     * Prompt the user for the last name of the person, and then write the updated
     * data (including the last name) to the new file
     */
    while (fgets(line, sizeof(line), file)) {
        /* Extract the name, age, and salary from the line, skipping the index and hometown */
        sscanf(line, "%*d %s %*s %d %d", person.name, &person.age, &person.salary);

        /* Prompt the user to input the last name for the person */
        printf("Enter last name for %s: ", person.name);
        fgets(person.lastName, MAX_LAST_NAME_LENGTH, stdin);

        /* Remove the newline character from the entered last name */
        person.lastName[strcspn(person.lastName, "\n")] = 0; 

        /* Write the updated data to the new file, including the index and last name */
        fprintf(newFile, "%d %s %s %d %d\n", index + 1, person.name, person.lastName, person.age, person.salary);
        index++;  /* Increment the index for the next person */
    }

    /* Close both files after processing */
    fclose(file);
    fclose(newFile);
}

/* 
 * Function to print the updated data from the file "OutPut_with_lastnames.txt" 
 */
void printUpdatedData() {
    /* Open the file with updated last names */
    FILE *file = fopen("OutPut_with_lastnames.txt", "r");

    /* If the file fails to open, print an error message and exit the function */
    if (!file) {
        perror("Failed to open file");
        return;
    }

    /* Buffer to store each line read from the file */
    char line[MAX_LINE_LENGTH];

    /* Print a heading for the updated list */
    printf("Updated List of People:\n");

    /* Read and print each line from the updated file */
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);  /* Output each line to the console */
    }

    /* Close the file after reading */
    fclose(file);
}

/* Main function to execute the program */
int main() {
    /* Call the function to add last names and save the updated data */
    addLastNames();

    /* Call the function to print the updated list of people */
    printUpdatedData();

    return 0;  /* Return 0 to indicate successful execution */
}


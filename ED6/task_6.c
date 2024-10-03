/*
 * Created by Rushabh Goswami (164992)
 * 
 * This program reads data from "OutPut.txt", allows the user to add additional information 
 * (last name, address, postal code, state), and writes the updated data to 
 * "OutPut_with_full_info.txt". The updated list is then printed to the console.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define maximum lengths for names, address fields, and input lines */
#define MAX_NAME_LENGTH 100
#define MAX_LAST_NAME_LENGTH 100
#define MAX_STREET_LENGTH 100
#define MAX_POSTAL_CODE_LENGTH 10
#define MAX_STATE_LENGTH 50
#define MAX_LINE_LENGTH 512

/* Structure to store a person's complete details including name, age, salary, and address */
typedef struct {
    char name[MAX_NAME_LENGTH];
    char lastName[MAX_LAST_NAME_LENGTH];
    int age;
    float salary;
    char street[MAX_STREET_LENGTH];
    int number;
    char postalCode[MAX_POSTAL_CODE_LENGTH];
    char state[MAX_STATE_LENGTH];
} Person;

/*
 * Function: addFullInfo
 * Purpose: This function reads data from "OutPut.txt", prompts the user to add more details
 *          (last name, street, number, postal code, state), and writes the updated information 
 *          to a new file "OutPut_with_full_info.txt".
 */
void addFullInfo() {
    /* Open the original file for reading and a new file for writing the updated data */
    FILE *file = fopen("OutPut.txt", "r");
    FILE *newFile = fopen("OutPut_with_full_info.txt", "w");

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
     * Read each line from the original file, prompt the user for additional details, 
     * and then write the updated data to the new file.
     */
    while (fgets(line, sizeof(line), file)) {
        /* Extract the name, age, and salary from the line, skipping the index and hometown */
        sscanf(line, "%*d %s %*s %d %f", person.name, &person.age, &person.salary);

        /* Prompt the user for the last name and additional address details */
        printf("\n\nEnter last name for %s: ", person.name);
        fgets(person.lastName, MAX_LAST_NAME_LENGTH, stdin);
        person.lastName[strcspn(person.lastName, "\n")] = 0; /* Remove the newline character */

        printf("Enter street for %s: ", person.name);
        fgets(person.street, MAX_STREET_LENGTH, stdin);
        person.street[strcspn(person.street, "\n")] = 0; /* Remove the newline character */

        printf("Enter number for %s: ", person.name);
        scanf("%d", &person.number);
        getchar(); /* Consume the newline character after entering the number */

        printf("Enter postal code for %s: ", person.name);
        fgets(person.postalCode, MAX_POSTAL_CODE_LENGTH, stdin);
        person.postalCode[strcspn(person.postalCode, "\n")] = 0; /* Remove the newline character */

        printf("Enter state for %s: ", person.name);
        fgets(person.state, MAX_STATE_LENGTH, stdin);
        person.state[strcspn(person.state, "\n")] = 0; /* Remove the newline character */

        /* Write the updated data to the new file */
        fprintf(newFile, "%d %s %s %d %.2f %s %d %s %s\n", index + 1, person.name, person.lastName, person.age, person.salary, person.street, person.number, person.postalCode, person.state);
        index++;  /* Increment the index for the next person */
    }

    /* Close both files after processing */
    fclose(file);
    fclose(newFile);
}

/*
 * Function: printUpdatedData
 * Purpose: This function reads the updated data from "OutPut_with_full_info.txt" and 
 *          prints it to the console.
 */
void printUpdatedData() {
    /* Open the file with the updated information */
    FILE *file = fopen("OutPut_with_full_info.txt", "r");

    /* If the file fails to open, print an error message and exit the function */
    if (!file) {
        perror("Failed to open file");
        return;
    }

    /* Buffer to store each line read from the file */
    char line[MAX_LINE_LENGTH];

    /* Print a heading for the updated list */
    printf("Updated List of People with Full Information:\n");

    /* Read and print each line from the updated file */
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);  /* Output each line to the console */
    }

    /* Close the file after reading */
    fclose(file);
}

/* 
 * Main function: This function calls the addFullInfo() function to update the data and 
 *                then calls the printUpdatedData() function to display the updated data.
 */
int main() {
    /* Call the function to add last names and save the updated data */
    addFullInfo();

    /* Call the function to print the updated list of people */
    printUpdatedData();

    return 0;  /* Return 0 to indicate successful execution */
}


/* 
*Command to run this program: 
*
*	./task_V2.2 01 12 2024 ages.txt
*
*Created by Rushabh Goswami (164992)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define a structure to store a date (day, month, year) */
typedef struct {
    int day;
    int month;
    int year;
} Date;

/* Define a structure to store a person's name and birthdate */
typedef struct {
    char name[100];
    Date birthdate;
} Person;

/* Function to read a person's data (name and birthdate) from the file */
int read_person(FILE *file, Person *person) {
    /* Read the person's name. If it's the end of the file, return 0 (stop reading) */
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        /* Skip blank lines */
        if (strlen(line) > 1) {
            strcpy(person->name, line);
            person->name[strcspn(person->name, "\n")] = '\0';  /* Remove the newline character */
            break;
        }
    }

    /* If no valid name is found, return 0 */
    if (feof(file)) {
        return 0;
    }

    /* Now, try to read the person's birthdate */
    int result = fscanf(file, "%d %d %d", &person->birthdate.day, &person->birthdate.month, &person->birthdate.year);

    /* If birthdate reading fails, return 0 */
    if (result != 3) {
        return 0;
    }

    return 1; /* Return 1 to indicate successful reading */
}


/* Function to calculate the age of a person based on the current date */
void calculate(Date current, Person *person, int *years, int *months, int *days) {
    /* 
    Adjust the day and month if the current day/month is earlier 
    than the birthdate's day/month
    */
    if (current.day < person->birthdate.day) {
        current.day += 30;  /* Assume 30 days in a month */
        current.month--;     /* Borrow a month */
    }
    if (current.month < person->birthdate.month) {
        current.month += 12; /* Borrow a year */
        current.year--;      /* Reduce the year */
    }

    /* 
    Calculate the difference in years, months, and days
    */
    *years = current.year - person->birthdate.year;
    *months = current.month - person->birthdate.month;
    *days = current.day - person->birthdate.day;
}

/* Main function */
int main(int argc, char *argv[]) {
    /* 
    Ensure correct number of arguments are provided
    */
    if (argc != 5) {
        printf("Usage: %s <day> <month> <year> <file>\n", argv[0]);
        return 1;
    }

    /* 
    Parse the current date from command-line arguments
    */
    Date current;
    current.day = atoi(argv[1]);
    current.month = atoi(argv[2]);
    current.year = atoi(argv[3]);

    /* 
    Open the input file specified in the arguments
    */
    FILE *file = fopen(argv[4], "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    /* 
    Array to store multiple persons' data
    */
    Person people[100];
    int count = 0; /* Counter for the number of people */

    /* 
    Read each person's data from the file
    */
    while (read_person(file, &people[count])) {
        count++;
    }

    /* 
    Close the file after reading all data
    */
    fclose(file);

    /* 
    Variables to store data for oldest person and person with the longest name
    */
    int maxYears = -1, oldestIndex = -1;        /* To store the oldest person's info */
    int maxNameLength = 0, longestNameIndex = -1; /* To store the person with the longest name */

    /* 
    Output ages and find the oldest person and person with longest name
    */
    printf("The ages are:\n");
    for (int i = 0; i < count; i++) {
        int years, months, days;

        /* 
        Calculate age of each person based on the current date
        */
        calculate(current, &people[i], &years, &months, &days);
        
        /* 
        Print the person's age in years
        */
        printf("%s is %d years old\n", people[i].name, years);

        /* 
        Check if this person is the oldest
        */
        if (years > maxYears) {
            maxYears = years;
            oldestIndex = i;
        }

        /* 
        Check if this person has the longest name
        */
        int nameLength = strlen(people[i].name);
        if (nameLength > maxNameLength) {
            maxNameLength = nameLength;
            longestNameIndex = i;
        }
    }

    /* 
    Output the name of the oldest person
    */
    if (oldestIndex != -1) {
        printf("%s is the oldest of the %d persons in the file.\n", people[oldestIndex].name, count);
    }
    
    /* 
    Output the name of the person with the longest name
    */
    if (longestNameIndex != -1) {
        printf("The person with the longest name is: %s\n", people[longestNameIndex].name);
    }

    return 0; /* Successful execution */
}


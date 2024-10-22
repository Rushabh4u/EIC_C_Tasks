/*
* Created by Rushabh Goswami (164992)
*/

/* Required header files */
/* stdio for input/output functions */
#include <stdio.h>
#include <string.h>

/* Constants for maximum persons and string lengths */
#define MAX_PERSONS 3  /* We are storing data for 3 persons */
#define NAME_LENGTH 50 /* Maximum length of a person's name */
#define TOWN_LENGTH 50 /* Maximum length of a town or city name */

/* Define the Person structure to hold the data for each person */
struct Person {
    char name[NAME_LENGTH]; /* String to store the person's name */
    char town[TOWN_LENGTH]; /* String to store the person's town/city */
};

/*
 * Function: readPerson
 * --------------------
 * Reads the name and town/city for one person from user input.
 * 
 * p: Pointer to a Person structure where the input will be stored.
 * 
 * This function uses fgets to read input, and then it removes the 
 * trailing newline character added by fgets.
 */
void readPerson(struct Person *p) {
    printf("Enter name: ");
    fgets(p->name, NAME_LENGTH, stdin); /* Get name as input */
    p->name[strcspn(p->name, "\n")] = '\0'; /* Remove the newline character */

    printf("Enter town or city: ");
    fgets(p->town, TOWN_LENGTH, stdin); /* Get town as input */
    p->town[strcspn(p->town, "\n")] = '\0'; /* Remove the newline character */
}

/*
 * Function: searchTown
 * --------------------
 * Searches for the town of a person by their name in the given list.
 * 
 * persons: Array of Person structures containing the data to search.
 * count: Number of persons in the array.
 * nameToSearch: Name of the person whose town is being searched.
 * townFound: Buffer to store the found town if the person is found.
 * 
 * Returns 1 if the person is found and their town is stored in townFound,
 * otherwise returns 0 if the person is not found.
 */
int searchTown(struct Person persons[], int count, const char *nameToSearch, char *townFound) {
    /* Multi-line comment explaining the loop below */
    /*
     * We are looping through all the persons in the array, one by one.
     * For each person, we check if the name matches the nameToSearch.
     * If a match is found, we copy the town of that person into townFound.
     * We return 1 to indicate that the search was successful.
     * If no match is found, we return 0 at the end.
     */
    for (int i = 0; i < count; i++) {
        /* Check if the current person's name matches the search name */
        if (strcmp(persons[i].name, nameToSearch) == 0) {
            /* If a match is found, copy the town to townFound */
            strcpy(townFound, persons[i].town);
            return 1; /* Return 1 to indicate a successful search */
        }
    }
    /* If the loop finishes without finding a match, return 0 */
    return 0; /* Return 0 to indicate the person was not found */
}

/*
 * Function: displayMenu
 * ---------------------
 * Displays the available menu options and returns the user's choice.
 * 
 * This function prints a list of menu options and waits for the user
 * to enter their choice. It returns the selected option.
 */
int displayMenu() {
    int choice;
    
    /* Display the menu options */
    printf("\nMenu:\n");
    printf("1. Enter details for persons\n");
    printf("2. Search for a person by name\n");
    printf("3. Exit\n");
    
    /* Prompt the user to enter their choice */
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); /* Consume the newline character left by scanf */
    
    return choice;
}

/*
 * Main function
 * -------------
 * This is the entry point of the program. It displays a menu, allows 
 * the user to enter person details, search for a town by name, or exit 
 * the program. The program continues to display the menu until the user
 * chooses to exit.
 */
int main() {
    /* Declare an array to store data for 3 persons */
    struct Person persons[MAX_PERSONS];
    int personCount = 0; /* Number of persons entered */
    
    int running = 1; /* Variable to control the loop */
    
    while (running) {
        /* Display the menu and get the user's choice */
        int choice = displayMenu();
        
        switch (choice) {
            case 1:
                /* Option to enter details for persons */
                /*
                 * In this option, we loop through the persons array and call 
                 * readPerson() to collect details for each person. The user can 
                 * enter data for up to MAX_PERSONS. 
                 */
                if (personCount < MAX_PERSONS) {
                    readPerson(&persons[personCount]);
                    personCount++;
                } else {
                    printf("You have already entered details for %d persons.\n", MAX_PERSONS);
                }
                break;
            
            case 2: 
                /* Option to search for a person's town by name */
                /*
                 * This option allows the user to search for a person's town.
                 * The program prompts the user to enter the name of the person
                 * they want to search for, then calls searchTown() to find the 
                 * town.
                 */
                if (personCount == 0) {
                    printf("No persons have been entered yet.\n");
                } else {
                    char searchName[NAME_LENGTH];
                    char townFound[TOWN_LENGTH];
                    
                    /* Prompt the user to enter the name to search for */
                    printf("Enter the name of the person you want to search for: ");
                    fgets(searchName, NAME_LENGTH, stdin);
                    searchName[strcspn(searchName, "\n")] = '\0'; /* Remove newline */
                    
                    /* Call searchTown to search for the person's town */
                    if (searchTown(persons, personCount, searchName, townFound)) {
                        printf("This person lives in %s\n", townFound); /* Person found */
                    } else {
                        printf("This person is not found.\n"); /* Person not found */
                    }
                }
                break;
            
            case 3:
                /* Option to exit the program */
                /*
                 * This option allows the user to exit the program. We set 
                 * running to 0, which will end the while loop and terminate 
                 * the program.
                 */
                running = 0;
                printf("Exiting the program.\n");
                break;
            
            default:
                /* Handle invalid input */
                printf("Invalid choice. Please select a valid option from the menu.\n");
                break;
        }
    }
    
    return 0; /* Return 0 to indicate successful execution */
}


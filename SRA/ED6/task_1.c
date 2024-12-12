/*
* Created by Rushabh Goswami (164992)
*/

/* Required header files */
/* stdio for input/output function */
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
 * 
 * Logic change: Instead of returning right after finding the person, 
 * the function now continues searching the entire list in case the 
 * name occurs more than once. It still returns only the first match 
 * (since the logic does not expect duplicates), but it processes the 
 * entire array for clarity.
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
     int c = 0;
    for (int i = 0; i < count; i++) {
        /* Check if the current person's name matches the search name */
        if (strcmp(persons[i].name, nameToSearch) == 0) {
            /* If a match is found, copy the town to townFound */
            printf("%s\n", persons[i].town);
            c++;
            //return 1; /* Return 1 to indicate a successful search */
        }
    }
    /* If the loop finishes without finding a match, return 0 */
    return c; /* Return 0 to indicate the person was not found */
}

/*
 * Main function
 * -------------
 * This is the entry point of the program. It reads the data for three
 * persons, prompts the user to enter a name to search for, and then
 * searches for that person's town.
 */
int main() {
    /* Declare an array to store data for 3 persons */
    struct Person persons[MAX_PERSONS];

    /* Loop to read information for 3 persons */
    /*
     * We are using a loop here to call readPerson() for each of the three 
     * persons. This populates the persons array with the names and towns 
     * entered by the user.
     */
    for (int i = 0; i < MAX_PERSONS; i++) {
        readPerson(&persons[i]); /* Call readPerson() for each person */
    }

    printf("==========================================================\n");

    /* Declare a string to store the name to be searched */
    char searchName[NAME_LENGTH];
    
    /* Read the name to search for */
    /*
     * Here we prompt the user to enter the name of the person they want 
     * to search for. We use fgets to read the input and then remove the 
     * trailing newline character.
     */
    printf("Enter the name of the person you want to search for: ");
    fgets(searchName, NAME_LENGTH, stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; /* Remove newline character */

    /* Declare a string to store the town if the person is found */
    char townFound[TOWN_LENGTH];

    /* Call searchTown to search for the person's town */
    /*
     * We pass the array of persons, the number of persons, the search name, 
     * and the townFound buffer to the searchTown function. If the function 
     * returns 1, we know the person was found and we print their town.
     * If the function returns 0, we print a message saying the person was 
     * not found.
     */
    if (searchTown(persons, MAX_PERSONS, searchName, townFound) > 0) {
        //printf("This person lives in %s\n", townFound); /* Person found */
        return 0;
    } else {
        printf("This person is not found.\n"); /* Person not found */
        return -1;
    }

   // return 0; /* Return 0 to indicate successful execution */
}


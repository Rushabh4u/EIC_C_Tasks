/*
*Created by Rushabh Goswami (164992)
*/

/*required header files*/
/*stdio for input output function*/
#include <stdio.h>
#include <string.h>
 
#define MAX_PERSONS 3
#define NAME_LENGTH 50
#define TOWN_LENGTH 50
 
/* Define the Person structure */
struct Person {
    char name[NAME_LENGTH];
    char town[TOWN_LENGTH];
};
 
/* Function to read a person's information */
void readPerson(struct Person *p) {
    printf("Enter name: ");
    fgets(p->name, NAME_LENGTH, stdin);
    p->name[strcspn(p->name, "\n")] = '\0'; // Remove newline character */
 
    printf("Enter town or city: ");
    fgets(p->town, TOWN_LENGTH, stdin);
    p->town[strcspn(p->town, "\n")] = '\0'; /* Remove newline character */
}
 
/* Function to search for a person's town by name */
int searchTown(struct Person persons[], int count, const char *nameToSearch, char *townFound) {
    for (int i = 0; i < count; i++) {
        if (strcmp(persons[i].name, nameToSearch) == 0) {
            strcpy(townFound, persons[i].town);
            return 1; /* Found */
        }
    }
    return 0; /* Not found */
}
 
int main() {
    struct Person persons[MAX_PERSONS];
 
    /* Read information for 3 persons */
    for (int i = 0; i < MAX_PERSONS; i++) {
        readPerson(&persons[i]);
    }
 
    printf("==========================================================\n");
    /* Read the name to search for */
    char searchName[NAME_LENGTH];
    printf("Enter the name of the person you want to search for: ");
    fgets(searchName, NAME_LENGTH, stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; // Remove newline character */
 
    /* Search for the town */
    char townFound[TOWN_LENGTH];
    if (searchTown(persons, MAX_PERSONS, searchName, townFound)) {
        printf("This person lives in %s\n", townFound);
    } else {
        printf("This person is not found.\n");
    }
 
    return 0;
}

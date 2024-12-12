/*
*Created by Rushabh Goswami (164992)
*/

/* Required header files */
#include<stdio.h>    /* stdio for input-output functions */
#include<string.h>   /* string.h for string manipulation functions like strcpy and strcmp */
 
/* Define constants */
#define MAX_INPUT 14  /* Maximum length for input strings */
 
/* Structure to store information of a person */
struct Person {
	char cName[MAX_INPUT];      /* Store the name of the person */
	char cHomeTown[MAX_INPUT];  /* Store the hometown of the person */
	int iAge;                   /* Store the age of the person */
	int iSalary;                /* Store the salary of the person */
};

/* Function prototypes */
void inputPersons(struct Person Persons[], int numPersons);              /* Function to input person details */
void add_age_salary(struct Person persons[], char cSearchName[], int numPersons); /* Function to add age and salary */
void file_save(struct Person Persons[]);                                /* Function to save the details into a file */

/* Main function */
int main() {
	struct Person Persons[3];  /* Array of 3 persons */
	
	/* Input person details */
	printf("\t\t\tINPUT");
	inputPersons(Persons, 3);
	printf("\n=========================================================\n");

	int iRunAgain = 0;  /* Variable to decide if the loop should run again */

	/* Loop to search and add age and salary for a person */
	do {
		char cSearchName[MAX_INPUT];  /* Variable to store the name to be searched */
		printf("--> Enter the name of the person whose 'age' and 'salary' you want to add: ");
		scanf("%s", cSearchName);  /* Read the name */
		add_age_salary(Persons, cSearchName, 3);  /* Add age and salary for the specified name */
		printf("\n");
		
		/* Ask the user if they want to search again */
		printf("Do you want to Search Again [1 for YES / 0 for NO]: "); 
		scanf("%d", &iRunAgain);
		printf("\n");

		/* Flush the input buffer */
		fflush(stdin);

	} while(iRunAgain);  /* Continue the loop if the user inputs 1 */

	/* Save the details to the file */
	file_save(Persons);
	return 0;
}

/* 
 * Function to input the details of the persons 
 * Persons - Array of Person structures
 * numPersons - Number of persons to input 
 */
void inputPersons(struct Person Persons[], int numPersons) {
	for (int iInputCounter = 0; iInputCounter < numPersons; iInputCounter++) {
		char cInputName[MAX_INPUT];      /* Temporary variable to store input name */
		char cInputHomeTown[MAX_INPUT];  /* Temporary variable to store input hometown */

		/* Prompt and input details for each person */
		printf("\nFor Person %d\n", (iInputCounter+1));
		printf("Enter Name: ");
		scanf("%s", cInputName);        /* Read name */
		printf("Enter HomeTown: ");
		scanf("%s", cInputHomeTown);    /* Read hometown */

		/* Copy input values into the Persons array */
		strcpy(Persons[iInputCounter].cName, cInputName);
		strcpy(Persons[iInputCounter].cHomeTown, cInputHomeTown);
	}
}

/* 
 * Function to add age and salary for the person with the given name 
 * Persons - Array of Person structures
 * cSearchName - Name of the person to search
 * numPersons - Number of persons in the array
 */
void add_age_salary(struct Person Persons[], char cSearchName[], int numPersons) {
	for (int iSearchCounter = 0; iSearchCounter < numPersons; iSearchCounter++) {
		/* Compare the searched name with the names in the array */
		if (!strcmp(cSearchName, Persons[iSearchCounter].cName)) {
			int iInputAge;     /* Variable to store input age */
			int iInputSalary;  /* Variable to store input salary */

			/* Prompt and input age and salary for the found person */
			printf("\n--> For '%s'\n", Persons[iSearchCounter].cName);
			printf("Enter Age: ");
			scanf("%d", &iInputAge);        /* Read age */
			printf("Enter Salary: ");
			scanf("%d", &iInputSalary);     /* Read salary */

			/* Store the input values in the corresponding structure */
			Persons[iSearchCounter].iAge = iInputAge;
			Persons[iSearchCounter].iSalary = iInputSalary;
			break;
		}
	}
}

/* 
 * Function to save the details of all persons to a file 
 * Persons - Array of Person structures
 */
void file_save(struct Person Persons[]) {
	/* Open the file in write mode */
	FILE *fptr = fopen("OutPut.txt", "a+"); 
	if (fptr == NULL) { 
		/* Check if the file could not be opened */
		printf("Could not open file"); 
		return; 
	}

	/* Loop through each person and save their details to the file */
	for (int iSaveCounter = 0; iSaveCounter < 3; iSaveCounter++) {
		fprintf(fptr, "%d %s %s %d %d\n", 
			(iSaveCounter+1), 
			Persons[iSaveCounter].cName, 
			Persons[iSaveCounter].cHomeTown, 
			Persons[iSaveCounter].iAge, 
			Persons[iSaveCounter].iSalary
		);
	}

	/* Close the file */
	fclose(fptr);
}


/*
*This program is given in ED8 SRA to complete some functions.
*Completed by Rushabh Goswami (164992)
*/

#include <stdio.h>
#include <string.h> /* needed for strcpy() and strcmp() */
#include <stdlib.h> /* needed for malloc(), free() */
#define STRLEN 64

/* Define the structure for a Node in the linked list */
typedef struct node {
    char name[STRLEN]; /* To store the string (name) */
    struct node *next; /* Pointer to the next node in the list */
} Node;

/* Function prototypes */
void showHelp(void);
void add(char *, Node **);
void removeElement(char *, Node **);
int isItem(char *, Node *);
int countItems(Node *);
void removeList(Node **);
void showList(Node *);
char * trim(char *);

int main(void) {
    char instruction[STRLEN]; /* Array to store user commands */
    Node *head = NULL; /* Pointer to the head of the linked list */
    char *pi; /* Pointer to the instruction */

    /* Initial prompt to the user */
    printf("Test program for a single-linked list.\n");
    printf("\nEnter an instruction (h = help)\n");
    printf("\n> ");
    
    /* Initialize the instruction array */
    memset(instruction, '\0', STRLEN);

    /* Get the user input */
    gets(instruction); /* Deprecated, but used here. Better to use fgets for safety. */
    
    /* Trim any leading spaces from the instruction */
    pi = trim(instruction);

    /* Loop until the user inputs 'q' to quit */
    while (*pi != 'q') {
        switch (*pi) {
            case 'i': 
                /* Add a new element to the list */
                add(trim(pi + 1), &head);
                break;
            case 'd': 
                /* Remove an element from the list */
                removeElement(trim(pi + 1), &head);
                break;
            case 'f': 
                /* Find if an element is in the list */
                if (isItem(trim(pi + 1), head))
                    printf("\"%s\" is in the list.\n", trim(pi+1));
                else
                    printf("\"%s\" is NOT in the list.\n", trim(pi+1));
                break;
            case 'l': 
                /* Show all items in the list */
                showList(head);
                break;
            case 'n': 
                /* Count and show the number of items in the list */
                printf("Number of list items: %d\n", countItems(head));
                break;
            case 'r': 
                /* Remove the entire list */
                removeList(&head);
                break;
            case 'h': 
                /* Show help menu */
                showHelp();
                break;
            case 'q': 
                /* Exit the loop and quit the program */
                break;
            default: 
                /* Handle unknown instructions */
                printf("Unknown instruction (h = help)\n");
        }
        
        /* Prompt for the next input */
        printf("\n> ");
        
        /* Clear the instruction array */
        memset(instruction, '\0', STRLEN);
        
        /* Get the next instruction */
        gets(instruction); /* Deprecated. For safety, use fgets */
        
        /* Trim leading spaces */
        pi = trim(instruction);
    }

    /* Clean up by removing the list before exiting */
    removeList(&head);
    return 0;
}

/* 
 * Function to show the help menu
 * Lists all available commands and their description
 */
void showHelp(void) {
    printf("i <string> : inserts the element in <string> alphabetically into the list\n");
    printf("d <string> : removes the element in <string> from the list\n");
    printf("f <string> : searches the list and returns if the string is in the list or not.\n");
    printf("l : shows the full list\n");
    printf("n : returns the number of items in the list\n");
    printf("r : removes the full list\n");
    printf("h : shows the help menu (this list).\n");
    printf("q : end of the program (first remove the list)\n");
}

/* 
 * Function to insert an item into the list in alphabetical order 
 * s = the string to add
 * head = the pointer to the head of the list
 */
void add(char *s, Node **head) {
    /* Create a new node and allocate memory for it */
    Node *newNode = (Node *)malloc(sizeof(Node));
    Node *current = *head, *previous = NULL;

    /* Copy the string into the new node */
    strcpy(newNode->name, s);
    newNode->next = NULL;

    /* Case 1: Insert at the beginning if the list is empty or the new node is smaller */
    if (*head == NULL || strcmp((*head)->name, s) > 0) {
        newNode->next = *head;
        *head = newNode;
    } else {
        /* Traverse the list to find the correct position to insert */
        while (current != NULL && strcmp(current->name, s) < 0) {
            previous = current;
            current = current->next;
        }
        /* Insert the new node at the correct position */
        newNode->next = current;
        previous->next = newNode;
    }
    printf("Inserted \"%s\" into the list.\n", s);
}

/* 
 * Function to remove an item from the list 
 * s = the string to remove
 * head = pointer to the head of the list
 */
void removeElement(char *s, Node **head) {
    Node *current = *head, *previous = NULL;

    /* Traverse the list to find the element */
    while (current != NULL && strcmp(current->name, s) != 0) {
        previous = current;
        current = current->next;
        

		/* If the element to be removed is the first node */
		if (previous == NULL) {
		    *head = current->next; /* Move the head to the next node */
		    return;
		} else {
		    previous->next = current->next; /* Bypass the current node */
    		free(current);
    		current = previous->next;
		}

    }
		        /* If the item is not found */
		if (current == NULL) {
		    printf("\"%s\" not found in the list.\n", s);
		    return;
		}

    /* Free the memory of the removed node */
    printf("\"%s\" removed from the list.\n", s);


}

/* 
 * Function to check if an item is in the list 
 * s = the string to search
 * head = pointer to the head of the list
 */
int isItem(char *s, Node *head) {
    Node *current = head;

    /* Traverse the list to find the item */
    while (current != NULL) {
        if (strcmp(current->name, s) == 0)
            return 1; /* Return 1 if the item is found */
        current = current->next;
    }

    /* Return 0 if the item is not found */
    return 0;
}

/* 
 * Function to count the number of items in the list 
 * head = pointer to the head of the list
 */
int countItems(Node *head) {
    int count = 0;
    Node *current = head;

    /* Traverse the list and count each node */
    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count; /* Return the number of items */
}

/* 
 * Function to remove the entire list and free allocated memory 
 * head = pointer to the head of the list
 */
void removeList(Node **head) {
    Node *current = *head;
    Node *nextNode;

    /* Traverse the list and free each node */
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    /* Set the head to NULL after clearing the list */
    *head = NULL;
    printf("List cleared.\n");
}

/* 
 * Function to display all items in the list 
 * head = pointer to the head of the list
 */
void showList(Node *head) {
    /* Check if the list is empty */
    if (head == NULL) {
        printf("The list is EMPTY\n");
    } else {
        /* Traverse and print each item in the list */
        printf("The list:\n");
        Node *current = head;
        while (current != NULL) {
            printf("%s ", current->name);
            current = current->next;
        }
        printf("\n\n");
    }
}

/* 
 * Function to trim leading spaces from a string 
 * s = the string to trim
 */
char * trim(char *s) {
    /* Move the pointer past leading spaces */
    while (*s == ' ') s++;
    return s;
}


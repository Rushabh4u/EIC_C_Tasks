/*
*This program is to search and print elements in strainght or reverse order in the linked list
*Created by Rushabh Goswami (164992)
*/

#include <stdio.h>
#include <stdlib.h>

/* Define a structure for the circular linked list node */
typedef struct node {
    int data;
    struct node *next;
} Node;

/* Function declarations */
void printReverse(Node *current, const Node *head);
void addElement(int data, Node **head);
void printList(Node *head);
void find(int x, Node *head);

int main() {
    Node *head = NULL;  /* Initialize head to NULL (empty list) */
    
    while (1) {
        int choice;
        printf("\n1. Add element to the linked list\n"
               "2. Print elements in reverse order\n"
               "3. Print elements in forward order\n"
               "4. Search element\n"
               "5. Exit the program\n\n"
               "Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int newElement;
                printf("Enter the element you want to insert: ");
                scanf("%d", &newElement);
                addElement(newElement, &head);  /* Add element to the list */
                break;
            }
            case 2: {
                printf("\nElements in reverse order:\n-----> ");
                if (head != NULL) {
                    printReverse(head->next, head);  /* Print in reverse order */
                    printf("%d ", head->data);  /* Print head at the end */
                } else {
                    printf("List is empty.\n");
                }
                break;
            }
            case 3: {
                printf("\nElements in forward order:\n-----> ");
                if (head != NULL) {
                    printList(head);  /* Print elements in forward order */
                } else {
                    printf("List is empty.\n");
                }
                break;
            }
            case 4: {
            int element;
                printf("\nEnter element you want to find:\n-----> ");
                scanf("%d", &element);
                
                if (head != NULL) {
                    find(element, head);  /* Search elements in in the list */
                } else {
                    printf("List is empty.\n");
                }
                break;
            }
            case 5: {
                printf("Exiting the program.\n");
                return 0;  /* Exit the program */
            }
            default: {
                printf("Invalid choice. Please enter a valid option.\n");
                break;
            }
        }
    }
    
    return 0;
}

/* Function to add a new element to the circular linked list */
void addElement(int data, Node **head) {
    /* Create a new node */
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    /* If the list is empty, make the new node point to itself */
    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head;
    } else {
        /* Traverse to the last node */
        Node *temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        /* Insert the new node at the end and link it to head */
        temp->next = newNode;
        newNode->next = *head;
    }
}

/* Function to print the elements of the circular linked list in forward order */
void printList(Node *head) {
    Node *temp = head;
    /* Traverse through the list and print each node's data */
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

/* Recursive function to print the elements in reverse order */
void printReverse(Node *current, const Node *head) {
    /* Base case: when the current node is the head again */
    if (current == head) {
        return;
    }
    /* Recursively move to the next node */
    printReverse(current->next, head);
    /* Print the current node's data after returning from recursion */
    printf("%d ", current->data);
}

/* Function to search the element in the circular linked list */
void find(int x, Node *head) {
    Node *temp = head;
    int count = 0;
    /* Traverse through the list and compare each node's data */
    while (temp -> data != x){
    	count++;
    	if (temp->next == head){
    		printf("\nElement is not present in the list\n"); 
    		return;
    	}
    	temp = temp->next;
    	}
    printf("element is present at position %d", count+1);
    return;
}


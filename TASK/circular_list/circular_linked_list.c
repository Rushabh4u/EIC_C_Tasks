#include <stdio.h>
#include <stdlib.h>
#include "circular_linked_list.h"

/* Creates a new node with the given data */
Node* createNode(int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) {
		/* Handle memory allocation failure */
		printf("Memory allocation failed\n");
		exit(1);
	}
	newNode->data = data;
	newNode->next = newNode; /* For a circular list, next points to itself initially */
	return newNode;
}

/* Inserts a new node at the beginning of the circular linked list */
void insertAtBeginning(Node** head, int data) {
	Node* newNode = createNode(data);
	if (*head == NULL) {
		*head = newNode;
		newNode->next = *head;
		return;
	}

	/* Find the last node to link the new node correctly */
	Node* temp = *head;
	while (temp->next != *head) {
		temp = temp->next;
	}
	
	temp->next = newNode;
	newNode->next = *head;
	*head = newNode;
}

/* Inserts a new node at the end of the circular linked list */
void insertAtEnd(Node** head, int data) {
	Node* newNode = createNode(data);
	if (*head == NULL) {
		*head = newNode;
		newNode->next = *head;
		return;
	}

	/* Traverse to the last node */
	Node* temp = *head;
	while (temp->next != *head) {
		temp = temp->next;
	}

	temp->next = newNode;
	newNode->next = *head;
}

/* Deletes the first occurrence of a node with the given data */
void deleteNode(Node** head, int data) {
	if (*head == NULL) {
		printf("List is empty, nothing to delete\n");
		return;
	}

	Node* current = *head;
	Node* previous = NULL;

	/* Special case if the node to be deleted is the head */
	do {
		if (current->data == data) {
			if (previous != NULL) {
				previous->next = current->next;
			} else {
				/* Adjust the last node's next pointer if the head is being deleted */
				Node* temp = *head;
				while (temp->next != *head) {
					temp = temp->next;
				}
				temp->next = current->next;
				*head = current->next;
			}
			free(current);
			return;
		}
		previous = current;
		current = current->next;
	} while (current != *head);

	printf("Node with data %d not found\n", data);
}

/* Displays the contents of the circular linked list */
void display(Node* head) {
	if (head == NULL) {
		printf("List is empty\n");
		return;
	}

	Node* current = head;
	while (current->next != head){
		printf("%d -> ", current->data);
		current = current->next;
	}
	printf("%d -> NULL", current->data);
	printf("\n");
}

/* Returns the sum of all even numbers in the circular linked list */
int sumEven(Node* head) {
	if (head == NULL) {
		return 0;
	}

	int sum = 0;
	Node* current = head;
	do {
		if (current->data % 2 == 0) {
			sum += current->data;
		}
		current = current->next;
	} while (current != head);

	return sum;
}


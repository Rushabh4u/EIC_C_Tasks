#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

/* Adds a new node at the end of the doubly linked list */
Node* d_append(Node **head, int num) {
	Node *new_node, *temp;
	new_node = (Node*)malloc(sizeof(Node));

	/* Check if memory allocation was successful */
	if (!new_node) {
		printf("Memory allocation failed\n");
		return NULL;
	}
	
	new_node->data = num;
	new_node->next = NULL;

	/* If the list is empty, make the new node the head */
	if (*head == NULL) {
		new_node->prev = NULL;
		*head = new_node;
		return *head;
	}

	/* Traverse to the end of the list */
	temp = *head;
	while (temp->next != NULL) {
		temp = temp->next;
	}

	temp->next = new_node;
	new_node->prev = temp;

	return *head;
}

/* Adds a new node at the beginning of the doubly linked list */
Node* d_addatbeg(Node **head, int num) {
	Node *new_node = (Node*)malloc(sizeof(Node));

	/* Check if memory allocation was successful */
	if (!new_node) {
		printf("Memory allocation failed\n");
		return NULL;
	}
	
	new_node->data = num;
	new_node->prev = NULL;
	new_node->next = *head;

	/* Update the previous head's previous pointer */
	if (*head != NULL) {
		(*head)->prev = new_node;
	}

	*head = new_node;

	return *head;
}

/* Adds a new node after the specified number of nodes */
void d_addafter(Node **q, int loc, int num) {
	Node *new_node;
	int i;
	Node *temp = *q;
	/* Traverse to the specified location */
	for (i = 0; i < loc && temp != NULL; i++) {
		temp = temp->next;
	}

	/* If location exceeds list size, return */
	if (temp == NULL) {
		printf("Location exceeds list size\n");
		return;
	}

	new_node = (Node*)malloc(sizeof(Node));
	
	/* Check if memory allocation was successful */
	if (!new_node) {
		printf("Memory allocation failed\n");
		return;
	}
	
	new_node->data = num;
	new_node->next = temp->next;
	new_node->prev = temp;

	/* Adjust pointers */
	if (temp->next != NULL) {
		temp->next->prev = new_node;
	}
	
	temp->next = new_node;
}

/* Displays the contents of the linked list */
void d_display(Node **q) {
	/* Check if list is empty */
	if (*q == NULL){
		printf("List is empty!\n");
		return;
	}
	
	/* Traverse the list and print each element */
	Node *temp = *q;
	while (temp->next != NULL) {
		printf("%d -> ", temp->data);
		temp = temp->next;
	}
	printf("%d -> NULL", temp->data);
	printf("\n");
}

/* Counts the number of nodes present in the linked list */
int d_count(Node **q) {
	int count = 0;
	Node *temp = *q;

	/* Traverse the list and count each node */
	while (temp != NULL) {
		count++;
		temp = temp->next;
	}

	return count;
}

/* Deletes the specified node from the doubly linked list */
void d_delete(Node **s, int num) {
	Node *temp = *s;

	/* Traverse the list to find the node to delete */
	while (temp != NULL && temp->data != num) {
		temp = temp->next;
	}

	/* If the node is not found, return */
	if (temp == NULL) {
		printf("Node not found\n");
		return;
	}

	/* Adjust pointers and free memory */
	if (temp->prev != NULL) {
		temp->prev->next = temp->next;
	} else {
		*s = temp->next;
	}

	if (temp->next != NULL) {
		temp->next->prev = temp->prev;
	}

	free(temp);
}


#include <stdio.h>
#include <stdlib.h>
#include "circular_linked_list.h"

int main() {
	Node* head = NULL;
	int choice, data;

	/* Menu-driven interface */
	while (1) {
		printf("\nMenu:\n");
		printf("1. Insert at Beginning\n");
		printf("2. Insert at End\n");
		printf("3. Delete Node\n");
		printf("4. Display List\n");
		printf("5. Sum of Even Numbers\n");
		printf("6. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				printf("Enter number to insert at beginning: ");
				scanf("%d", &data);
				insertAtBeginning(&head, data);
				break;
			case 2:
				printf("Enter number to insert at end: ");
				scanf("%d", &data);
				insertAtEnd(&head, data);
				break;
			case 3:
				printf("Enter number to delete: ");
				scanf("%d", &data);
				deleteNode(&head, data);
				break;
			case 4:
				printf("Circular Linked List: ");
				display(head);
				break;
			case 5:
				printf("Sum of all even numbers: %d\n", sumEven(head));
				break;
			case 6:
				exit(0);
			default:
				printf("Invalid choice! Please try again.\n");
		}
	}

	return 0;
}


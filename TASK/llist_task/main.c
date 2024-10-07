#include "llistV1.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Node *head = NULL;
    int choice, value, position;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert at beginning\n");
        printf("2. Insert at end\n");
        printf("3. Insert at position\n");
        printf("4. Delete last node\n");
        printf("5. Reverse list\n");
        printf("6. Print list\n");
        printf("7. Print list in reverse\n");
        printf("8. Count occurrences of an element\n");
        printf("9. Get nth element\n");
        printf("10. Search for an element\n");
        printf("11. Pop (remove first element)\n");
        printf("12. Remove from position\n");
        printf("13. Delete entire list\n");
        printf("0. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                Push(&head, value);
                break;

            case 2:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                InsertAtEnd(&head, value);
                break;

            case 3:
                printf("Enter position and value to insert: ");
                scanf("%d %d", &position, &value);
                InsertAtPosition(&head, position, value);
                break;

            case 4:
                RemoveLast(&head);
                break;

            case 5:
                head = ReverseList(&head);
                break;

            case 6:
                PrintList(&head);
                break;

            case 7:
                PrintReverse(&head);
                printf("NULL\n");
                break;

            case 8:
                printf("Enter value to count occurrences: ");
                scanf("%d", &value);
                printf("Occurrences of %d: %d\n", value, CountOccurrence(&head, value));
                break;

            case 9:
                printf("Enter position: ");
                scanf("%d", &position);
                value = GetNthElement(&head, position);
                if (value != -1) {
                    printf("Element at position %d: %d\n", position, value);
                }
                break;

            case 10:
                printf("Enter value to search: ");
                scanf("%d", &value);
                position = SearchElement(&head, value);
                if (position != -1) {
                    printf("Element found at position %d\n", position);
                } else {
                    printf("Element not found\n");
                }
                break;

            case 11:
                value = Pop(&head);
                if (value != -1) {
                    printf("Popped value: %d\n", value);
                }
                break;

            case 12:
                printf("Enter position to remove: ");
                scanf("%d", &position);
                RemoveFromPosition(&head, position);
                break;

            case 13:
                DeleteList(&head);
                break;

            case 0:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice, try again.\n");
        }
    }

    return 0;
}


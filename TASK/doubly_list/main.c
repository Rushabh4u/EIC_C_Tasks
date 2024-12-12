#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

int main() {
    Node *head = NULL;
    int choice, num, loc;

    /* Menu-driven interface */
    while (1) {
        printf("\nMenu:\n");
        printf("1. Append\n");
        printf("2. Add at Beginning\n");
        printf("3. Add After\n");
        printf("4. Display\n");
        printf("5. Count\n");
        printf("6. Delete\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter number to append: ");
                scanf("%d", &num);
                d_append(&head, num);
                break;
            case 2:
                printf("Enter number to add at beginning: ");
                scanf("%d", &num);
                d_addatbeg(&head, num);
                break;
            case 3:
                printf("Enter location after which to add: ");
                scanf("%d", &loc);
                printf("Enter number to add: ");
                scanf("%d", &num);
                d_addafter(&head, loc, num);
                break;
            case 4:
                printf("Doubly Linked List: ");
                d_display(&head);
                break;
            case 5:
                printf("Number of nodes: %d\n", d_count(&head));
                break;
            case 6:
                printf("Enter number to delete: ");
                scanf("%d", &num);
                d_delete(&head, num);
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}


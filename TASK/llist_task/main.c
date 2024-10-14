/*

#include "llistV1.h"

int main() {
    Node* head = NULL;
    Node* anotherList = NULL;
    int choice, value, position;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Push\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Position\n");
        printf("4. Remove Last\n");
        printf("5. Print List\n");
        printf("6. Reverse List\n");
        printf("7. Print Reverse\n");
        printf("8. Count Occurrences\n");
        printf("9. Get Nth Element\n");
        printf("10. Search Element\n");
        printf("11. Pop\n");
        printf("12. Remove from Position\n");
        printf("13. Delete List\n");
        printf("14. Sorted Insert\n");
        printf("15. Insert Sort\n");
        printf("16. Append Lists\n");
        printf("17. Remove Duplicates\n");
        printf("18. Move Node\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                Push(&head, value);
                break;

            case 2:
                printf("Enter value to insert at end: ");
                scanf("%d", &value);
                InsertAtEnd(&head, value);
                break;

            case 3:
                printf("Enter position and value: ");
                scanf("%d %d", &position, &value);
                InsertAtPosition(&head, position, value);
                break;

            case 4:
                RemoveLast(&head);
                break;

            case 5:
                PrintList(&head);
                break;

            case 6:
                head = ReverseList(&head);
                PrintList(&head);
                break;

            case 7:
                PrintReverse(&head);
                break;

            case 8:
                printf("Enter value to count: ");
                scanf("%d", &value);
                printf("Occurrences: %d\n", CountOccurrences(head, value));
                break;

            case 9:
                printf("Enter position: ");
                scanf("%d", &position);
                printf("Nth element: %d\n", GetNth(head, position));
                break;

            case 10:
                printf("Enter value to search: ");
                scanf("%d", &value);
                position = Search(head, value);
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

            case 14:
                printf("Enter value for sorted insert: ");
                scanf("%d", &value);
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->data = value;
                newNode->next = NULL;
                SortedInsert(&head, newNode);
                break;

            case 15:
                InsertSort(&head);
                break;

            case 16:
                printf("Appending another list to the main list.\n");
                Append(&head, &anotherList);
                break;

            case 17:
                RemoveDuplicates(head);
                break;

            case 18:
                printf("Moving a node from another list to the main list.\n");
                MoveNode(&head, &anotherList);
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

*/

#include "llistV1.h"

int main() {
    Node* head = NULL;
    Node* anotherList = NULL;
    int choice, value, position;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Push\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Position\n");
        printf("4. Remove Last\n");
        printf("5. Print List\n");
        printf("6. Reverse List\n");
        printf("7. Print Reverse\n");
        printf("8. Count Occurrences\n");
        printf("9. Get Nth Element\n");
        printf("10. Search Element\n");
        printf("11. Pop\n");
        printf("12. Remove from Position\n");
        printf("13. Delete List\n");
        printf("14. Sorted Insert\n");
        printf("15. Insert Sort\n");
        printf("16. Append Lists\n");
        printf("17. Remove Duplicates\n");
        printf("18. Move Node\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                Push(&head, value);
                break;

            case 2:
                printf("Enter value to insert at end: ");
                scanf("%d", &value);
                InsertAtEnd(&head, value);
                break;

            case 3:
                printf("Enter position and value: ");
                scanf("%d %d", &position, &value);
                InsertAtPosition(&head, position, value);
                break;

            case 4:
                RemoveLast(&head);
                break;

            case 5:
                PrintList(head);
                break;

            case 6:
                head = ReverseList(head);
                PrintList(head);
                break;

            case 7:
                PrintReverse(head);
                break;

            case 8:
                printf("Enter value to count: ");
                scanf("%d", &value);
                printf("Occurrences: %d\n", CountOccurrences(head, value));
                break;

            case 9:
                printf("Enter position: ");
                scanf("%d", &position);
                printf("Nth element: %d\n", GetNth(head, position));
                break;

            case 10:
                printf("Enter value to search: ");
                scanf("%d", &value);
                position = Search(head, value);
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

            case 14:
                printf("Enter value for sorted insert: ");
                scanf("%d", &value);
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->data = value;
                newNode->next = NULL;
                SortedInsert(&head, newNode);
                break;

            case 15:
                InsertSort(&head);
                break;

            case 16:
                printf("Appending another list to the main list.\n");
                Append(&head, &anotherList);
                break;

            case 17:
                RemoveDuplicates(head);
                break;

            case 18:
                printf("Moving a node from another list to the main list.\n");
                MoveNode(&head, &anotherList);
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



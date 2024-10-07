#include "llistV1.h"
#include <stdio.h>
#include <stdlib.h>

int CountNodes(Node **head) {
    if (!*head) {
        return 0;
    }

    Node *temp = *head;
    int count = 0;

    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

void Push(Node **head, int x) {
    Node *new;
    new = (Node *)malloc(sizeof(Node));
    new->data = x;
    new->next = NULL;

    if (!*head) {
        *head = new;
        return;
    }
    new->next = *head;
    *head = new;
    return;
}

void InsertAtEnd(Node **head, int x) {
    Node *new;
    new = (Node *)malloc(sizeof(Node));
    new->data = x;
    new->next = NULL;

    if (!*head) {
        *head = new;
        return;
    }

    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new;
    return;
}

void InsertAtPosition(Node **head, int pos, int x) {
    if (pos - 1 > CountNodes(head) || pos <= 0) {
        printf("Position out of bound!!!\n");
        return;
    }

    Node *temp = *head;
    int count = 1;

    while (count < pos - 1) {
        temp = temp->next;
        count++;
    }

    Node *new = (Node *)malloc(sizeof(Node));
    new->data = x;

    if (*head == NULL && pos == 1) {
        *head = new;
        return;
    }

    new->next = temp->next;
    temp->next = new;
}

void RemoveLast(Node **head) {
    if (!*head) {
        printf("List is empty!!!\n");
        return;
    }

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    Node *temp = *head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }

    free(temp->next);
    temp->next = NULL;
}

Node* ReverseList(Node **head) {
    if (!*head)
        return NULL;

    Node *prev = NULL;
    Node *current = *head;
    Node *next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
    return *head;
}

void PrintReverse(Node **head) {
    if (!*head) {
        return;
    }

    PrintReverse(&((*head)->next));
    printf("%d -> ", (*head)->data);
}

void PrintList(Node **head) {
    if (!*head) {
        printf("Empty list\n");
        return;
    }

    Node *temp = *head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int CountOccurrence(Node **head, int key) {
    Node *temp = *head;
    int count = 0;

    while (temp != NULL) {
        if (temp->data == key) {
            count++;
        }
        temp = temp->next;
    }
    return count;
}

void DeleteList(Node **head) {
    Node *temp = *head;
    Node *next;

    while (temp != NULL) {
        next = temp->next;
        free(temp);
        temp = next;
    }
    *head = NULL;
}

int GetNthElement(Node **head, int index) {
    if (index <= 0) {
        printf("Invalid index\n");
        return -1;
    }

    Node *temp = *head;
    int count = 1;

    while (temp != NULL && count < index) {
        temp = temp->next;
        count++;
    }

    if (temp == NULL) {
        printf("Index out of bounds\n");
        return -1;
    }
    return temp->data;
}

int SearchElement(Node **head, int key) {
    Node *temp = *head;
    int position = 1;

    while (temp != NULL) {
        if (temp->data == key) {
            return position;
        }
        temp = temp->next;
        position++;
    }
    return -1;  // Element not found
}

int Pop(Node **head) {
    if (!*head) {
        printf("List is empty\n");
        return -1;
    }

    Node *temp = *head;
    int data = temp->data;

    *head = (*head)->next;
    free(temp);
    return data;
}

void RemoveFromPosition(Node **head, int pos) {
    if (!*head || pos <= 0) {
        printf("Invalid position\n");
        return;
    }

    Node *temp = *head;

    if (pos == 1) {
        *head = (*head)->next;
        free(temp);
        return;
    }

    for (int i = 1; temp != NULL && i < pos - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Position out of bounds\n");
        return;
    }

    Node *next = temp->next->next;
    free(temp->next);
    temp->next = next;
}


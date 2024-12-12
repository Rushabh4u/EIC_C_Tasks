#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

/* Structure definition for a circular linked list node */
typedef struct Node {
    int data;
    struct Node* next;
} Node;

/* Function prototypes */
Node* createNode(int data);
void insertAtBeginning(Node** head, int data);
void insertAtEnd(Node** head, int data);
void deleteNode(Node** head, int data);
void display(Node* head);
int sumEven(Node* head);

#endif


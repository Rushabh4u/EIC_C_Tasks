#ifndef LLISTV1_H
#define LLISTV1_H

// Define the node structure
struct node {
    int data;
    struct node *next;
};
typedef struct node Node;

// Function declarations
int CountNodes(Node **head);
void Push(Node **head, int x);
void InsertAtEnd(Node **head, int x);
void InsertAtPosition(Node **head, int pos, int x);
void RemoveLast(Node **head);
Node* ReverseList(Node **head);
void PrintReverse(Node **head);
void PrintList(Node **head);
int CountOccurrence(Node **head, int key);
void DeleteList(Node **head);
int GetNthElement(Node **head, int index);
int SearchElement(Node **head, int key);
int Pop(Node **head);
void RemoveFromPosition(Node **head, int pos);

#endif


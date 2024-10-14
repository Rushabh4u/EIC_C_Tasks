/*
#ifndef LLISTV1_H
#define LLISTV1_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

// Function declarations
int CountNodes(Node** head);
void Push(Node** head, int x);
void InsertAtEnd(Node** head, int x);
void InsertAtPosition(Node** head, int pos, int x);
void RemoveLast(Node** head);
Node* ReverseList(Node** head);
void PrintReverse(Node** head);
void PrintList(Node** head);
int CountOccurrences(Node* head, int x);
void DeleteList(Node** head);
int GetNth(Node* head, int n);
int Search(Node* head, int x);
int Pop(Node** head);
void RemoveFromPosition(Node** head, int pos);

// New functions
void SortedInsert(Node** headRef, Node* newNode);
void InsertSort(Node** headRef);
void Append(Node** aRef, Node** bRef);
void RemoveDuplicates(Node* head);
void MoveNode(Node** destRef, Node** sourceRef);

#endif

*/


#ifndef LLISTV1_H
#define LLISTV1_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

// Function declarations
int CountNodes(Node* head);
void Push(Node** head, int x);
void InsertAtEnd(Node** head, int x);
void InsertAtPosition(Node** head, int pos, int x);
void RemoveLast(Node** head);
Node* ReverseList(Node* head);
void PrintReverse(Node* head);
void PrintList(Node* head);
int CountOccurrences(Node* head, int x);
void DeleteList(Node** head);
int GetNth(Node* head, int n);
int Search(Node* head, int x);
int Pop(Node** head);
void RemoveFromPosition(Node** head, int pos);

// New functions
void SortedInsert(Node** headRef, Node* newNode);
void InsertSort(Node** headRef);
void Append(Node** aRef, Node** bRef);
void RemoveDuplicates(Node* head);
void MoveNode(Node** destRef, Node** sourceRef);

#endif


#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

/* Structure definition for a doubly linked list node */
typedef struct dnode {
    struct dnode *prev;
    int data;
    struct dnode *next;
} Node;

/* Function prototypes */
Node* d_append(Node **head, int num);
Node* d_addatbeg(Node **head, int num);
void d_addafter(Node **q, int loc, int num);
void d_display(Node **q);
int d_count(Node **q);
void d_delete(Node **s, int num);

#endif


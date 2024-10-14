/*
#include "llistV1.h"

// Definitions for old functions...
// CountNodes, Push, InsertAtEnd, InsertAtPosition, RemoveLast, ReverseList, 
// PrintReverse, PrintList, CountOccurrences, DeleteList, GetNth, Search, 
// Pop, RemoveFromPosition


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


// New function implementations

void SortedInsert(Node** headRef, Node* newNode) {
    Node* current;
    if (*headRef == NULL || (*headRef)->data >= newNode->data) {
        newNode->next = *headRef;
        *headRef = newNode;
    } else {
        current = *headRef;
        while (current->next != NULL && current->next->data < newNode->data) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void InsertSort(Node** headRef) {
    Node* sorted = NULL;
    Node* current = *headRef;
    while (current != NULL) {
        Node* next = current->next;
        SortedInsert(&sorted, current);
        current = next;
    }
    *headRef = sorted;
}

void Append(Node** aRef, Node** bRef) {
    if (*aRef == NULL) {
        *aRef = *bRef;
    } else {
        Node* current = *aRef;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = *bRef;
    }
    *bRef = NULL;
}

void RemoveDuplicates(Node* head) {
    if (head == NULL) return;
    Node* current = head;
    while (current->next != NULL) {
        if (current->data == current->next->data) {
            Node* nextNext = current->next->next;
            free(current->next);
            current->next = nextNext;
        } else {
            current = current->next;
        }
    }
}

void MoveNode(Node** destRef, Node** sourceRef) {
    if (*sourceRef == NULL) {
        printf("Source list is empty!\n");
        return;
    }
    Node* newNode = *sourceRef;
    *sourceRef = newNode->next;
    newNode->next = *destRef;
    *destRef = newNode;
}
*/


#include "llistV1.h"

// Count number of nodes in the list
int CountNodes(Node* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

// Push a new node onto the head of the list
void Push(Node** head, int x) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = x;
    newNode->next = *head;
    *head = newNode;
}

// Insert node at the end of the list
void InsertAtEnd(Node** head, int x) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = x;
    newNode->next = NULL;
    
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Insert node at a specific position in the list
void InsertAtPosition(Node** head, int pos, int x) {
    if (pos < 1 || pos > CountNodes(*head) + 1) {
        printf("Position out of bounds!\n");
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = x;

    if (pos == 1) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node* temp = *head;
    for (int i = 1; i < pos - 1; i++) {
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

// Remove the last node from the list
void RemoveLast(Node** head) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    Node* temp = *head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }

    free(temp->next);
    temp->next = NULL;
}

// Reverse the linked list
Node* ReverseList(Node* head) {
    Node* prev = NULL;
    Node* current = head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

// Print the list in reverse order using recursion
void PrintReverse(Node* head) {
    if (head == NULL) {
        return;
    }
    PrintReverse(head->next);
    printf("%d ", head->data);
}

// Print the list
void PrintList(Node* head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }

    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Count occurrences of a given value in the list
int CountOccurrences(Node* head, int x) {
    int count = 0;
    while (head != NULL) {
        if (head->data == x) {
            count++;
        }
        head = head->next;
    }
    return count;
}

// Delete the entire list
void DeleteList(Node** head) {
    Node* current = *head;
    Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

// Get the nth element in the list
int GetNth(Node* head, int n) {
    int count = 1;
    while (head != NULL) {
        if (count == n) {
            return head->data;
        }
        count++;
        head = head->next;
    }
    return -1;
}

// Search for an element in the list and return its position
int Search(Node* head, int x) {
    int position = 1;
    while (head != NULL) {
        if (head->data == x) {
            return position;
        }
        position++;
        head = head->next;
    }
    return -1;
}

// Pop (remove and return the first element)
int Pop(Node** head) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return -1;
    }

    Node* temp = *head;
    int value = temp->data;
    *head = (*head)->next;
    free(temp);
    return value;
}

// Remove a node from a specific position
void RemoveFromPosition(Node** head, int pos) {
    if (*head == NULL || pos < 1 || pos > CountNodes(*head)) {
        printf("Position out of bounds!\n");
        return;
    }

    Node* temp = *head;

    if (pos == 1) {
        *head = temp->next;
        free(temp);
        return;
    }

    for (int i = 1; i < pos - 1; i++) {
        temp = temp->next;
    }

    Node* next = temp->next->next;
    free(temp->next);
    temp->next = next;
}

// New function implementations

void SortedInsert(Node** headRef, Node* newNode) {
    Node* current;
    if (*headRef == NULL || (*headRef)->data >= newNode->data) {
        newNode->next = *headRef;
        *headRef = newNode;
    } else {
        current = *headRef;
        while (current->next != NULL && current->next->data < newNode->data) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void InsertSort(Node** headRef) {
    Node* sorted = NULL;
    Node* current = *headRef;
    while (current != NULL) {
        Node* next = current->next;
        SortedInsert(&sorted, current);
        current = next;
    }
    *headRef = sorted;
}

void Append(Node** aRef, Node** bRef) {
    if (*aRef == NULL) {
        *aRef = *bRef;
    } else {
        Node* current = *aRef;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = *bRef;
    }
    *bRef = NULL;
}

void RemoveDuplicates(Node* head) {
    if (head == NULL) return;
    Node* current = head;
    while (current->next != NULL) {
        if (current->data == current->next->data) {
            Node* nextNext = current->next->next;
            free(current->next);
            current->next = nextNext;
        } else {
            current = current->next;
        }
    }
}

void MoveNode(Node** destRef, Node** sourceRef) {
    if (*sourceRef == NULL) {
        printf("Source list is empty!\n");
        return;
    }
    Node* newNode = *sourceRef;
    *sourceRef = newNode->next;
    newNode->next = *destRef;
    *destRef = newNode;
}


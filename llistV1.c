#include"llistV1.h"
#include<stdlib.h>

struct node{
	int data;
	Node *next;
}Node;

void InsertAtFront(Node *head, int x){
	Node *new;
	new = (Node *)malloc(sizeof(Node));
	new->data = x;
	new->next = NULL;
	
	if(!head){
		head = new;
		return;
	}
	new->next = head;
	head = new;
	return;
}

void InsertAtEnd(Node *head, int x){
	Node *new;
	new = (Node *)malloc(sizeof(Node));
	new->data = x;
	new->next = NULL;
	
	if(!head){
		head = new;
		return;
	}
	
	Node *temp = head;
	
	while(temp->next == NULL){
		temp = temp->next;
	}
	temp->next = new;
	return;
}

void InsertAtPosition(Node *head, int pos, int x){
	
}

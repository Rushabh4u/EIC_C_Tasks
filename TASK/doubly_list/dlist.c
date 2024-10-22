#include<stdio.h>
#include<stdlib.h>

struct dnode{

      struct dnode *prev;

      int data;

      struct dnode  *next;

      }Node;


/*adds a new node at the end of the doubly linked list*/

Node *d_append(struct dnode **head, int num){
	Node *new = (Node *)malloc(sizeof(Node *));
	new->data = num;
	new->prev = NULL;
	new->
	
	if (*head == NULL){
		*head = new;
		return *head;
	}
	
	Node *temp = *head;
	
}

 

/*adds a new node at the beginning of the doubly linked list*/


d_addatbeg(struct dnode **s, int num)

 

/*adds a new node after the specified number of nodes*/
 

d_addafter(struct dnode *q, int loc, int num) //loc is not equal to 0

 

/*displays the contents of the linked list*/
 

d_display (struct dnode *q)

 

/*counts the number of nodes present in the linked list*/
 

d_count (struct dnode *q)

 

/*deletes the specified node from the doubly linked list*/
 

d_delete(struct dnode **s, int num)

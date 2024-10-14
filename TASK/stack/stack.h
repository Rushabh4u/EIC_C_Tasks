#ifndef STACK_H
#define STACK_H

bool is_empty();
bool is_full();
void push(int s[], int data);
void pop(int s[]);
void clear(int s[]);
int top(int s[]);
int top_and_pop(int s[]);

#endif

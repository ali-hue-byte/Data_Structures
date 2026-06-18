#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>

struct Node{
    int value;
    struct Node *next;
};

typedef struct  Node  Node;

typedef struct {
    Node *top;
} Stack;

bool stack_is_empty(Stack *stack);
void stack_push(Stack *stack, int i);
int stack_pop(Stack *stack);
int stack_size(Stack *stack);
int stack_peek(Stack *stack);
void print_stack(Stack *stack);
void empty_stack(Stack *stack);
Stack create_stack();

#endif

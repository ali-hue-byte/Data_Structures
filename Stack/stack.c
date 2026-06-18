/* This file provides necessary functions to implement a Stack using a linked list
   Possible operations for stack :
   - push: Add an element to its top
   - pop: Remove the last added element
*/

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "stack.h"

// Creates a new stack
Stack create_stack(){
    Stack stack;
    stack.top = NULL;
    return stack;

}

// Checks if the stack is empty
bool stack_is_empty(Stack *stack){
    
    return stack->top == NULL; // If top is NULL the stack is empty
    
}

// Adds a new value to the stack
void stack_push(Stack *stack, int i){
    Node *newN = malloc(sizeof(Node)); // Creates a new Node
    newN->value = i;
    newN->next = stack->top;
    stack->top = newN; // New Node becomes top of the stack
    stack->size++;
}

// Returns and removes the last added value to the stack 
// (Last In First Out)
int stack_pop(Stack *stack){
    if (stack_is_empty(stack)){
        printf("Stack is empty ");
        return 0;
    }else{
        int nb = stack->top->value; // Last pushed value
        Node *old = stack->top;
        stack->top = stack->top->next; // Changes top 
        stack->size--;
        free(old); // Frees memory allocated for the previous top
        return nb;
    }
    
}

// Returns the last added value to the stack (without removing it)
int stack_peek(Stack *stack){
    if (stack_is_empty(stack)){
        printf("Stack is empty ");
        return -1;
    }else{
        int nb = stack->top->value; // Last pushed value
        return nb;
    }
}

// Prints the stack
void print_stack(Stack *stack){
    
    Node *now = stack->top;
    while (now != NULL){
        printf("%d ", now->value); // Prints current value
        now = now->next; // Moves to the next Node
    };
    
    
}

// Removes all the values from the stack
void empty_stack(Stack *stack){
    Node *now = stack->top;
    while (now != NULL){
        now = now->next;
        free(stack->top); // Frees memory of the current top
        stack->top = now; // Changes top to the next Node
        stack->size = 0;
    };
}

// Returns the number of elements in the stack
int stack_size(Stack *stack) {
    return stack->size;
}



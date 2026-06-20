# Stack

## Description 

A stack is a data structure that follows Last in First out (LIFO) principle, meaning the last added element is the first one removed. In this implementation it is built as a linked list, where each new value is added at the front.

---
## How it works 

### Structure
Internally, the stack is implemented as a linked list, where each element (Node) holds a value, and a pointer to the next node below it.
The stack only operates with the top - a pointer to the most recently added node.

### Push
When a new value is pushed, a new node is created, its next pointer is set to point to the current top, and then it becomes the new top.
This means the newest element is always added to the front of the linked list, which makes removing it as fast as adding it.

### Pop & Peek
When a value is popped, the top's value is saved, the top pointer is moved to point to the next node in the chain, and the old top is freed from memory. 
If the stack is empty (top == NULL), there is nothing to pop or peek at.

---
## Operations

| Function | Description | Time complexity |
|----------|-------------|-----------------|
| create_stack() | Creates a new stack. | O(1) |
| stack_is_empty(Stack *stack) | Checks if the stack is empty (top == NULL). | O(1) |
| stack_push(Stack *stack, int i) | Adds a new value to the stack by creating a new node and setting it as the new top of the stack. | O(1) |
| stack_pop(Stack *stack) | Returns and removes the top value of the stack by saving its value, updating the top pointer to the next node, and freeing the old top node. | O(1) |
| stack_peek(Stack *stack) | Returns the last added value to the stack, without removing it. | O(1) |
| print_stack(Stack *stack) | Prints the stack. | O(n) |
| empty_stack(Stack *stack) | Removes all the values from the stack. | O(n) |
| stack_size(Stack *stack) | Returns the number of elements in the stack. | O(1) |

---
## Example 

```c

#include "stack.h"
#include <stdio.h>

int main(){
    Stack stack = create_stack();

    stack_push(&stack, 10);
    stack_push(&stack, 20);
    stack_push(&stack, 30);

    print_stack(&stack); // 30 20 10
    printf("\n");

    printf("Top: %d\n", stack_peek(&stack)); // 30

    printf("Popped: %d\n", stack_pop(&stack)); // 30
    print_stack(&stack); // 20 10
    printf("\n");

    printf("Size: %d\n", stack_size(&stack)); // 2

    empty_stack(&stack);
    printf("Empty: %d\n", stack_is_empty(&stack)) ? "yes" : "no"; // yes

    return 0;
}

```

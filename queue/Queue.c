// This file provides necessary functions to implement a Queue using two stacks
// Possible operations for Queue :
// Add an element to its rear
// Remove an element from the front 

// With two stacks it is possible to make a Queue, using one stack
// to add elements, and the second one to remove the first added element.

// This can be simulated by moving the elements from stack 1 to stack 2,
// using pop function of the Stack. This reverses the order of the elements,
// allowing the oldest element to be removed first.

# include "../stack/stack.h"
# include "Queue.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>



// Adds an element to the queue
// Uses stack 1 to store elements
void enqueue(Queue *queue, int i){
    stack_push(queue->Stack1, i); // Stores elements in first stack
}

// Removes and returns oldest element of the Queue, using stack 2
int dequeue(Queue *queue) { 
    
    if (queue_is_empty(queue)){
        printf("Queue is empty");
        return 0;
    }
    else {
        
        while(!stack_is_empty(queue->Stack1)){
            // Moves elements from stack 1 to stack 2, from the 
            // last added element to the oldest one.
            stack_push(queue->Stack2, stack_pop(queue->Stack1)); 
        };
        int nb = stack_pop(queue->Stack2);
        while(!stack_is_empty(queue->Stack2)){
            // Removes elements to stack 1
            stack_push(queue->Stack1, stack_pop(queue->Stack2)); 
        };
        return nb;
    }
}

// Returns the oldest element without removing it
int queue_peek(Queue *queue){
    if (queue_is_empty(queue)){
        printf("Queue is empty");
        return 0;
    }
    else {
        while(!stack_is_empty(queue->Stack1)){
            // Moves elements from stack 1 to stack 2, from the 
            // last added element to the oldest one.
            stack_push(queue->Stack2, stack_pop(queue->Stack1)); 
        };
        int nb = queue->Stack2->top->value;
        while(!stack_is_empty(queue->Stack2)){
            // Removes elements to stack 1
            stack_push(queue->Stack1, stack_pop(queue->Stack2)); 
        };
        return nb;
    }
}

// Prints all the elements of the stack
void print_queue(Queue *queue){
    if (queue_is_empty(queue)){
        printf("Queue is empty");
    }else{
        while(!stack_is_empty(queue->Stack1)){
            // Moves elements from stack 1 to stack 2
            stack_push(queue->Stack2, stack_pop(queue->Stack1));
        };
        // stack 2 is the reverse of stack 1, which simulates Queue 
        // behavior (First In First Out)
        Node *top_now = queue->Stack2->top; 
        while(top_now != NULL){
            // Prints elements from the oldest to latest
            printf("%d ", top_now->value);
            top_now = top_now->next; // Next element
        };
        while(!stack_is_empty(queue->Stack2)){
            // Moves elements from stack 2 to stack 1
            stack_push(queue->Stack1, stack_pop(queue->Stack2));
        };
    }
}
// Cheks if the Queue is empty
bool queue_is_empty(Queue *queue){
    return (queue->Stack1->top == NULL && queue->Stack2->top == NULL);
}
// Removes all elements from the Queue
void empty_queue(Queue *queue){
        empty_stack(queue->Stack1);
        empty_stack(queue->Stack2);
}

// Returns the number of elements in the queue
int queue_size(Queue *queue){
    return (stack_size(queue->Stack1) + stack_size(queue->Stack2));
}


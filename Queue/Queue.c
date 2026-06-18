/* This file provides necessary functions to implement a Queue using two stacks
   Possible operations for Queue :
   - enqueue: Add an element to its rear
   - dequeue: Remove an element from the front 

   With two stacks it is possible to make a Queue, using one stack
   to add elements, and the second one to remove the first added element.

   This can be simulated by moving the elements from stack 1 to stack 2,
   using pop function of the Stack. This reverses the order of the elements,
   allowing the oldest element to be removed first.
*/

# include "../Stack/stack.h"
# include "Queue.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

// Creates a new queue
Queue create_queue(){
    Queue new_queue;

    Stack *stack1 = malloc(sizeof(Stack));
    stack1->top = NULL;
    stack1->size = 0;

    Stack *stack2 = malloc(sizeof(Stack));
    stack2->top = NULL;
    stack2->size = 0;

    new_queue.Stack1 = stack1;
    new_queue.Stack2 = stack2;
    
    return new_queue;
}

// Adds an element to the queue
// Uses stack 1 to store elements
void enqueue(Queue *queue, int i){
    stack_push(queue->Stack1, i); // Stores elements in first stack
}

// Removes and returns oldest element of the Queue
int dequeue(Queue *queue) { 
    
    if (queue_is_empty(queue)){
        printf("Queue is empty\n");
        return 0;
    }
    else {
        if (queue->Stack2->top == NULL){
            while(!stack_is_empty(queue->Stack1)){
                stack_push(queue->Stack2, stack_pop(queue->Stack1)); 
            }
        }

        if (queue->Stack2->top == NULL){
            printf("Queue is empty\n");
            return 0;
        }
        
        int nb = stack_pop(queue->Stack2);
        return nb;
    }
}
// Returns the oldest element without removing it
int queue_peek(Queue *queue){
    if (queue_is_empty(queue)){
        printf("Queue is empty\n");
        return 0;
    }
    else {
        if(queue->Stack2->top == NULL){
            while(!stack_is_empty(queue->Stack1)){
                stack_push(queue->Stack2, stack_pop(queue->Stack1)); 
            }
        }

        if (queue->Stack2->top == NULL){
            printf("Queue is empty\n");
            return 0;
        }
        
        int nb = queue->Stack2->top->value;
        return nb;
    }
}

// Helper function to print a reversed stack (used to print stack 1 after stack 2)
void print_stack_bottom_to_top(Node *node){
    if (node == NULL)
        return;

    print_stack_bottom_to_top(node->next);
    printf("%d ", node->value);
}

// Prints all the elements of the queue
void print_queue(Queue *queue){
    if (queue_is_empty(queue)){
        printf("Queue is empty\n");
    }else{

        // Print Stack2 (front part of queue)
        Node *top_now = queue->Stack2->top; 
        while(top_now != NULL){
            printf("%d ", top_now->value);
            top_now = top_now->next;
        }

        // Print Stack1 (needs reverse order)
        print_stack_bottom_to_top(queue->Stack1->top);
    }
}
// Checks if the Queue is empty
bool queue_is_empty(Queue *queue){
    return (queue->Stack1->top == NULL && queue->Stack2->top == NULL);
}
// Removes all elements from the Queue
void empty_queue(Queue *queue){
        empty_stack(queue->Stack1);
        empty_stack(queue->Stack2);
}

// Frees all elements and the stacks themselves 
void destroy_queue(Queue *queue) {
    empty_stack(queue->Stack1);
    empty_stack(queue->Stack2);
    free(queue->Stack1);
    free(queue->Stack2);
}

// Returns the number of elements in the queue
int queue_size(Queue *queue){
    return (stack_size(queue->Stack1) + stack_size(queue->Stack2));
}


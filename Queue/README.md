# Queue

## Description

A queue is a data structure that follows the First In, First Out (FIFO) principle, meaning that the first element added is the first one removed. In this implementation, it is built using two stacks.

## How it works

### Structure
Internally, the queue is implemented using two stacks. The first stack (Stack1) is used to store elements when they are enqueued, while the second stack is used to retrieve elements in the correct order for dequeue operations. This structure allows the queue to simulate a FIFO (First-In First-Out) behavior using two LIFO (Last-In First-Out) stacks.

### Enqueue
When a new value is enqueued, it is directly pushed to Stack1. This operation is fast because it doesn't require accessing or rearranging of existing elements. 

### Dequeue & Peek
When a value is dequeued or peeked, the algorithm first checks whether Stack2 is empty. If it is empty, all elements from Stack1 are popped one by one and pushed into Stack2. This process reverses the order of the elements, so the oldest inserted value ends up on top of Stack2.
Once the transfer is complete (or if Stack2 was already not empty), the top element of Stack2 is either popped (for dequeue) or read (for peek). If both stacks are empty, the queue is considered empty and there are no elements to return.

## Operations

| Function | Description | Time complexity |
|----------|-------------|-----------------|
| create_queue | Creates a new queue | O(1) |
| enqueue | Adds a new element to the queue, precisely to StackA (rear of the queue). | O(1) |
| dequeue | Removes and returns oldest element. If Stack2 is empty, all elements from Stack1 are moved to Stack2 (reversing order), then the top of Stack2 is popped. | - O(1): when no moving between stacks is needed. <br> - O(n): when elements must be moved from Stack1 to Stack2. |
| queue_peek | Returns the oldest element without removing it. If Stack2 is empty, all elements from Stack1 are moved to Stack2 (reversing order), then the top of Stack2 is saved. | - O(1): when no moving between stacks is needed. <br> - O(n): when elements must be moved from Stack1 to Stack2. |
| print_stack_bottom_to_top | Helper function that uses recursion to print a reversed stack. | O(n) |
| print_queue | Prints all the elements of the queue. | O(n) |
| queue_is_empty | Checks if the queue is empty. | O(1) |
| empty_queue | Removes all elements from the queue by removing them from Stack1 and Stack2. | O(n) |
| destroy_queue | Frees all elements and the stacks themselves. Used when the queue is no longer needed | O(n) |
| queue_size | Returns the number of elements in the queue (number of elements in both Stack1 and Stack2). | O(1) |

## Example

```c

#include "Queue.h"
#include <stdio.h>

int main(void) {
    Queue q = create_queue();

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);

    printf("Queue: ");
    print_queue(&q); // 10 20 30 
    printf("\n");

    printf("Front (peek): %d\n", queue_peek(&q)); // 10

    int removed = dequeue(&q);
    printf("Dequeued: %d\n", removed); // 10

    printf("Queue after dequeue: ");
    print_queue(&q); // 20 30 
    printf("\n");

    printf("Size: %d\n", queue_size(&q)); // 2

    empty_queue(&q);
    printf("Empty after empty_queue()? %s\n", queue_is_empty(&q) ? "yes" : "no"); // yes

    destroy_queue(&q);

    return 0;
}

```

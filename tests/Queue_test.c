/*
Queue_test.c

Purpose:
Tests the correctness of the Queue implementation.

Covered scenarios:
- Empty queue handling
- General enqueue/dequeue
- Peek
- Size tracking
- Print correctness
- Enqueue after full dequeue
- Mixed enqueue/dequeue
- Single element
- Stress testing
*/

#include <stdio.h>
#include <stdlib.h>
#include "../Queue/Queue.h"

int main(){

    // Test 1: Empty queue
    // Verifies that a newly created queue is empty
    // and has size 0 without any operations
    printf("=== Test 1 ===\n\n");

    Queue q = create_queue();
    printf("Empty?: %s\n", queue_is_empty(&q) ? "yes" : "no");
    printf("Size: %d\n\n", queue_size(&q));

    // Test 2: Enqueue elements
    // Checks if elements are correctly added to the queue
    // and that size is also tracked correctly
    printf("=== Test 2 ===\n\n");

    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);
    enqueue(&q, 4);
    enqueue(&q, 5);

    printf("Queue: ");
    print_queue(&q);
    printf("\n");
    printf("Empty?: %s\n", queue_is_empty(&q) ? "yes" : "no");
    printf("Size: %d\n\n", queue_size(&q));

    // Test 3: Dequeue
    // Ensures elements are removed in FIFO order
    // and size is correctly tracked
    printf("=== Test 3 ===\n\n");

    printf("%d->", dequeue(&q));
    printf("%d->", dequeue(&q));
    printf("%d->", dequeue(&q));
    printf("%d->", dequeue(&q));
    printf("%d\n", dequeue(&q));

    printf("Empty?: %s\n", queue_is_empty(&q) ? "yes" : "no");
    printf("Size: %d\n\n", queue_size(&q));

    printf("Dequeue after empty: \n");
    dequeue(&q);

    // Test 4: Peek
    // Ensures peek returns the front element without removing it
    printf("=== Test 4 ===\n\n");

    Queue q2 = create_queue();
    enqueue(&q2, 10);
    enqueue(&q2, 20);
    enqueue(&q2, 30);

    printf("1st peek: %d\n", queue_peek(&q2));
    printf("2nd peek: %d\n", queue_peek(&q2));

    printf("Empty?: %s\n", queue_is_empty(&q2) ? "yes" : "no");
    printf("Size: %d\n\n", queue_size(&q2));

    // Test 5: Print & empty
    // Verifies print and empty functions work correctly
    printf("=== Test 5 ===\n\n");

    printf("Queue: ");
    print_queue(&q2);
    printf("\n\nBefore empty\n");
    printf("Empty?: %s\n", queue_is_empty(&q2) ? "yes" : "no");
    printf("Size: %d\n\n", queue_size(&q2));

    empty_queue(&q2);

    printf("\nAfter empty\n");
    printf("Empty?: %s\n", queue_is_empty(&q2) ? "yes" : "no");
    printf("Size: %d\n\n", queue_size(&q2));

    // Test 6: Lazy transfer
    // Verifies that dequeue correctly transfers elements from Stack1 to Stack2
    printf("=== Test 6 ===\n\n");

    Queue q3 = create_queue();
    enqueue(&q3, 100);
    enqueue(&q3, 200);
    enqueue(&q3, 300);

    printf("Dequeue: %d\n", dequeue(&q3)); // triggers transfer
    printf("Queue after transfer: ");
    print_queue(&q3);
    printf("\n");
    enqueue(&q3, 400);
    printf("Queue after new enqueue: ");
    print_queue(&q3);
    printf("\n\n");

    // Test 7: Stress test
    // Verifies correct FIFO behavior under heavy usage
    printf("=== Test 7 ===\n\n");

    Queue q4 = create_queue();
    for(int i = 0; i < 1000000; i++){
        enqueue(&q4, i);
    }

    printf("Peek: %d\n", queue_peek(&q4));
    printf("Size: %d\n", queue_size(&q4));

    for(int i = 0; i < 1000000; i++){
        if(i != dequeue(&q4)){
            printf("FAILED\n");
            return 1;
        }
    }
    printf("1000000 DEQUEUE PASSED\n");
    printf("Empty?: %s\n\n", queue_is_empty(&q4) ? "yes" : "no");

    // Test 8: Enqueue after full dequeue
    // Verifies queue works correctly after being emptied through dequeuing
    printf("=== Test 8 ===\n\n");

    Queue q5 = create_queue();
    enqueue(&q5, 1);
    enqueue(&q5, 2);
    enqueue(&q5, 3);

    dequeue(&q5);
    dequeue(&q5);
    dequeue(&q5);

    printf("Empty after dequeue all?: %s\n", queue_is_empty(&q5) ? "yes" : "no");

    enqueue(&q5, 10);
    enqueue(&q5, 20);

    printf("Queue after re-enqueue: ");
    print_queue(&q5);
    printf("\n");
    printf("Size: %d\n\n", queue_size(&q5));

    // Test 9: Mixed enqueue/dequeue
    // Stresses the Stack1/Stack2 transfer logic in different states
    printf("=== Test 9 ===\n\n");

    Queue q6 = create_queue();
    enqueue(&q6, 1);
    enqueue(&q6, 2);
    printf("Dequeue: %d\n", dequeue(&q6)); // triggers transfer, should be 1
    enqueue(&q6, 3);
    enqueue(&q6, 4);
    printf("Dequeue: %d\n", dequeue(&q6)); // should be 2
    printf("Dequeue: %d\n", dequeue(&q6)); // should be 3
    enqueue(&q6, 5);
    printf("Queue: ");
    print_queue(&q6);
    printf("\n");
    printf("Size: %d\n\n", queue_size(&q6));

    // Test 10: Single element
    // Verifies simplest non-trivial case
    printf("=== Test 10 ===\n\n");

    Queue q7 = create_queue();
    enqueue(&q7, 42);
    printf("Peek: %d\n", queue_peek(&q7)); // 42
    printf("Dequeue: %d\n", dequeue(&q7)); // 42
    printf("Empty?: %s\n", queue_is_empty(&q7) ? "yes" : "no"); // yes
    printf("Size: %d\n\n", queue_size(&q7)); // 0

    destroy_queue(&q);
    destroy_queue(&q2);
    destroy_queue(&q3);
    destroy_queue(&q4);
    destroy_queue(&q5);
    destroy_queue(&q6);
    destroy_queue(&q7);

    return 0;
}

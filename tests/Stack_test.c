/*
Stack_test.c

Purpose: 
Tests the correctness of the stack implementation.

Covered scenarios:
- General push/pop
- Peek
- Size tracking
- Print correctness
- Stress testing
*/

#include <stdio.h>
#include <stdlib.h>
#include "../Stack/stack.h"


int main(){

    // Test 1: Empty stack
    // Verifies that a newly created stack is empty
    // and has size 0 without any operations

    printf("=== Test 1 ===");

    printf("\n\n");

    Stack stack = create_stack();
    printf("Empty?: %s\n", stack_is_empty(&stack) ? "yes" : "no");
    printf("Size: %d\n\n", stack_size(&stack));


    // Test 2: Pushing elements
    // Checks if elements are correctly added to the stack,
    // and that size is also tracked correctly

    printf("=== Test 2 ===");
     
    printf("\n\n");

    stack_push(&stack, 1);
    stack_push(&stack, 2);
    stack_push(&stack, 3);
    stack_push(&stack, 4);
    stack_push(&stack, 5);

    printf("Empty?: %s\n", stack_is_empty(&stack) ? "yes" : "no");
    printf("Size: %d\n\n", stack_size(&stack));

    // Test 3: Pop 
    // Ensures removing elements works correctly,
    // and that size is correctly tracked

    printf("=== Test 3 ===");

    printf("\n\n");

    printf("%d->", stack_pop(&stack));
    printf("%d->", stack_pop(&stack));
    printf("%d->", stack_pop(&stack));
    printf("%d->", stack_pop(&stack));
    printf("%d\n", stack_pop(&stack));

    printf("Empty?: %s\n", stack_is_empty(&stack) ? "yes" : "no");
    printf("Size: %d\n\n", stack_size(&stack));
    
    printf("Pop after empty: \n");
    stack_pop(&stack);

    // Test 4: Peek
    // Ensures peek returns the top element without removing it


    printf("=== Test 4 ===");

    printf("\n\n");
    Stack stack2 = create_stack();
    

    stack_push(&stack2, 1);
    stack_push(&stack2, 2);
    stack_push(&stack2, 3);
    

    printf("1st peek: %d\n", stack_peek(&stack2));
    printf("2nd peek: %d\n", stack_peek(&stack2));
    

    printf("Empty?: %s\n", stack_is_empty(&stack2) ? "yes" : "no");
    printf("Size: %d\n\n", stack_size(&stack2));

    empty_stack(&stack2);

    printf("Peek after empty: \n");
    stack_peek(&stack2);

    // Test 5: Print & empty
    // Verifies print and empty functions work perfectly

    printf("=== Test 5 ===");

    printf("\n\n");


    stack_push(&stack2, 10);
    stack_push(&stack2, 2);
    stack_push(&stack2, 3);
    stack_push(&stack2, 4);
    stack_push(&stack2, 6);
    stack_push(&stack2, 8);

    printf("Stack: ");

    print_stack(&stack2);
    printf("\n\nBefore Empty\n");

    printf("Empty?: %s\n", stack_is_empty(&stack2) ? "yes" : "no");
    printf("Size: %d\n\n", stack_size(&stack2));

    empty_stack(&stack2);

    printf("\nAfter Empty\n");

    printf("Empty?: %s\n", stack_is_empty(&stack2) ? "yes" : "no");
    printf("Size: %d\n\n", stack_size(&stack2));

    // Test 6: Stress test
    // Verifies correct behavior under heavy usage

    printf("=== Test 6 ==="); 
    printf("\n\n");

    Stack stack3 = create_stack();
    for(int i = 0; i <= 1000000; i++){
        stack_push(&stack3, i);
    }

    printf("Peek: %d\n", stack_peek(&stack3));
    printf("Size: %d\n", stack_size(&stack3));
    printf("Empty?: %s\n", stack_is_empty(&stack3) ? "yes" : "no");


    for(int i = 1000000; i >= 0; i--){
        if(i != stack_pop(&stack3)) {
            printf("FAILED");
            return 1;
        }

    }
    printf("1000001 POP PASSED\n");
    printf("Empty?: %s\n", stack_is_empty(&stack3) ? "yes" : "no");

    return 0;
}

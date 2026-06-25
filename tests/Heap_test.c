/*
Heap_test.c

Purpose:
Tests the correctness of the Heap implementation (both max and min).

Covered scenarios:
- Empty heap handling
- Max-heap: general insertion and extraction order
- Min-heap: general insertion and extraction order
- Peek without removal
- Empty heap peek and extract
- Duplicate values
- Single element
- Two elements
- Ascending insertion (stresses bubble-up)
- Descending insertion (stresses bubble-down)
- Empty after operations and reuse
- Print correctness
- Stress test (max-heap)
- Stress test (min-heap)
*/

#include <stdio.h>
#include <stdlib.h>
#include "../Heap/Heap.h"

int main(){

    // Test 1: Empty heap
    // Verifies that a newly created heap is empty
    // and has size 0 without any operations
    printf("=== Test 1 ===\n\n");

    Heap h = create_heap(true);
    printf("Empty?: %s\n", is_empty_heap(&h) ? "yes" : "no");
    printf("Size: %d\n\n", heap_length(&h));

    // Test 2: Max-heap general insertion and extraction
    // Verifies that extraction returns values in descending order
    printf("=== Test 2 ===\n\n");

    Heap h1 = create_heap(true);
    int values[] = {50, 30, 80, 20, 40, 70, 90, 10, 60};
    int n = sizeof(values) / sizeof(values[0]);

    for(int i = 0; i < n; i++)
        heap_add(&h1, values[i]);

    printf("Size after %d inserts: %d\n", n, heap_length(&h1));
    printf("Max-heap extraction order (expect descending): ");
    while(!is_empty_heap(&h1))
        printf("%d ", heap_extract(&h1));
    printf("\n\n");

    // Test 3: Min-heap general insertion and extraction
    // Verifies that extraction returns values in ascending order
    printf("=== Test 3 ===\n\n");

    Heap h2 = create_heap(false);
    for(int i = 0; i < n; i++)
        heap_add(&h2, values[i]);

    printf("Size after %d inserts: %d\n", n, heap_length(&h2));
    printf("Min-heap extraction order (expect ascending): ");
    while(!is_empty_heap(&h2))
        printf("%d ", heap_extract(&h2));
    printf("\n\n");

    // Test 4: Peek without removal
    // Verifies peek returns root without changing size
    printf("=== Test 4 ===\n\n");

    Heap h3 = create_heap(true);
    heap_add(&h3, 15);
    heap_add(&h3, 40);
    heap_add(&h3, 25);

    printf("Max-heap peek (expect 40): %d\n", heap_peek(&h3));
    printf("Size unchanged after peek: %d\n", heap_length(&h3));

    Heap h3b = create_heap(false);
    heap_add(&h3b, 15);
    heap_add(&h3b, 40);
    heap_add(&h3b, 25);

    printf("Min-heap peek (expect 15): %d\n", heap_peek(&h3b));
    printf("Size unchanged after peek: %d\n\n", heap_length(&h3b));

    // Test 5: Empty heap peek and extract
    // Verifies correct error handling on empty heap
    printf("=== Test 5 ===\n\n");

    Heap h4 = create_heap(true);
    printf("peek on empty heap: ");
    heap_peek(&h4);
    printf("\n");
    printf("extract on empty heap: ");
    heap_extract(&h4);
    printf("\n\n");

    // Test 6: Duplicate values
    // Ensures the heap correctly handles duplicate elements
    printf("=== Test 6 ===\n\n");

    Heap h5 = create_heap(true);
    heap_add(&h5, 5);
    heap_add(&h5, 5);
    heap_add(&h5, 10);
    heap_add(&h5, 10);
    heap_add(&h5, 7);

    printf("Max-heap with duplicates (expect 10 10 7 5 5): ");
    while(!is_empty_heap(&h5))
        printf("%d ", heap_extract(&h5));
    printf("\n\n");

    // Test 7: Single element
    // Verifies extraction works correctly when heap contains only one value
    printf("=== Test 7 ===\n\n");

    Heap h6 = create_heap(true);
    heap_add(&h6, 42);

    printf("Peek (expect 42): %d\n", heap_peek(&h6));
    printf("Extract (expect 42): %d\n", heap_extract(&h6));
    printf("Empty after extract?: %s\n", is_empty_heap(&h6) ? "yes" : "no");
    printf("Size: %d\n\n", heap_length(&h6));

    // Test 8: Two elements
    // Verifies the simplest non-trivial heap configuration
    printf("=== Test 8 ===\n\n");

    Heap h7 = create_heap(true);
    heap_add(&h7, 10);
    heap_add(&h7, 20);

    printf("Max-heap two elements (expect 20 10): ");
    while(!is_empty_heap(&h7))
        printf("%d ", heap_extract(&h7));
    printf("\n\n");

    // Test 9: Ascending insertion
    // Stresses the bubble-up operation by inserting increasing values
    printf("=== Test 9 ===\n\n");

    Heap h8 = create_heap(true);
    for(int i = 1; i <= 20; i++)
        heap_add(&h8, i);

    printf("Max-heap ascending insert (expect 20 down to 1): ");
    while(!is_empty_heap(&h8))
        printf("%d ", heap_extract(&h8));
    printf("\n\n");

    // Test 10: Descending insertion
    // Stresses extraction and bubble-down behavior
    printf("=== Test 10 ===\n\n");

    Heap h9 = create_heap(true);
    for(int i = 20; i >= 1; i--)
        heap_add(&h9, i);

    printf("Max-heap descending insert (expect 20 down to 1): ");
    while(!is_empty_heap(&h9))
        printf("%d ", heap_extract(&h9));
    printf("\n\n");

    // Test 11: Empty after operations and reuse
    // Verifies heap can be reused after empty_heap
    printf("=== Test 11 ===\n\n");

    Heap h10 = create_heap(true);
    heap_add(&h10, 1);
    heap_add(&h10, 2);
    heap_add(&h10, 3);

    empty_heap(&h10);
    printf("After empty:\n");
    printf("Empty?: %s\n", is_empty_heap(&h10) ? "yes" : "no");
    printf("Size: %d\n", heap_length(&h10));

    heap_add(&h10, 100);
    heap_add(&h10, 50);
    heap_add(&h10, 200);
    printf("After re-add, peek (expect 200): %d\n", heap_peek(&h10));
    printf("Size: %d\n\n", heap_length(&h10));

    // Test 12: Print
    // Verifies print function works correctly on non-empty and empty heap
    printf("=== Test 12 ===\n\n");

    Heap h11 = create_heap(false);
    heap_add(&h11, 30);
    heap_add(&h11, 10);
    heap_add(&h11, 20);

    printf("Min-heap internal array: ");
    print_heap(&h11);
    printf("\n");

    Heap h12 = create_heap(true);
    printf("Print empty heap: ");
    print_heap(&h12);
    printf("\n");

    // Test 13: Stress test max-heap
    // Inserts 1000000 values and verifies extracted values are in descending order
    printf("=== Test 13 ===\n\n");

    Heap h13 = create_heap(true);
    for(int i = 0; i < 1000000; i++)
        heap_add(&h13, rand() % 1000000);

    printf("Size after 1000000 inserts: %d\n", heap_length(&h13));

    int prev = heap_extract(&h13);
    int errors = 0;
    while(!is_empty_heap(&h13)){
        int curr = heap_extract(&h13);
        if(curr > prev) errors++;
        prev = curr;
    }
    printf("Max-heap order errors: %d\n", errors == 0 ? 0 : errors);
    printf("Empty after full extraction?: %s\n\n", is_empty_heap(&h13) ? "yes" : "no");

    // Test 14: Stress test min-heap
    // Inserts 1000000 values and verifies extracted values are in ascending order
    printf("=== Test 14 ===\n\n");

    Heap h14 = create_heap(false);
    for(int i = 0; i < 1000000; i++)
        heap_add(&h14, rand() % 1000000);

    printf("Size after 1000000 inserts: %d\n", heap_length(&h14));

    prev = heap_extract(&h14);
    errors = 0;
    while(!is_empty_heap(&h14)){
        int curr = heap_extract(&h14);
        if(curr < prev) errors++;
        prev = curr;
    }
    printf("Min-heap order errors: %d\n", errors == 0 ? 0 : errors);
    printf("Empty after full extraction?: %s\n", is_empty_heap(&h14) ? "yes" : "no");

    destroy_heap(&h);
    destroy_heap(&h1);
    destroy_heap(&h2);
    destroy_heap(&h3);
    destroy_heap(&h3b);
    destroy_heap(&h4);
    destroy_heap(&h5);
    destroy_heap(&h6);
    destroy_heap(&h7);
    destroy_heap(&h8);
    destroy_heap(&h9);
    destroy_heap(&h10);
    destroy_heap(&h11);
    destroy_heap(&h12);
    destroy_heap(&h13);
    destroy_heap(&h14);

    return 0;
}

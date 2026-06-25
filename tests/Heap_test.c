/*
Heap_test.c

Purpose:
Tests the correctness of the Heap implementation.

Covered scenarios:
- General insertion/extraction
- Duplicate values
- Single-element heaps
- Two-element heaps
- Ascending insertion
- Descending insertion
- Randomized stress testing
*/

#include <stdio.h>
#include <stdlib.h>
#include "../Heap/Heap.h"

int main(){

    // Test 1: Empty heap
    // Verifies that a newly created heap is empty
    // and has size 0 without any operations

    printf("=== Test 1 ===");

    printf("\n\n");

    Heap h = create_heap(true);
    printf("Empty?: %s\n", is_empty_heap(&h) ? "yes" : "no");
    printf("Size: %d\n\n", heap_length(&h));

    // Test 2: General functionality.
    // Verifies that insertion and extraction preserve max-heap ordering.
    printf("=== Test 2 ===\n");

    Heap h1 = create_heap(true);

    int values[] = {50,30,80,20,40,70,90,10,60};

    int n = sizeof(values)/sizeof(values[0]);

    for(int i=0;i<n;i++)
        heap_add(&h1, values[i]);

    while(!is_empty_heap(&h1))
        printf("%d ", heap_extract(&h1));

    printf("\n\n");


    // Test 3: Duplicate values.
    // Ensures the heap correctly handles duplicate elements.
    printf("=== Test 3 ===\n");

    Heap h2 = create_heap(true);

    heap_add(&h2,5);
    heap_add(&h2,5);
    heap_add(&h2,10);
    heap_add(&h2,10);
    heap_add(&h2,7);

    while(!is_empty_heap(&h2))
        printf("%d ", heap_extract(&h2));

    printf("\n\n");


    // Test 4: Single element.
    // Verifies extraction works correctly when the heap contains only one value.
    printf("=== Test 4 ===\n");

    Heap h3 = create_heap(true);

    heap_add(&h3,42);

    printf("%d\n\n",heap_extract(&h3));
    printf("Empty? : %s\n", is_empty_heap(&h3) ? "yes": "no");


    // Test 5: Two elements.
    // Verifies the simplest non-trivial heap configuration.
    printf("=== Test 5 ===\n");

    Heap h4 = create_heap(true);

    heap_add(&h4,10);
    heap_add(&h4,20);

    while(!is_empty_heap(&h4))
        printf("%d ",heap_extract(&h4));

    printf("\n\n");


    // Test 6: Ascending insertion.
    // Stresses the bubble-up operation by inserting increasing values.
    printf("=== Test 6 ===\n");

    Heap h5 = create_heap(true);

    for(int i=1;i<=20;i++)
        heap_add(&h5,i);

    while(!is_empty_heap(&h5))
        printf("%d ",heap_extract(&h5));

    printf("\n\n");

    // Test 7: Descending insertion.
    // Stresses extraction and bubble-down behavior.
    printf("=== Test 7 ===\n");

    Heap h6 = create_heap(true);

    for(int i=20;i>=1;i--)
        heap_add(&h6,i);

    while(!is_empty_heap(&h6))
        printf("%d ",heap_extract(&h6));

    printf("\n\n");


    // Test 8: Randomized stress test.
    // Inserts 1000 random values and verifies extracted values remain sorted.
    printf("=== Test 8 ===\n");

    Heap h7 = create_heap(true);

    for(int i=0;i<1000;i++)
        heap_add(&h7, rand()%1000);

    int previous = heap_extract(&h7);

    while(!is_empty_heap(&h7)){

        int current = heap_extract(&h7);

        if(current > previous){
            printf("ERROR\n");
            return 1;
        }

        previous = current;
    }

    printf("PASS\n");


    destroy_heap(&h);
    destroy_heap(&h1);
    destroy_heap(&h2);
    destroy_heap(&h3);
    destroy_heap(&h4);
    destroy_heap(&h5);
    destroy_heap(&h6);
    destroy_heap(&h7);


    return 0;
}

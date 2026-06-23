/*
Dynamic_array_test.c

Purpose:
Tests the correctness of the Dynamic Array implementation.

Covered scenarios:
- Empty array handling
- General append/insertion/deletion
- Duplicate values
- Correct resizing
- Printing multiple values
- Correct indexing
- Updating values
- Stress testing
*/

#include <stdio.h>
#include "../Array/dynamic_array.h"


int main(){
    // Test 1: Empty array 
    // Verifies that a newly created dynamic array is empty
    // and has size 0 without any operations

    printf("=== Test 1 ===");

    printf("\n\n");

    Dynamic_Array d_array = create_dynamic_array();
    printf("Empty?: %s\n", is_empty_dynamic_array(&d_array) ? "yes" : "no");
    printf("Size: %d\n\n", get_dynamic_array_length(&d_array));


    // Test 2: Single append
    // Verifies if a simple append works perfectly

    printf("=== Test 2 ===");
    printf("\n\n");

    dynamic_array_append(&d_array, 68);
    printf("Dynamic array: ");
    print_dynamic_array(&d_array);
    printf("\n");
    printf("Size: %d", get_dynamic_array_length(&d_array));
    printf("\n\n");

    // Test 3: Multiple appends
    // Verifies that the dynamic array can handle multiple elements,
    // automatic capacity expansion works correctly,
    // and values can be retrieved accurately.

    printf("=== Test 3 ===");
    printf("\n\n");

    Dynamic_Array d_array2 = create_dynamic_array();

    for(int i = 0; i < 100; i++){
        dynamic_array_append(&d_array2, i);
    }

    printf("First element: %d\n", dynamic_array_value(&d_array2, 0));
    printf("50th element: %d\n", dynamic_array_value(&d_array2, 50));
    printf("Last element: %d\n", dynamic_array_value(&d_array2, get_dynamic_array_length(&d_array2) - 1));
    printf("101th element: %d\n", dynamic_array_value(&d_array2, 101));

    printf("Size: %d", get_dynamic_array_length(&d_array2));
    printf("\n\n");


    // Test 4: Printing 
    // Ensures the print function doesn't crash with multiple elements
    printf("=== Test 4 ===");
    printf("\n\n");
    Dynamic_Array d_array3 = create_dynamic_array();
    printf("Dynamic array before adding elements: ");
    print_dynamic_array(&d_array3);
    printf("\n");

    for(int i = 1; i <= 30; i++){
        dynamic_array_append(&d_array3, i); // Adds 30 elements
    }
    
    printf("Dynamic array: ");
    print_dynamic_array(&d_array3);
    printf("\n");
    printf("Size: %d", get_dynamic_array_length(&d_array3));
    printf("\n\n");

    // Test 5: Deletion
    // Verifies that delete function correctly shifts all elements, 
    // and updates size correctly

    printf("=== Test 5 ===");
    printf("\n\n");
    Dynamic_Array d_array4 = create_dynamic_array();

    dynamic_array_append(&d_array4, 1);
    dynamic_array_append(&d_array4, 2);
    dynamic_array_append(&d_array4, 3);
    dynamic_array_append(&d_array4, 4);
    dynamic_array_append(&d_array4, 5);
    dynamic_array_append(&d_array4, 6);

    int size = get_dynamic_array_length(&d_array4);

    printf("Before deletion: ");
    print_dynamic_array(&d_array4);
    printf("\n");
    printf("After deleting first element: ");
    dynamic_array_delete(&d_array4, 0);
    size = get_dynamic_array_length(&d_array4);
    print_dynamic_array(&d_array4);
    printf("\n");
    printf("After deleting middle element: ");
    dynamic_array_delete(&d_array4, size / 2);
    size = get_dynamic_array_length(&d_array4);
    print_dynamic_array(&d_array4);
    printf("\n");
    printf("After deleting last element: ");
    dynamic_array_delete(&d_array4, size-1);
    print_dynamic_array(&d_array4);

    printf("\n\n");

    // Test 6: Insert vs Update
    // Verifies that insertion increases the size whereas
    // updating only changes an existing value

    printf("=== Test 6 ===");
    printf("\n\n");
    Dynamic_Array d_array5 = create_dynamic_array();

    for(int i = 1; i <= 5; i++){
        dynamic_array_append(&d_array5, i); // Adds 5 elements
    }

    printf("Dynamic array before operations: ");
    print_dynamic_array(&d_array5);
    printf("    Size: %d", get_dynamic_array_length(&d_array5));
    printf("\n");

    dynamic_array_insert(&d_array5, 3, 80);
    printf("Insert 80 at index 3: ");
    print_dynamic_array(&d_array5);
    printf("    Size: %d", get_dynamic_array_length(&d_array5));
    printf("\n");
    
    dynamic_array_insert(&d_array5, 0, 80);
    printf("Insert 80 as first element (index 0): ");
    print_dynamic_array(&d_array5);
    printf("    Size: %d", get_dynamic_array_length(&d_array5));
    printf("\n");

    dynamic_array_update(&d_array5, 2, 99);
    printf("Update value at index 2 to 99: ");
    print_dynamic_array(&d_array5);
    printf(" Size: %d", get_dynamic_array_length(&d_array5));
    printf("\n");

    dynamic_array_update(&d_array5, get_dynamic_array_length(&d_array5) - 1, 99);
    printf("Update last element to 99: ");
    print_dynamic_array(&d_array5);
    printf("    Size: %d", get_dynamic_array_length(&d_array5));
    printf("\n\n");

    // Test 7: Get index of a value
    // Verifies that the correct index is returned for a given value,
    // and the dynamic_array_get_indexes correctly finds all indexes of a value

    printf("=== Test 7 ===");
    printf("\n\n");

    printf("Dynamic array: ");
    print_dynamic_array(&d_array5);
    printf("\n");
    printf("Index of value 1: %d\n", dynamic_array_get_index(&d_array5, 1));
    printf("Index of value 3: %d\n", dynamic_array_get_index(&d_array5, 3));
    printf("Index of value 80: %d\n", dynamic_array_get_index(&d_array5, 80));
    printf("Index of value 99: %d\n", dynamic_array_get_index(&d_array5, 99));
    Dynamic_Array indexes = dynamic_array_get_indexes(&d_array5, 80);
    printf("Indexes of value 80: ");
    print_dynamic_array(&indexes);
    printf("\n\n");

    // Test 8: Multiple operations
    // Verifies correct behavior under heavy usage including
    // multiple insertions, updates, deletions, and resizing.

    printf("=== Test 8 ===");
    printf("\n\n");


    Dynamic_Array d_array6 = create_dynamic_array();

    for (int i = 0; i < 100; i++){
        dynamic_array_append(&d_array6, i);
    }

    printf("Dynamic array before operations: ");
    print_dynamic_array(&d_array6);
    printf(" Size: %d", get_dynamic_array_length(&d_array6));
    printf("\n");

    

    dynamic_array_update(&d_array6, 0, 1000);
    int index = 2;
    while(index < get_dynamic_array_length(&d_array6)){
        dynamic_array_update(&d_array6, index, 1000);
        index = index * 2;
    }

    

    
    Dynamic_Array powers_of_two = dynamic_array_get_indexes(&d_array6, 1000);

    for(int i = 0; i < 100; i++){ 
        if(i % 30 == 0){
            dynamic_array_insert(&d_array6, i , 3000);
        }
    }

    Dynamic_Array divisible_by_30 = dynamic_array_get_indexes(&d_array6, 3000);

    printf("Dynamic array after operations: ");
    print_dynamic_array(&d_array6);
    printf(" Size: %d", get_dynamic_array_length(&d_array6));
    printf("\n");


    printf("Powers of two (updated values of indexes that are power of two): ");
    print_dynamic_array(&powers_of_two);
    printf("\n");
    printf("Divisible by 30 (inserted 3000 to indexes divisble by 30): ");
    print_dynamic_array(&divisible_by_30);
    printf("\n");

    for (int i = 0; i < 40; i++){
        dynamic_array_delete(&d_array6, 0);
    }

    printf("Dynamic array after deleting first 40 elements: ");
    print_dynamic_array(&d_array6);
    printf(" Size: %d", get_dynamic_array_length(&d_array6));
    printf("\n");
    printf("Empty? %s\n", is_empty_dynamic_array(&d_array6) ? "yes" : "no");

    empty_dynamic_array(&d_array6);
    printf("Dynamic array after applying empty function: ");
    print_dynamic_array(&d_array6);
    printf(" Size: %d", get_dynamic_array_length(&d_array6));
    printf("\n");
    printf("Empty? %s\n", is_empty_dynamic_array(&d_array6) ? "yes" : "no");


    printf("\n\nALL TESTS PASSED\n");

    destroy_dynamic_array(&d_array);
    destroy_dynamic_array(&d_array2);
    destroy_dynamic_array(&d_array3);
    destroy_dynamic_array(&d_array4);
    destroy_dynamic_array(&d_array5);
    destroy_dynamic_array(&d_array6);
    destroy_dynamic_array(&powers_of_two);
    destroy_dynamic_array(&divisible_by_30);
    destroy_dynamic_array(&indexes);

    return 0;
}

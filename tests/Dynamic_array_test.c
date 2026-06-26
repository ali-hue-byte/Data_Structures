/*
Dynamic_array_test.c

Run: 
gcc Dynamic_array_test.c ../Array/dynamic_array.c -o dynamic_array_test
./dynamic_array_test.exe

Purpose:
Tests the correctness of the Dynamic Array implementation.

Covered scenarios:
- Empty array handling
- Single append
- Multiple appends and resizing
- Out-of-bounds access (value, insert, update, delete)
- Negative index handling
- Insert at front, middle, and end
- Insert vs Update distinction
- Delete front, middle, and last
- Empty after operations and reuse
- Get index / get indexes (including duplicates and missing values)
- Get indexes on empty array
- Stress testing
*/

#include <stdio.h>
#include <stdlib.h>
#include "../Array/dynamic_array.h"

int main(){

    // Test 1: Empty array
    // Verifies that a newly created dynamic array is empty
    // and has size 0 without any operations
    printf("=== Test 1 ===\n\n");

    Dynamic_Array arr = create_dynamic_array();
    printf("Empty?: %s\n", is_empty_dynamic_array(&arr) ? "yes" : "no");
    printf("Size: %d\n\n", get_dynamic_array_length(&arr));

    // Test 2: Single append
    // Verifies that a single append works correctly
    printf("=== Test 2 ===\n\n");

    dynamic_array_append(&arr, 42);
    printf("Array: ");
    print_dynamic_array(&arr);
    printf("\n");
    printf("Value at 0: %d\n", dynamic_array_value(&arr, 0));
    printf("Empty?: %s\n", is_empty_dynamic_array(&arr) ? "yes" : "no");
    printf("Size: %d\n\n", get_dynamic_array_length(&arr));

    // Test 3: Multiple appends and resizing
    // Verifies automatic capacity expansion works correctly
    // and all values are accessible after resizing
    printf("=== Test 3 ===\n\n");

    Dynamic_Array arr2 = create_dynamic_array();
    for(int i = 0; i < 100; i++){
        dynamic_array_append(&arr2, i);
    }

    printf("Size after 100 appends: %d\n", get_dynamic_array_length(&arr2));
    printf("First element: %d\n", dynamic_array_value(&arr2, 0));
    printf("50th element: %d\n", dynamic_array_value(&arr2, 50));
    printf("Last element: %d\n", dynamic_array_value(&arr2, get_dynamic_array_length(&arr2) - 1));

    int errors = 0;
    for(int i = 0; i < 100; i++){
        if(dynamic_array_value(&arr2, i) != i) errors++;
    }
    printf("Errors after 100 appends: %d\n\n", errors);

    // Test 4: Out-of-bounds access
    // Verifies correct error handling when index is out of range
    // for value, insert, update, and delete
    printf("=== Test 4 ===\n\n");

    Dynamic_Array arr3 = create_dynamic_array();
    dynamic_array_append(&arr3, 1);
    dynamic_array_append(&arr3, 2);
    dynamic_array_append(&arr3, 3);

    printf("value at index 10 (out of bounds): ");
    dynamic_array_value(&arr3, 10);
    printf("\n");

    printf("insert at index 10 (out of bounds): ");
    dynamic_array_insert(&arr3, 10, 99);
    printf("\n");

    printf("update at index 10 (out of bounds): ");
    dynamic_array_update(&arr3, 10, 99);
    printf("\n");

    printf("delete at index 10 (out of bounds): ");
    dynamic_array_delete(&arr3, 10);
    printf("\n");

    printf("Size unchanged: %d\n\n", get_dynamic_array_length(&arr3));

    // Test 5: Negative index handling
    // Verifies correct error handling for negative indexes
    printf("=== Test 5 ===\n\n");

    printf("value at index -1: ");
    dynamic_array_value(&arr3, -1);
    printf("\n");

    printf("insert at index -1: ");
    dynamic_array_insert(&arr3, -1, 99);
    printf("\n");

    printf("update at index -1: ");
    dynamic_array_update(&arr3, -1, 99);
    printf("\n");

    printf("delete at index -1: ");
    dynamic_array_delete(&arr3, -1);
    printf("\n");

    printf("Size unchanged: %d\n\n", get_dynamic_array_length(&arr3));

    // Test 6: Insert at front, middle, and end
    // Verifies insertion shifts elements correctly at all positions
    printf("=== Test 6 ===\n\n");

    Dynamic_Array arr4 = create_dynamic_array();
    dynamic_array_append(&arr4, 10);
    dynamic_array_append(&arr4, 20);
    dynamic_array_append(&arr4, 30);

    printf("Before inserts: ");
    print_dynamic_array(&arr4);
    printf("\n");

    dynamic_array_insert(&arr4, 0, 5);
    printf("After insert 5 at front (index 0): ");
    print_dynamic_array(&arr4);
    printf("\n");

    dynamic_array_insert(&arr4, 2, 15);
    printf("After insert 15 at middle (index 2): ");
    print_dynamic_array(&arr4);
    printf("\n");

    dynamic_array_insert(&arr4, get_dynamic_array_length(&arr4), 99);
    printf("After insert 99 at end (index size): ");
    print_dynamic_array(&arr4);
    printf("\n");

    printf("Size: %d\n\n", get_dynamic_array_length(&arr4));

    // Test 7: Insert vs Update
    // Verifies insert increases size while update only changes a value
    printf("=== Test 7 ===\n\n");

    Dynamic_Array arr5 = create_dynamic_array();
    for(int i = 1; i <= 5; i++){
        dynamic_array_append(&arr5, i);
    }

    printf("Before: ");
    print_dynamic_array(&arr5);
    printf("  Size: %d\n", get_dynamic_array_length(&arr5));

    dynamic_array_insert(&arr5, 3, 80);
    printf("After insert 80 at index 3: ");
    print_dynamic_array(&arr5);
    printf("  Size: %d\n", get_dynamic_array_length(&arr5));

    dynamic_array_update(&arr5, 3, 77);
    printf("After update index 3 to 77: ");
    print_dynamic_array(&arr5);
    printf("  Size: %d\n\n", get_dynamic_array_length(&arr5));

    // Test 8: Delete front, middle, and last
    // Verifies deletion shifts elements correctly and updates size
    printf("=== Test 8 ===\n\n");

    Dynamic_Array arr6 = create_dynamic_array();
    for(int i = 1; i <= 6; i++){
        dynamic_array_append(&arr6, i);
    }

    printf("Before deletes: ");
    print_dynamic_array(&arr6);
    printf("\n");

    dynamic_array_delete(&arr6, 0);
    printf("After delete front: ");
    print_dynamic_array(&arr6);
    printf("  Size: %d\n", get_dynamic_array_length(&arr6));

    dynamic_array_delete(&arr6, get_dynamic_array_length(&arr6) / 2);
    printf("After delete middle: ");
    print_dynamic_array(&arr6);
    printf("  Size: %d\n", get_dynamic_array_length(&arr6));

    dynamic_array_delete(&arr6, get_dynamic_array_length(&arr6) - 1);
    printf("After delete last: ");
    print_dynamic_array(&arr6);
    printf("  Size: %d\n\n", get_dynamic_array_length(&arr6));

    // Test 9: Empty after operations and reuse
    // Verifies array can be reused after empty_dynamic_array
    printf("=== Test 9 ===\n\n");

    empty_dynamic_array(&arr6);
    printf("After empty:\n");
    printf("Empty?: %s\n", is_empty_dynamic_array(&arr6) ? "yes" : "no");
    printf("Size: %d\n", get_dynamic_array_length(&arr6));

    dynamic_array_append(&arr6, 100);
    dynamic_array_append(&arr6, 200);
    dynamic_array_append(&arr6, 300);
    printf("After re-append: ");
    print_dynamic_array(&arr6);
    printf("\n");
    printf("Size: %d\n\n", get_dynamic_array_length(&arr6));

    // Test 10: Get index / get indexes
    // Verifies correct index is returned for existing and missing values,
    // and all indexes are returned for duplicate values
    printf("=== Test 10 ===\n\n");

    Dynamic_Array arr7 = create_dynamic_array();
    dynamic_array_append(&arr7, 10);
    dynamic_array_append(&arr7, 20);
    dynamic_array_append(&arr7, 30);
    dynamic_array_append(&arr7, 20);
    dynamic_array_append(&arr7, 40);
    dynamic_array_append(&arr7, 20);

    printf("Array: ");
    print_dynamic_array(&arr7);
    printf("\n");

    printf("Index of 10 (expect 0): %d\n", dynamic_array_get_index(&arr7, 10));
    printf("Index of 20 (expect 1, first occurrence): %d\n", dynamic_array_get_index(&arr7, 20));
    printf("Index of 99 (not found, expect -1): %d\n", dynamic_array_get_index(&arr7, 99));

    Dynamic_Array indexes = dynamic_array_get_indexes(&arr7, 20);
    printf("All indexes of 20 (expect 1 3 5): ");
    print_dynamic_array(&indexes);
    printf("\n");

    Dynamic_Array empty_indexes = dynamic_array_get_indexes(&arr7, 99);
    printf("All indexes of 99 (not found, expect empty): ");
    print_dynamic_array(&empty_indexes);
    printf("\n\n");

    // Test 11: Get indexes on empty array
    // Verifies get_index and get_indexes handle empty arrays correctly
    printf("=== Test 11 ===\n\n");

    Dynamic_Array arr8 = create_dynamic_array();
    printf("get_index on empty array (expect -1): %d\n", dynamic_array_get_index(&arr8, 5));
    Dynamic_Array no_indexes = dynamic_array_get_indexes(&arr8, 5);
    printf("get_indexes on empty array (expect empty): ");
    print_dynamic_array(&no_indexes);
    printf("\n\n");

    // Test 12: Multiple operations
    // Verifies correct behavior under a mix of appends, updates,
    // inserts, index lookups, deletes, and empty in sequence
    printf("=== Test 12 ===\n\n");

    Dynamic_Array arr10 = create_dynamic_array();

    for(int i = 0; i < 100; i++){
        dynamic_array_append(&arr10, i);
    }

    printf("Array before operations: ");
    print_dynamic_array(&arr10);
    printf("  Size: %d\n", get_dynamic_array_length(&arr10));

    dynamic_array_update(&arr10, 0, 1000);
    int index = 2;
    while(index < get_dynamic_array_length(&arr10)){
        dynamic_array_update(&arr10, index, 1000);
        index = index * 2;
    }

    Dynamic_Array powers_of_two = dynamic_array_get_indexes(&arr10, 1000);

    for(int i = 0; i < 100; i++){
        if(i % 30 == 0){
            dynamic_array_insert(&arr10, i, 3000);
        }
    }

    Dynamic_Array divisible_by_30 = dynamic_array_get_indexes(&arr10, 3000);

    printf("Array after updates and inserts: ");
    print_dynamic_array(&arr10);
    printf("  Size: %d\n", get_dynamic_array_length(&arr10));

    printf("Indexes updated to 1000 (powers of two): ");
    print_dynamic_array(&powers_of_two);
    printf("\n");
    printf("Indexes inserted with 3000 (divisible by 30): ");
    print_dynamic_array(&divisible_by_30);
    printf("\n");

    for(int i = 0; i < 40; i++){
        dynamic_array_delete(&arr10, 0);
    }

    printf("After deleting first 40 elements: ");
    print_dynamic_array(&arr10);
    printf("  Size: %d\n", get_dynamic_array_length(&arr10));

    empty_dynamic_array(&arr10);
    printf("After empty: ");
    print_dynamic_array(&arr10);
    printf("  Size: %d\n", get_dynamic_array_length(&arr10));
    printf("Empty?: %s\n\n", is_empty_dynamic_array(&arr10) ? "yes" : "no");

    // Test 13: Stress test
    // Verifies correct behavior under heavy usage with
    // large-scale appends, random-access reads, updates, and deletes
    printf("=== Test 13 ===\n\n");

    Dynamic_Array arr9 = create_dynamic_array();
    for(int i = 0; i < 10000; i++){
        dynamic_array_append(&arr9, i);
    }

    printf("Size after 10000 appends: %d\n", get_dynamic_array_length(&arr9));
    printf("First element: %d\n", dynamic_array_value(&arr9, 0));
    printf("Last element: %d\n", dynamic_array_value(&arr9, get_dynamic_array_length(&arr9) - 1));

    errors = 0;
    for(int i = 0; i < 10000; i++){
        if(dynamic_array_value(&arr9, i) != i) errors++;
    }
    printf("Read errors: %d\n", errors);

    for(int i = 0; i < 10000; i++){
        dynamic_array_update(&arr9, i, i * 2);
    }

    errors = 0;
    for(int i = 0; i < 10000; i++){
        if(dynamic_array_value(&arr9, i) != i * 2) errors++;
    }
    printf("Update errors: %d\n", errors);

    for(int i = 0; i < 10000; i++){
        dynamic_array_delete(&arr9, 0);
    }

    printf("Size after 10000 deletes: %d\n", get_dynamic_array_length(&arr9));
    printf("Empty?: %s\n", is_empty_dynamic_array(&arr9) ? "yes" : "no");

    destroy_dynamic_array(&arr);
    destroy_dynamic_array(&arr2);
    destroy_dynamic_array(&arr3);
    destroy_dynamic_array(&arr4);
    destroy_dynamic_array(&arr5);
    destroy_dynamic_array(&arr6);
    destroy_dynamic_array(&arr7);
    destroy_dynamic_array(&arr8);
    destroy_dynamic_array(&arr9);
    destroy_dynamic_array(&arr10);
    destroy_dynamic_array(&indexes);
    destroy_dynamic_array(&empty_indexes);
    destroy_dynamic_array(&no_indexes);
    destroy_dynamic_array(&powers_of_two);
    destroy_dynamic_array(&divisible_by_30);

    return 0;
}

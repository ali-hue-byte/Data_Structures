# Algorithms

### Description

A collection of utility functions that combine multiple data structures from the library to solve common algorithmic problems.

### Functions

| Functions | Description | Time complexity |
|-----------|-------------|-----------------|
| sort_dynamic_array(Dynamic_Array *d_arr) | Sorts a dynamic array using a BST (duplicates are removed). Caller is responsible for freeing the returned array's data (`free(array.data)`). | O(n log(n)) |
| words_frequency(char *text) | Counts the frequency of each word in a given text. Returns a Hash Table with words as keys and their frequency as values. | O(n) |
| remove_duplicates_dynamic_array(Dynamic_Array *d_arr) | Removes duplicates from a dynamic array while preserving the original order. Uses a Hash Table to track seen values. Caller is responsible for freeing the returned array's data (`free(array.data)`). | O(n) |
| Heap_sort(Dynamic_Array *d_array, bool ascending) | Sorts a dynamic array in ascending or descending order using a heap. Duplicates are preserved. The caller is responsible for freeing the returned array's data (`free(array.data)`). | O(n log(n)) |

### Example

```c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ds.h"

int main(void) {

    // sort_dynamic_array
    Dynamic_Array arr = create_dynamic_array();
    dynamic_array_append(&arr, 5);
    dynamic_array_append(&arr, 3);
    dynamic_array_append(&arr, 8);
    dynamic_array_append(&arr, 3);
    dynamic_array_append(&arr, 1);
    dynamic_array_append(&arr, 5);
    dynamic_array_append(&arr, 9);
    dynamic_array_append(&arr, 1);

    printf("Before sort: ");
    print_dynamic_array(&arr); // 5 3 8 3 1 5 9 1
    printf("\n");

    Dynamic_Array sorted = sort_dynamic_array(&arr);
    printf("After sort (duplicates removed): ");
    print_dynamic_array(&sorted); // 1 3 5 8 9
    printf("\n");
    free(sorted.data);

    // remove_duplicates_dynamic_array
    printf("\n");
    Dynamic_Array no_dup = remove_duplicates_dynamic_array(&arr);
    printf("After remove duplicates (order preserved): ");
    print_dynamic_array(&no_dup); // 5 3 8 1 9
    printf("\n");
    free(no_dup.data);

    free(arr.data);

    // words_frequency
    printf("\n");
    char text[] = "the cat sat on the mat the cat is on the mat";
    Hash_Table freq = words_frequency(text);
    printf("Word frequencies:\n");
    print_Hash_Table(&freq); // the:4 cat:2 sat:1 on:2 mat:2 is:1


    // Heap sort (duplicates are preserved)
    printf("\n");
    Dynamic_Array d_array = create_dynamic_array();
    dynamic_array_append(&d_array, 2);
    dynamic_array_append(&d_array, 3);
    dynamic_array_append(&d_array, 1);
    dynamic_array_append(&d_array, 2);
    dynamic_array_append(&d_array, 4);
    dynamic_array_append(&d_array, 0);
    dynamic_array_append(&d_array, -4);
    dynamic_array_append(&d_array, 4);
    dynamic_array_append(&d_array, 3);
    dynamic_array_append(&d_array, 4);
    printf("Before sorting: "); 
    print_dynamic_array(&d_array); // 2 3 1 2 4 0 -4 4 3 4 
    printf("\nAscending: ");
    Dynamic_Array ascending = Heap_sort(&d_array, true);
    print_dynamic_array(&ascending); // -4 0 1 2 2 3 3 4 4 4 
    printf("\nDescending: ");
    Dynamic_Array descending = Heap_sort(&d_array, false);
    print_dynamic_array(&descending); // 4 4 4 3 3 2 2 1 0 -4 

    return 0;
}

```

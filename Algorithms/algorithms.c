/* This file provides utility functions that combine multiple data structures
   from the library to solve common algorithmic problems.

   Functions:
   - sort_dynamic_array: Sorts a dynamic array using a BST (duplicates are removed)
   - remove_duplicates_dynamic_array: Removes duplicates from a dynamic array while preserving order
   - words_frequency: Counts the frequency of each word in a given text
   - Heap_sort: sorts a dynamic array using a heap (duplicates are not removed)

   Note: Functions that return a Dynamic_Array require the caller to free 
   the returned array's data (free(array.data)) when done.
*/

#include "../ds.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Sorts a dynamic array using a BST (duplicates are removed)
// Caller is responsible for freeing the returned array's data (free(array.data))
Dynamic_Array sort_dynamic_array(Dynamic_Array *d_arr){
    BST bst = create_BST();
    for(int i = 0; i < get_dynamic_array_length(d_arr); i++){
        BST_insert_silent(&bst, dynamic_array_value(d_arr, i));
    }
    Dynamic_Array result = BST_get_values(&bst);
    empty_BST(&bst);
    return result;
}

// Counts the frequency of each word in a given text
// Returns a Hash Table with words as keys and their frequency as values
Hash_Table words_frequency(char *text){
    Hash_Table h_t = create_hash_table();
    char *word = strtok(text, " .,!?");
    
    while(word != NULL){
        // Convert word to lowercase for case-insensitive counting
        for(int i = 0; word[i]; i++){
            word[i] = tolower(word[i]);
        }
        if(Key_in_Hash_Table(&h_t, word)){
            Hash_Table_update(&h_t, word, Hash_Table_get(&h_t, word)+1);
        }else{
            Hash_Table_add(&h_t, word, 1);
        }
        word = strtok(NULL, " .,!?");
    }
    return h_t;
}

// Removes duplicates from a dynamic array while preserving the original order
// Uses a Hash Table to track seen values
// Caller is responsible for freeing the returned array's data (free(array.data))
Dynamic_Array remove_duplicates_dynamic_array(Dynamic_Array *d_arr){
    Hash_Table h_t = create_hash_table();
    Dynamic_Array new_array = create_dynamic_array();
    for(int i = 0; i < get_dynamic_array_length(d_arr); i++){
        int value = dynamic_array_value(d_arr, i);
        char key[20];
        snprintf(key, sizeof(key), "%d", value); // Convert int to string for hash table key
        if(!Key_in_Hash_Table(&h_t, key)) {
            Hash_Table_add(&h_t, key, 1);
            dynamic_array_append(&new_array, value); // Only add if not seen before
        }
    }
    return new_array;
}

// Sorts a dynamic array without removing duplicates
// Uses a heap-based sorting algorithm
// Caller is responsible for freeing the returned array's data: free(array.data)

Dynamic_Array Heap_sort(Dynamic_Array *d_array, bool ascending){

    // For ascending order, use a Min Heap so the smallest element is extracted each time.
    // For descending order, use a Max Heap so the largest element is extracted each time.
    
    Heap heap = create_heap(!ascending);

    Dynamic_Array result = create_dynamic_array();

    int size = get_dynamic_array_length(d_array);

    // Insert all elements into the heap.
    for(int i = 0; i < size; i++){
        heap_add(&heap, dynamic_array_value(d_array, i));
    }

    // Extract elements from the heap in sorted order.
    for(int i = 0; i < size; i++){
        dynamic_array_append(&result, heap_extract(&heap));
    }

    return result;
}

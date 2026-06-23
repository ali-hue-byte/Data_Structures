/*This file provides necessary functions to implement a heap using dynamic array.

  A heap is a tree based data structure, where each value has 2 children (left and right).
  Unlike BST, the heap is stored as an array. For a parent at index i, its children's 
  indexes are:
   - n = 2*i + 1 for left child
   - n = 2*i + 2 for right child
  And each value's parent is at index i = (n - 1)/2, with n the index of the child 

  The heap divides into 2 types :
   - Max heap: each parent is bigger than its children
   - Min heap: each parent is smaller than its children

  The heap provides fast access to minimum or maximum value, which can be used to sort an array,
  scheduling tasks by priority, finding the k largest or smallest elements in a dataset, 
  or implementing Dijkstra's shortest path algorithm in a graph.

  Possible operations :
  add: Add a new value to the heap at corresponding place
  peek: Get the root value, which is the maximum or minimum based on heap type
  extract: Remove and return the root value
*/


#include "Heap.h"
#include <stdbool.h>


// Creates a new heap
Heap create_heap(bool is_max){
    Heap heap;
    heap.is_max = is_max;
    heap.heap_arr = create_dynamic_array();
    return heap;
}

// Adds a new value to the heap, and places it to its corresponding position based on the heap property
void heap_add(Heap *heap, int value){
    if(is_empty_heap(heap)){
        dynamic_array_append(&heap->heap_arr, value);
        return;
    }

    int new_index = get_dynamic_array_length(&heap->heap_arr); 
    int parent_index = (new_index - 1) / 2;

    int parent_value = dynamic_array_value(&heap->heap_arr, parent_index);
    int new_value = value;
    
    dynamic_array_append(&heap->heap_arr, value); // Adds the value to the end of the heap array
    bool operation;
    if(heap->is_max) operation = parent_value < new_value ; // Max heap
    else operation = parent_value > new_value; // Min heap
    
    // Bubbles the new value up till the heap property is satisfied
    while((new_index > 0) && (operation)){
        // Switch value with parent
        dynamic_array_update(&heap->heap_arr, parent_index, new_value);
        dynamic_array_update(&heap->heap_arr, new_index, parent_value);

        new_index = parent_index;

        parent_index = (parent_index - 1) / 2;
        parent_value = dynamic_array_value(&heap->heap_arr, parent_index);

        if(heap->is_max) operation = parent_value < new_value ;
        else operation = parent_value > new_value;

    }
}

// Returns the value of the first element of the heap (minimum or maximum)
int heap_peek(Heap *heap){
    if(is_empty_heap(heap)){
        printf("Heap is empty: ");
        return -1;
    }
    return  dynamic_array_value(&heap->heap_arr, 0);
}

// Returns and removes the first element of the heap (minimum or maximum)
int heap_extract(Heap *heap){
    if(is_empty_heap(heap)){
        printf("Heap is empty: ");
        return -1;
    }

    int value = dynamic_array_value(&heap->heap_arr, 0);
    int last = dynamic_array_value(&heap->heap_arr, get_dynamic_array_length(&heap->heap_arr) - 1);
    dynamic_array_update(&heap->heap_arr, 0, last);
    heap->heap_arr.size--;
    if(is_empty_heap(heap)){
        return value;
    }
    int parent_index = 0; 
    int swap = parent_index;
    
    while(true){
        
        bool left = false;
        bool right = false;
        int left_child_index = 2*parent_index+1;
        int right_child_index = 2*parent_index+2;
        int parent_value = dynamic_array_value(&heap->heap_arr, parent_index);

        if(left_child_index < get_dynamic_array_length(&heap->heap_arr)){ // Left child exists
            int left_child_value = dynamic_array_value(&heap->heap_arr, left_child_index);
            // Max heap: checks if left child is bigger than parent
            if (heap->is_max && left_child_value > parent_value) swap = left_child_index;
            // Min heap: checks if left child is smaller than parent
            else if (!heap->is_max && left_child_value < parent_value) swap = left_child_index;
            // Heap property satisfied for left child :
            // - Max heap: parent bigger than left child
            // - Min heap: parent smaller than left child
            else left = true; 
        }else left = true; // Left child doesn't exist

        if(right_child_index < get_dynamic_array_length(&heap->heap_arr)){ // Right child exists
            int right_child_value = dynamic_array_value(&heap->heap_arr, right_child_index);
            // Max heap: checks if the right child is bigger than the largest value between the parent and the left child
            if (heap->is_max && right_child_value > dynamic_array_value(&heap->heap_arr, swap)) swap = right_child_index;
            // Min heap: checks if the right child is smaller than the smallest value between the parent and the left child
            else if (!heap->is_max && right_child_value < dynamic_array_value(&heap->heap_arr, swap)) swap = right_child_index;
            // Heap property satisfied for right child :
            // - Max heap: parent bigger than right child
            // - Min heap: parent smaller than right child
            else right = true;
        }else right = true; // Right child doesn't exist

        if(left && right) break;
        int swap_value = dynamic_array_value(&heap->heap_arr, swap); 
        // Swaps parent value with biggest child
        dynamic_array_update(&heap->heap_arr, parent_index, swap_value);
        dynamic_array_update(&heap->heap_arr, swap, parent_value);        
        parent_index = swap;

    }

    return value;

    
}

// Checks if the heap is empty
bool is_empty_heap(Heap *heap){
    return is_empty_dynamic_array(&heap->heap_arr);
}

// Returns the number of elements in the heap
int heap_length(Heap *heap){
    return get_dynamic_array_length(&heap->heap_arr);
}

// Prints the heap
void print_heap(Heap *heap){
    print_dynamic_array(&heap->heap_arr);
}

// Empties the heap
void empty_heap(Heap *heap){
    empty_dynamic_array(&heap->heap_arr);
}

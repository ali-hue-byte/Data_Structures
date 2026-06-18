# Dynamic array

## Description

Dynamic array is an index based data structure, where elements are stored in order and accessed using their index. Unlike a static array, 
it can automatically resize itself when its capacity is reached.
In reality it is just a sequence of memory locations, where data is stored. 

## How it works

Under the hood, the array itself is just a pointer to its first element. The 'index' isn't magic — it's a shift in memory address: 
arr[i] is the same as *(arr + i), meaning 'move i positions forward from the start, then read what's there'.
When the array is full, a new larger block of memory is allocated (typically double the previous capacity, to keep future resizes
infrequent), and all elements are copied to it, then the old block is freed.

## Operations

| Function | Description | Time complexity |
|----------|-------------|-----------------|
| create_dynamic_array | Creates a new dynamic array. | O(1) |
| dynamic_array_append | Adds a new value to the end of the array. If the array is full, it first doubles its capacity by allocating a new, larger block of memory and copying the existing elements over.| - O(1): if the array is not full <br> - O(n): if the array is full (must copy all elements to new allocated memory)|
| dynamic_array_value | Returns the value at a given index. | O(1) |
| dynamic_array_insert | Adds an element to a given index. If necessary, the array capacity is increased, a new block of memory is allocated, the existing elements are copied, and the remaining elements are shifted to make room for the new value. | O(n) |
| dynamic_array_update | Updates a value at a given index. | O(1) |
| dynamic_array_delete | Deletes an element at a given index by copying all existing elements, except the one at the specified index, into a new block of memory. | O(n) |
| get_dynamic_array_length | Returns the number of elements in the dynamic array. | O(1) |
| print_dynamic_array | Prints the dynamic array. | O(n) |
| is_empty_dynamic_array | Checks if array is empty. | O(1) |
| empty_dynamic_array | Resets the array size to 0 without freeing its allocated memory, allowing it to be reused. | O(1) |
|destroy_dynamic_array | Frees the allocated memory of the dynamic array. Used when the array is no longer needed. | O(1) |

## Example

```c

#include "dynamic_array.h"
#include <stdio.h>

int main(){
    Dynamic_Array arr = create_dynamic_array();

    dynamic_array_append(&arr, 10);
    dynamic_array_append(&arr, 20);
    dynamic_array_append(&arr, 30);

    print_dynamic_array(&arr); // 10 20 30
    printf("\n");

    dynamic_array_insert(&arr, 1, 99);
    print_dynamic_array(&arr); // 10 99 20 30
    printf("\n");

    dynamic_array_update(&arr, 0, 5);
    print_dynamic_array(&arr); // 5 99 20 30
    printf("\n");
    
    dynamic_array_delete(&arr, 2);
    print_dynamic_array(&arr); // 5 99 30

    printf("\nLength: %d\n", get_dynamic_array_length(&arr)); // 3

    return 0;
}

```

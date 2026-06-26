/* This file provides necessary functions to implement a dynamic array
   Possible operations :
   - append: Add an item at the end 
   - insert: Add an item at a given index
   - update: Change an element at a given index
   - delete: Removes an element at a given index
*/



#include <stdio.h>
#include "dynamic_array.h"
#include <stdlib.h>
#include <stdbool.h>

// Creates a new dynamic array
Dynamic_Array create_dynamic_array(){
    Dynamic_Array arr;
    arr.size = 0 ;
    arr.capacity = 4;
    arr.data = malloc(4 * sizeof(int));
    return arr;
}

// Adds a new element to the rear of the dynamic array
void dynamic_array_append(Dynamic_Array *d_array, int value){
    if(d_array->size == d_array->capacity){
        int new_capacity = (d_array->capacity == 0) ? 1 : d_array->capacity * 2;
        int *data = malloc(new_capacity*sizeof(int)); // Provides more memory if the array is full

        for (int i = 0; i < d_array->size; i++) {
            *(data + i) = *(d_array->data + i); // Moves the data to new allocated memory
        }

        free(d_array->data);
       
        d_array->data = data; // Updates the data pointer to the new memory block
        d_array->capacity = new_capacity;
    } 
    *(d_array->data + d_array->size) = value; // Adds the value at the end of the array
    d_array->size++;
}

// Returns the value at a given index
int dynamic_array_value(Dynamic_Array *d_array, int index){
      if (index >= d_array->size || index < 0){
        printf("Index out of range: %d", index);
        return -1;
      }
      return *(d_array->data + index); 
}

// Adds an element to a given index
void dynamic_array_insert(Dynamic_Array *d_array, int index, int value){
    if (index > d_array->size || index < 0){
        printf("Index out of range: %d", index);
        return;
    }
    
    // Only realloc if full
    if(d_array->size == d_array->capacity){
        int new_capacity = d_array->capacity == 0 ? 1 : d_array->capacity * 2;
        int *new_data = realloc(d_array->data, new_capacity * sizeof(int));
        d_array->data = new_data;
        d_array->capacity = new_capacity;
    }

    // Shift in place — no malloc needed
    for(int i = d_array->size; i > index; i--){
        d_array->data[i] = d_array->data[i - 1];
    }
    d_array->data[index] = value;
    d_array->size++;
}

// Changes a value at a given index
void dynamic_array_update(Dynamic_Array *d_array, int index, int value){
    if (index >= d_array->size || index < 0){
        printf("Index out of range: %d", index);
        return;
    }
    *(d_array->data + index) = value; 
}

// Deletes an element at a given index
void dynamic_array_delete(Dynamic_Array *d_array, int index){
    if (index >= d_array->size || index < 0){
        printf("Index out of range: %d", index);
        return;
    }
    for (int i = index; i < d_array->size - 1; i++){
        d_array->data[i] = d_array->data[i + 1];
    }
    d_array->size--;
}

// Returns the number of elements in the dynamic array
int get_dynamic_array_length(Dynamic_Array *d_array){
    return d_array->size;
}

// Prints the dynamic array
void print_dynamic_array(Dynamic_Array *d_array){
    if (is_empty_dynamic_array(d_array)){
        printf("Dynamic array is empty ");
        return;
    }
    for(int i = 0; i<d_array->size; i++){
        printf("%d ", *(d_array->data + i)); // Prints element at index i
    }
}

// Checks if array is empty
bool is_empty_dynamic_array(Dynamic_Array *d_array){
    return (d_array->size == 0);
}

// Marks the array as empty without freeing its allocated memory
void empty_dynamic_array(Dynamic_Array *d_array){
    d_array->size = 0;
}

// Frees the allocated memory of the dynamic array. Used when the array is no longer needed.
void destroy_dynamic_array(Dynamic_Array *d_array) {
    free(d_array->data); // Frees the internal data array
    d_array->data = NULL;
    d_array->size = 0;
    d_array->capacity = 0;
}

// Returns the index of the first occurrence of a given value
int dynamic_array_get_index(Dynamic_Array *d_array, int value){
    for(int i = 0; i < d_array->size; i++){
        if(*(d_array->data + i) == value){
            return i;
        }
    }
    return -1;
}

// Returns a dynamic array of indexes with that value
Dynamic_Array dynamic_array_get_indexes(Dynamic_Array *d_array, int value){
    Dynamic_Array arr = create_dynamic_array();
    for(int i = 0; i < d_array->size; i++){
        if(*(d_array->data + i) == value){
            dynamic_array_append(&arr, i);
        }
    }
    return arr;
}

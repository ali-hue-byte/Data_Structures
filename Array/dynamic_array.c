#include <stdio.h>
#include "dynamic_array.h"
#include <stdlib.h>
#include <stdbool.h>

void dynamic_array_append(Dynamic_Array *d_array, int value){
    if(d_array->size == d_array->capacity){
        int new_capacity = (d_array->capacity == 0) ? 1 : d_array->capacity * 2;
        int *data = malloc(new_capacity*sizeof(int));

        for (int i = 0; i<d_array->size; i++) {
            *(data + i) = *(d_array->data + i);
        }

        free(d_array->data);
        
        d_array->data = data;
        
        d_array->capacity = new_capacity;
    } 
    *(d_array->data + d_array->size) = value;
    d_array->size++;
}

int dynamic_array_value(Dynamic_Array *d_array, int index){
      if (index >= d_array->size || index < 0){
        printf("Index out of range");
        return 0;
      }
      return *(d_array->data + index);
}

void dynamic_array_insert(Dynamic_Array *d_array, int index, int value){
    if (index > d_array->size || index < 0){
        printf("Index out of range");
        return;
    }
    int capacity;
    
    if(d_array->size == d_array->capacity){
        capacity = (d_array->capacity == 0) ? 1 : d_array->capacity * 2;
    } else{
        capacity = (d_array->capacity == 0) ? 1 : d_array->capacity;
    }

    int *data = malloc(capacity*sizeof(int));
    for (int i = 0; i < index; i++)
    {
        *(data + i) = *(d_array->data + i);
    }

    for (int i = d_array->size; i > index; i--)
    {
        *(data + i) = *(d_array->data + i - 1);
    }

    *(data + index) = value;

    free(d_array->data);
        
    d_array->data = data;
        
    d_array->capacity = capacity;
    d_array->size++;
}

void dynamic_array_update(Dynamic_Array *d_array, int index, int value){
    if (index >= d_array->size || index < 0){
        printf("Index out of range");
        return;
    }
    *(d_array->data + index) = value;
}

void dynamic_array_delete(Dynamic_Array *d_array, int index){
    if (index >= d_array->size || index < 0){
        printf("Index out of range");
        return;
    }
    int *data = malloc(d_array->capacity*sizeof(int));
    for (int i = 0; i < index; i++)
    {
        *(data + i) = *(d_array->data + i);
    }
    

    for (int i = index; i < d_array->size - 1; i++){
        *(data + i) = *(d_array->data + i + 1);
    }
    
    free(d_array->data);
        
    d_array->data = data;
    d_array->size--;
}

int get_dynamic_array_length(Dynamic_Array *d_array){
    return d_array->size;
}

void print_dynamic_array(Dynamic_Array *d_array){
    if (is_empty_dynamic_array(d_array)){
        printf("Dynamic array is empty ");
        return;
    }
    for(int i = 0; i<d_array->size; i++){
        printf("%d ", *(d_array->data + i));
    }
}

bool is_empty_dynamic_array(Dynamic_Array *d_array){
    return (d_array->size == 0);
}

void empty_dynamic_array(Dynamic_Array *d_array){
    d_array->size = 0;
}

Dynamic_Array creat_dynamic_array(){
    Dynamic_Array arr;
    arr.size = 0 ;
    arr.capacity = 4;
    arr.data = malloc(4 * sizeof(int));
    return arr;
}
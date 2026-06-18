#ifndef DARRAY_H
#define DARRAY_H

#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} Dynamic_Array;

void dynamic_array_append(Dynamic_Array *d_array, int value);
int dynamic_array_value(Dynamic_Array *d_array, int index);
void dynamic_array_insert(Dynamic_Array *d_array, int index, int value);
void dynamic_array_update(Dynamic_Array *d_array, int index, int value);
void dynamic_array_delete(Dynamic_Array *d_array, int index);
int get_dynamic_array_length(Dynamic_Array *d_array);
Dynamic_Array create_dynamic_array();
void empty_dynamic_array(Dynamic_Array *d_array);
void print_dynamic_array(Dynamic_Array *d_array);
bool is_empty_dynamic_array(Dynamic_Array *d_array);
void destroy_dynamic_array(Dynamic_Array *d_array);

#endif

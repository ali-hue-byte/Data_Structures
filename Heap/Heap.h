#ifndef HEAP_H
#define HEAP_H



#include "../Array/dynamic_array.h"
typedef struct {
    Dynamic_Array heap_arr;
    bool is_max;
} Heap;

Heap create_heap(bool is_max);
void heap_add(Heap *heap, int value);
int heap_peek(Heap *heap);
int heap_extract(Heap *heap);
bool is_empty_heap(Heap *heap);
int heap_length(Heap *heap);
void print_heap(Heap *heap);
void empty_heap(Heap *heap);

#endif

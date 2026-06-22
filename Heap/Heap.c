#include "Heap.h"
#include <stdbool.h>



Heap create_heap(bool is_max){
    Heap heap;
    heap.is_max = is_max;
    heap.heap_arr = create_dynamic_array();
    return heap;
}

void heap_add(Heap *heap, int value){
    if(is_empty_heap(heap)){
        dynamic_array_append(&heap->heap_arr, value);
        return;
    }

    int new_index = get_dynamic_array_length(&heap->heap_arr); 
    int parent_index = (new_index - 1) / 2;

    int parent_value = dynamic_array_value(&heap->heap_arr, parent_index);
    int new_value = value;
    
    dynamic_array_append(&heap->heap_arr, value);
    bool operation;
    if(heap->is_max) operation = parent_value < new_value ;
    else operation = parent_value > new_value;

    while((new_index > 0) && (operation)){
        dynamic_array_update(&heap->heap_arr, parent_index, new_value);
        dynamic_array_update(&heap->heap_arr, new_index, parent_value);

        new_index = parent_index;

        parent_index = (parent_index - 1) / 2;
        parent_value = dynamic_array_value(&heap->heap_arr, parent_index);
        if(heap->is_max) operation = parent_value < new_value ;
        else operation = parent_value > new_value;

    }
}

int heap_peek(Heap *heap){
    if(is_empty_heap(heap)){
        printf("Heap is empty: ");
        return -1;
    }
    return  dynamic_array_value(&heap->heap_arr, 0);
}

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
        if(left_child_index < get_dynamic_array_length(&heap->heap_arr)){
            int left_child_value = dynamic_array_value(&heap->heap_arr, left_child_index);
            if (heap->is_max && left_child_value > parent_value) swap = left_child_index;
            else if (!heap->is_max && left_child_value < parent_value) swap = left_child_index;
            else left = true;
        }else left = true;

        if(right_child_index < get_dynamic_array_length(&heap->heap_arr)){
            int right_child_value = dynamic_array_value(&heap->heap_arr, right_child_index);
            if (heap->is_max && right_child_value > dynamic_array_value(&heap->heap_arr, swap)) swap = right_child_index;
            else if (!heap->is_max && right_child_value < dynamic_array_value(&heap->heap_arr, swap)) swap = right_child_index;
            else right = true;
        }else right = true;

        if(left && right) break;
        int swap_value = dynamic_array_value(&heap->heap_arr, swap);
        dynamic_array_update(&heap->heap_arr, parent_index, swap_value);
        dynamic_array_update(&heap->heap_arr, swap, parent_value);        
        parent_index = swap;

    }

    return value;

    
}

bool is_empty_heap(Heap *heap){
    return is_empty_dynamic_array(&heap->heap_arr);
}

int heap_length(Heap *heap){
    return get_dynamic_array_length(&heap->heap_arr);
}

void print_heap(Heap *heap){
    print_dynamic_array(&heap->heap_arr);
}

void empty_heap(Heap *heap){
    empty_dynamic_array(&heap->heap_arr);
}

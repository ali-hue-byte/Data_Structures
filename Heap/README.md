# Heap

## Description


---
## How does it work



---
## Operations

| Function | Description | Time complexity |
|----------|-------------|-----------------|
| create_heap(bool is_max) | Creates a new heap. if is_max is true, a max heap is created, otherwise a min heap is created. | O(1) |
| heap_add(Heap *heap, int value) | Adds a new value to the heap, and places it to its corresponding position based on the heap property. | O(log(n)) |
| heap_peek(Heap *heap) | Returns the value of the first element of the heap (minimum or maximum). | O(1) |
| heap_extract(Heap *heap) | Returns and removes the root of the heap (minimum or maximum), then restructures it to maintain the heap property. | O(log(n)) |
| is_empty_heap(Heap *heap) | Checks if the heap is empty. | O(1) |
| heap_length(Heap *heap) | Returns the number of elements in the heap. | O(1) |
| print_heap(Heap *heap) | Prints the heap. | O(n) |
| empty_heap(Heap *heap) | Empties the heap. | O(1) |
| destroy_heap(Heap *heap) | Frees the allocated memory of the heap. Used when the array is no longer needed. | O(1) |

---
## Example

```c

#include "Heap/Heap.h"
#include <stdio.h>

int main(void) {

    // Max heap
    Heap max_heap = create_heap(true);

    heap_add(&max_heap, 10);
    heap_add(&max_heap, 5);
    heap_add(&max_heap, 20);
    heap_add(&max_heap, 3);
    heap_add(&max_heap, 15);

    printf("Max heap: ");
    print_heap(&max_heap); // 20 15 10 3 5  
    printf("\n");

    printf("Peek: %d\n", heap_peek(&max_heap)); // 20
    printf("After peek: ");
    print_heap(&max_heap); // 20 15 5 10 3
    printf("\n");
    printf("Size: %d\n", heap_length(&max_heap)); // 5


    printf("Extract: %d\n", heap_extract(&max_heap)); // 20
    printf("After extract: ");
    print_heap(&max_heap); // 15 5 10 3
    printf("\n");
    printf("Size: %d\n", heap_length(&max_heap)); // 4

    empty_heap(&max_heap);
    printf("Empty? %s\n", is_empty_heap(&max_heap) ? "yes" : "no"); // yes

    // Min heap
    Heap min_heap = create_heap(false);

    heap_add(&min_heap, 10);
    heap_add(&min_heap, 5);
    heap_add(&min_heap, 20);
    heap_add(&min_heap, 3);
    heap_add(&min_heap, 15);

    printf("\nMin heap: ");
    print_heap(&min_heap); // 3 5 20 10 15  
    printf("\n");

    printf("Peek: %d\n", heap_peek(&min_heap)); // 3
    printf("Extract: %d\n", heap_extract(&min_heap)); // 3
    printf("After extract: ");
    print_heap(&min_heap); // 5 10 20 15
    printf("\n");

    destroy_heap(&max_heap);
    destroy_heap(&min_heap);

    return 0;
}

```

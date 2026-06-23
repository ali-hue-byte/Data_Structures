# Heap

## Description
Heap is a data structure represented by a tree, and stored as an array. Each value has 2 children (left and right).
Unlike a BST, the heap does not store elements in sorted order, it only guarantees that the root is always the maximum or minimum value, depending on the heap type.

---
## How does it work

### Structure
The heap is implemented using the dynamic array. To simulate the tree structure, children are accessed using index arithmetic instead of pointers.
Each value has a left child at index `2*i + 1` and a right child at index `2*i + 2`, and a parent at index `(i - 1) / 2`. The root is the only value without a parent, and leaves are the only values without children. 

### Heap property

#### - Max heap
The max heap is a heap where each parent is bigger than its children. as a result of this property, the root is always the maximum value.

#### - Min heap
The min heap is a heap where each parent is smaller than its children. as a result of this property, the root is always the minimum value.

### Adding values
A new value is added at the end of the array, which corresponds to adding a new leaf in the tree representation. It is repeatedly compared with its parent, and swapped when necessary, based on the heap type. The new value is bubbled up till the heap property is satisfied.

### Extracting
After extracting the root, the last element in the array is moved to the root position. It is repeatedly compared with its children, and swapped when necessary with the corresponding child, depending on the type of the heap. The value is bubbled down till the heap property is satisfied.

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
## Visualisation of heaps used in the example

### Max heap

#### Array representation

<img width="379" height="124" alt="image" src="https://github.com/user-attachments/assets/3d5be0b9-15ca-4f30-8155-5f46597218cc" />


#### Tree representation 

<img width="1429" height="280" alt="image" src="https://github.com/user-attachments/assets/419680bb-daa5-4a9b-ab78-e1489a40b17b" />



### Min heap

#### Array representation

<img width="384" height="139" alt="image" src="https://github.com/user-attachments/assets/54b8dd06-6906-4e7c-9562-5547aa9b16d2" />


#### Tree representation

<img width="1751" height="329" alt="image" src="https://github.com/user-attachments/assets/9dcbdfda-7019-43e3-a595-7047f48e6e9e" />


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

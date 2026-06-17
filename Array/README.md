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
| dynamic_array_append | Adds a new value to the end of the array. If the array is full, it first doubles its capacity by allocating a new, larger block of memory and copying the existing elements over.| - O(1): if the array is not full <br> - O(n): if the array is full (must copy all elements to new allocated memory)|

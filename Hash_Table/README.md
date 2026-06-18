# Hash Table

## Description

A hash table is a data structure that stores key-value pairs and allows fast insertion, searching, and deletion based on a key, 
instead of relying on position like an array does. In this implementation, it's built using an array combined with linked 
lists to handle collisions (a technique called separate chaining).

## How it works



## Operations

| Function | Description | Time complexity |
|----------|-------------|-----------------|
| Hash_function | Transforms a key to a valid index for the hash table. | O(k), where k is the length of the key |
| create_hash_table | Creates a new hash table. | O(1) |
| is_empty_hash_table | Checks if the Hash Table is empty. | O(1) |
| Key_in_Hash_Table | Checks if a key is in the Hash Table. | - O(1): best case, if the bucket is empty, or the key is the first element in the linked list. <br> - O(n): in worst case, all n elements hash to the same index, so you traverse the entire linked list <br> - Average case: O(1). |
| Hash_Table_add | If necessary, it allocates a new memory block to the hash table, rehashes all elements, and copies them from old array to new one, with their new indexes. Then inserts the new key-value pair to its appropriate index in the array, by setting it's next to the previous head of the linked list at that index, and changing the head of the chain to the new pair. | - O(1): if the table isn't full. <br> - O(n): when the table must be resized and all elements have to be rehashed and copied.  |
| Hash_Table_get | Returns the value of a given key. | - O(1): best case, if the bucket is empty, or the key is the first element in the linked list. <br> - O(n): in worst case, all n elements hash to the same index, so you traverse the entire linked list <br> - Average case: O(1). |  
| Hash_Table_delete | Deletes a key-value pair from the Hash_Table. | - O(1): best case, if the bucket is empty, or the key is the first element in the linked list. <br> - O(n): in worst case, all n elements hash to the same index, so you traverse the entire linked list <br> - Average case: O(1). |
| Hash_Table_empty | Frees all nodes in the hash table and resets it to empty. | O(n) |
| print_Hash_Table | Prints the hash table. | O(n) |
| Hash_Table_size | Returns the number of elements in the Hash Table. | O(1) |
| Hash_Table_update | Updates the value associated with a given key. |  - O(1): best case, if the bucket is empty, or the key is the first element in the linked list. <br> - O(n): in worst case, all n elements hash to the same index, so you traverse the entire linked list <br> - Average case: O(1). |

## Example

```c
#include <stdio.h>
#include "hash_table.h"

int main(){

    Hash_Table ht = create_hash_table();

    // Add elements
    Hash_Table_add(&ht, "apple", 10);
    Hash_Table_add(&ht, "banana", 20);
    Hash_Table_add(&ht, "orange", 30);
    Hash_Table_add(&ht, "grape", 40);

    print_Hash_Table(&ht);
    /*
    Expected output:
    Key : Value
    apple : 10
    banana : 20
    orange : 30
    grape : 40
    */

    // Get values
    printf("\napple = %d\n", Hash_Table_get(&ht, "apple"));   // 10
    printf("grape = %d\n", Hash_Table_get(&ht, "grape"));     // 40

    // Update values
    Hash_Table_update(&ht, "banana", 99);
    Hash_Table_update(&ht, "orange", 77);

    printf("\nAfter updates:\n");
    print_Hash_Table(&ht);
    /*
    Expected output:
    Key : Value
    apple : 10
    banana : 99
    orange : 77
    grape : 40
    */

    // Delete element
    Hash_Table_delete(&ht, "apple");

    printf("\nAfter deleting apple:\n");
    print_Hash_Table(&ht);
    /*
    Expected output:
    Key : Value
    banana : 99
    orange : 77
    grape : 40
    */

    // Check key existence
    if(Key_in_Hash_Table(&ht, "banana")){
        printf("\nbanana exists\n"); // banana exists
    }

    // Size
    printf("Size = %d\n", Hash_Table_size(&ht)); // 3

    // Empty table
    Hash_Table_empty(&ht);

    printf("\nAfter emptying:\n");
    print_Hash_Table(&ht);
    /*
    Expected output:
    Hash is empty
    */

    return 0;
}

```

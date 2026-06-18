/* This file provides the necessary functions to implement a hash table.
   Possible operations:
   - add: Add a key-value pair
   - delete: Delete a pair
   - get: Get a value using its key
   - update: Change the value associated with a key

   A hash table is implemented using an array and linked lists.
   A key is transformed into an index using a hash function, and the 
   key-value pair is stored in the array at that index.
   If two keys produce the same index, a linked list is used to handle the collision.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hash_table.h"

// Computes the index in the hash table for a given key
int Hash_function(const char *c, int capacity){
    unsigned int nb = 0;
    int len = strlen(c);
    for(int i = 0; i < len; i++){
        nb = nb * 11 + c[i];
    }
    return nb % capacity;
}

// Creates a new hash table with a capacity of 4 elements
Hash_Table create_hash_table(){
    Hash_Table h_t;
    h_t.capacity = 4;
    h_t.pair = malloc(h_t.capacity * sizeof(elem*)); 
    h_t.size = 0;

    for(int i = 0; i < h_t.capacity ; i++){ 
        *(h_t.pair + i) = NULL;
    }
    
    return h_t;
}

// Checks if the Hash Table is empty
bool is_empty_hash_table(Hash_Table *h_t){
    return h_t->size == 0;
}

// Checks if a key is in the Hash Table
bool Key_in_Hash_Table(Hash_Table *h_t, const char *key){
    
    int index = Hash_function(key, h_t->capacity);
    elem *current = *(h_t->pair + index);
    while(current != NULL){
        if(strcmp(key, current->key) == 0){ // If strings matches
            return true;
        }
        current = current->next;
    }
    return false;
}

// Inserts a key-value pair into the hash table using separate chaining
void Hash_Table_add(Hash_Table *h_t, const char *key, int value){
    if(Key_in_Hash_Table(h_t, key)){
        printf("Key already exists: %s\n", key);
        return;
    }

    if(h_t->size == h_t->capacity){
        // Resizes the hash table when capacity is reached and rehashes all elements
        int new_capacity = h_t->capacity * 2;
        h_t->capacity = new_capacity;
        // Creates a new array of pairs
        elem **new_array_of_pairs = malloc(new_capacity * sizeof(elem*)); 
        for (int i = 0 ; i < h_t->capacity ; i++){
            *(new_array_of_pairs + i) = NULL;
        }
        // Copies elements from old array to new one, with their new indexes
        for(int i = 0 ; i<h_t->capacity / 2 ; i++){
            elem *current = h_t->pair[i];
            while(current != NULL){
                elem *next_one = current->next;
                int new_index = Hash_function(current->key, h_t->capacity);
                current->next = new_array_of_pairs[new_index];
                new_array_of_pairs[new_index] = current;
                current = next_one;
            }
        }
        free(h_t->pair);
        h_t->pair = new_array_of_pairs;
    }
    int index = Hash_function(key, h_t->capacity); // Hash index of the new key
    h_t->size++;
    elem *new_pair = malloc(sizeof(elem)); // New key-value pair
    strcpy(new_pair->key, key); 
    new_pair->value = value;
    new_pair->next = *(h_t->pair + index); // New pair's next pointer points to the current 
                                           // head of the chain at this index
    *(h_t->pair + index) = new_pair; // Changes the head of the chain to the new pair
}

// Returns the value of a given key
int Hash_Table_get(Hash_Table *h_t, const char *key){
    if(is_empty_hash_table(h_t)){
        printf("Hash is empty: ");
        return -1;
    }
    int index = Hash_function(key, h_t->capacity);
    elem *current = *(h_t->pair + index); // Head of the chain at index
    while(current != NULL){
        if(strcmp(key, current->key) == 0){
            return current->value;
        }
        current = current->next; // Next pair of the chain
    }
    printf("Key not found: %s ", key);
    return -1;
}

// Deletes a key-value pair from the Hash_Table
void Hash_Table_delete(Hash_Table *h_t, const char *key){
    if(is_empty_hash_table(h_t)){
        printf("Hash is empty\n");
        return;
    }

    int index = Hash_function(key, h_t->capacity);
    elem *current = *(h_t->pair + index);
    elem *previous = NULL;

    if (current == NULL) { 
       printf("Key not found: %s\n", key);
       return;
    }

    if(strcmp(key, current->key) == 0){ // First head of the chain
        *(h_t->pair + index) = current->next;
        free(current);
        h_t->size--;
        return;
    }
    previous = current;
    current = current->next;
    
    while(current != NULL){
        
        if(strcmp(key, current->key) == 0){
            previous->next = current->next;
            free(current);
            h_t->size--;
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("Key not found: %s\n", key);
}

// Frees all nodes in the hash table and resets it to empty
void Hash_Table_empty(Hash_Table *h_t){
    if(is_empty_hash_table(h_t)){
        printf("Hash is empty\n");
        return;
    }
    for(int i = 0; i < h_t->capacity; i++){
        elem *Now = *(h_t->pair + i);
        while(Now != NULL){
            elem *next = Now->next;
            free(Now);
            Now = next;
        }
        *(h_t->pair + i) = NULL;
    }
    h_t->size = 0;
}


// Frees all elements and the internal array. Used when the hash table is no longer needed.
void destroy_hash_table(Hash_Table *h_t) {
    for(int i = 0; i < h_t->capacity; i++){
        elem *current = *(h_t->pair + i);
        while(current != NULL){
            elem *next = current->next;
            free(current); // Frees each elem node in the chain
            current = next;
        }
    }
    free(h_t->pair); // Frees the bucket array itself
    h_t->pair = NULL;
    h_t->size = 0;
    h_t->capacity = 0;
}

// Prints all the elements of the Hash Table
void print_Hash_Table(Hash_Table *h_t){
    if(is_empty_hash_table(h_t)){
        printf("Hash is empty\n");
        return;
    }

    printf("Key : Value\n");
    for(int i = 0; i < h_t->capacity; i++){
        elem *Now = *(h_t->pair + i);
        while(Now != NULL){
            printf("%s : %d\n", Now->key, Now->value);
            Now = Now->next;
        }
        
    }
}

// Returns the number of elements in the Hash Table
int Hash_Table_size(Hash_Table *h_t){
    return h_t->size;
}

// Updates the value associated with a given key
void Hash_Table_update(Hash_Table *h_t, const char *key, int value){
    if(is_empty_hash_table(h_t)){
        printf("Hash is empty\n");
        return;
    }
    
    int index = Hash_function(key, h_t->capacity);

    elem *current = *(h_t->pair + index);
    while(current != NULL){
        if(strcmp(current->key, key) == 0){
            current->value = value;
            return;
        }
        current = current->next;
    }
    
    printf("Key not found: %s\n", key);

}


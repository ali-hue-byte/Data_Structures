// This file provides neccessary function to implement the Hash Table used in graph data structure

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"

// Computes the index in the hash table for a given key
int Hash_function(int key, int capacity){
    unsigned int k = (unsigned int)key;
    k = ((k >> 16) ^ k) * 0x45d9f3b;
    k = ((k >> 16) ^ k);
    return k % capacity;
}

// Creates a new hash table with a capacity of 4 elements
Hash_Table_Graph create_hash_table_graph(){
    Hash_Table_Graph h_t;
    h_t.capacity = 4;
    h_t.pair = malloc(h_t.capacity * sizeof(elem_Graph*));
    h_t.size = 0;
    for(int i = 0; i < h_t.capacity; i++)
        h_t.pair[i] = NULL;
    return h_t;
}

// Checks if the hash table is empty
bool is_empty_hash_table_graph(Hash_Table_Graph *h_t){
    return h_t->size == 0;
}

// Checks if a key is in the hash table
bool key_in_hash_table_graph(Hash_Table_Graph *h_t, int key){
    int index = Hash_function(key, h_t->capacity);
    elem_Graph *current = h_t->pair[index];
    while(current != NULL){
        if(current->key == key) return true;
        current = current->next;
    }
    return false;
}

// Inserts a key-value pair using separate chaining
void hash_table_graph_add(Hash_Table_Graph *h_t, int key, Vertex *value){
    if(key_in_hash_table_graph(h_t, key)){
        printf("Vertex id already exists: %d\n", key);
        return;
    }

    if(h_t->size == h_t->capacity){
        int new_capacity = h_t->capacity * 2;
        elem_Graph **new_pairs = malloc(new_capacity * sizeof(elem_Graph*));
        for(int i = 0; i < new_capacity; i++)
            new_pairs[i] = NULL;
        // Rehash all existing elements
        for(int i = 0; i < h_t->capacity; i++){
            elem_Graph *current = h_t->pair[i];
            while(current != NULL){
                elem_Graph *next = current->next;
                int new_index = Hash_function(current->key, new_capacity);
                current->next = new_pairs[new_index];
                new_pairs[new_index] = current;
                current = next;
            }
        }
        free(h_t->pair);
        h_t->pair = new_pairs;
        h_t->capacity = new_capacity;
    }

    int index = Hash_function(key, h_t->capacity);
    elem_Graph *new_pair = malloc(sizeof(elem_Graph));
    new_pair->key   = key;
    new_pair->value = value;
    new_pair->next  = h_t->pair[index];
    h_t->pair[index] = new_pair;
    h_t->size++;
}

// Returns the Vertex* for a given key, NULL if not found
Vertex *hash_table_graph_get(Hash_Table_Graph *h_t, int key){
    if(is_empty_hash_table_graph(h_t)){
        
        return NULL;
    }
    int index = Hash_function(key, h_t->capacity);
    elem_Graph *current = h_t->pair[index];
    while(current != NULL){
        if(current->key == key) return current->value;
        current = current->next;
    }
   
    return NULL;
}

// Deletes a key-value pair
void hash_table_graph_delete(Hash_Table_Graph *h_t, int key){
    if(is_empty_hash_table_graph(h_t)){
        printf("Graph is empty\n");
        return;
    }
    int index = Hash_function(key, h_t->capacity);
    elem_Graph *current  = h_t->pair[index];
    elem_Graph *previous = NULL;

    while(current != NULL){
        if(current->key == key){
            if(previous) previous->next = current->next;
            else h_t->pair[index] = current->next;
            free(current);
            h_t->size--;
            return;
        }
        previous = current;
        current  = current->next;
    }
    printf("Vertex id not found: %d\n", key);
}

// Frees all nodes, resets to empty
void hash_table_graph_empty(Hash_Table_Graph *h_t){
    for(int i = 0; i < h_t->capacity; i++){
        elem_Graph *current = h_t->pair[i];
        while(current != NULL){
            elem_Graph *next = current->next;
            free(current->value);
            free(current);
            current = next;
        }
        h_t->pair[i] = NULL;
    }
    h_t->size = 0;
}

// Frees everything including the array
void destroy_hash_table_graph(Hash_Table_Graph *h_t){
    hash_table_graph_empty(h_t);
    free(h_t->pair);
    h_t->pair     = NULL;
    h_t->capacity = 0;
}

// Returns number of elements
int hash_table_graph_size(Hash_Table_Graph *h_t){
    return h_t->size;
}

// Updates the Vertex* for a given key
void hash_table_graph_update(Hash_Table_Graph *h_t, int key, Vertex *value){
    if(is_empty_hash_table_graph(h_t)){
        printf("Graph is empty\n");
        return;
    }
    int index = Hash_function(key, h_t->capacity);
    elem_Graph *current = h_t->pair[index];
    while(current != NULL){
        if(current->key == key){
            current->value = value;
            return;
        }
        current = current->next;
    }
    printf("Vertex id not found: %d\n", key);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct elem{
   char key[20];
   int value;
   struct elem *next;
}elem;

typedef struct {
    elem **pair;
    int size;
    int capacity;
}Hash_Table;

int Hash_function(char c[20], int capacity){
    unsigned int nb = 0;
    for(int i = 0; i < strlen(c); i++){
        nb = nb * 11 + c[i];
    }
    return nb % capacity;
}

Hash_Table create_hash_table(){
    Hash_Table h_t;
    h_t.capacity = 4;

    h_t.pair = malloc(h_t.capacity * sizeof(elem*)); 
    for(int i = 0; i<h_t.capacity ; i++){
        *(h_t.pair + i) = NULL;
    }
    h_t.size = 0;
    return h_t;
}

bool is_empty_hash_table(Hash_Table *h_t){
    for(int i = 0; i < h_t->capacity ; i++){
        if(*(h_t->pair + i) != NULL){
            return false;
        }
    }
    return true;
}

void Hash_Table_add(Hash_Table *h_t, char key[20], int value){
    if(h_t->size == h_t->capacity){
        int new_capacity = h_t->capacity * 2;
        h_t->capacity = new_capacity;
        elem **new_array_of_pairs = malloc(new_capacity * sizeof(elem*));
        for (int i = 0 ; i < h_t->capacity ; i++){
            *(new_array_of_pairs + i) = NULL;
        }

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
    int index = Hash_function(key, h_t->capacity);
    h_t->size++;
    elem *new_pair = malloc(sizeof(elem));
    strcpy(new_pair->key, key);
    new_pair->value = value;
    new_pair->next = *(h_t->pair + index);
    *(h_t->pair + index) = new_pair;

}

int Hash_Table_get(Hash_Table *h_t, char key[20]){
    if(is_empty_hash_table(h_t)){
        printf("Hash is empty");
        return 0;
    }
    int index = Hash_function(key, h_t->capacity);
    elem *current = *(h_t->pair + index);
    while(current != NULL){
        if(strcmp(key, current->key) == 0){
            return current->value;
        }
        current = current->next;
    }
    printf("Key not found");
    return 0;
}

void Hash_Table_delete(Hash_Table *h_t, char key[20]){
    if(is_empty_hash_table(h_t)){
        printf("Hash is empty");
        return;
    }

    int index = Hash_function(key, h_t->capacity);
    elem *current = *(h_t->pair + index);
    elem *previous = NULL;

    if (current == NULL) {
       printf("Key not found");
       return;
    }

    if(strcmp(key, current->key) == 0){
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

    printf("Key not found");
}

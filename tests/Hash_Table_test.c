/*
Hash_Table_test.c

Purpose:
Tests the correctness of the Hash Table implementation.

Covered scenarios:
- Empty table handling
- General add/get/delete/update
- Duplicate key prevention
- Collision handling
- Resizing and rehashing
- Key not found handling
- Empty after operations
- Stress testing
*/

#include <stdio.h>
#include <stdlib.h>
#include "../Hash_Table/hash_table.h"

int main(){

    // Test 1: Empty table
    // Verifies that a newly created hash table is empty
    // and has size 0 without any operations
    printf("=== Test 1 ===\n\n");

    Hash_Table h_t = create_hash_table();
    printf("Empty?: %s\n", is_empty_hash_table(&h_t) ? "yes" : "no");
    printf("Size: %d\n\n", Hash_Table_size(&h_t));

    // Test 2: Add and get
    // Verifies elements are correctly added and retrieved
    printf("=== Test 2 ===\n\n");

    Hash_Table_add(&h_t, "name", 1);
    Hash_Table_add(&h_t, "age", 25);
    Hash_Table_add(&h_t, "score", 100);

    printf("name: %d\n", Hash_Table_get(&h_t, "name"));
    printf("age: %d\n", Hash_Table_get(&h_t, "age"));
    printf("score: %d\n", Hash_Table_get(&h_t, "score"));
    printf("Size: %d\n\n", Hash_Table_size(&h_t));

    // Test 3: Duplicate key prevention
    // Verifies that adding an existing key is rejected
    printf("=== Test 3 ===\n\n");

    Hash_Table_add(&h_t, "name", 999);
    printf("name after duplicate add: %d\n", Hash_Table_get(&h_t, "name"));
    printf("Size: %d\n\n", Hash_Table_size(&h_t));

    // Test 4: Update
    // Verifies value update works correctly
    printf("=== Test 4 ===\n\n");

    Hash_Table_update(&h_t, "age", 30);
    printf("age after update: %d\n", Hash_Table_get(&h_t, "age"));

    Hash_Table_update(&h_t, "non_existent", 0);
    printf("Size: %d\n\n", Hash_Table_size(&h_t));

    // Test 5: Delete
    // Verifies deletion works correctly
    printf("=== Test 5 ===\n\n");

    Hash_Table_delete(&h_t, "score");
    printf("score after delete: ");
    Hash_Table_get(&h_t, "score");
    printf("\n");
    printf("Size: %d\n\n", Hash_Table_size(&h_t));

    Hash_Table_delete(&h_t, "non_existent");
    printf("\n");

    // Test 6: Key not found
    // Verifies correct behavior when key doesn't exist
    printf("=== Test 6 ===\n\n");

    printf("get non_existent: ");
    Hash_Table_get(&h_t, "non_existent");
    printf("\n");
    printf("Key_in_Hash_Table non_existent: %s\n\n", Key_in_Hash_Table(&h_t, "nonexistent") ? "yes" : "no");

    // Test 7: Collision handling
    // Verifies that collisions are handled correctly using separate chaining
    printf("=== Test 7 ===\n\n");

    Hash_Table h_t2 = create_hash_table();
    Hash_Table_add(&h_t2, "a", 1);
    Hash_Table_add(&h_t2, "b", 2);
    Hash_Table_add(&h_t2, "c", 3);
    Hash_Table_add(&h_t2, "d", 4);

    printf("a: %d\n", Hash_Table_get(&h_t2, "a"));
    printf("b: %d\n", Hash_Table_get(&h_t2, "b"));
    printf("c: %d\n", Hash_Table_get(&h_t2, "c"));
    printf("d: %d\n", Hash_Table_get(&h_t2, "d"));
    printf("Size: %d\n\n", Hash_Table_size(&h_t2));

    // Test 8: Resizing and rehashing
    // Verifies that the table resizes correctly when capacity is reached
    // and all elements are accessible after rehashing
    printf("=== Test 8 ===\n\n");

    Hash_Table h_t3 = create_hash_table();
    char key[10];
    for(int i = 0; i < 20; i++){
        sprintf(key, "key%d", i);
        Hash_Table_add(&h_t3, key, i);
    }

    printf("Size after 20 inserts: %d\n", Hash_Table_size(&h_t3));

    int errors = 0;
    for(int i = 0; i < 20; i++){
        sprintf(key, "key%d", i);
        if(Hash_Table_get(&h_t3, key) != i) errors++;
    }
    printf("Errors after rehash: %d\n\n", errors);

    // Test 9: Empty after operations
    // Verifies table can be reused after Hash_Table_empty
    printf("=== Test 9 ===\n\n");

    Hash_Table_empty(&h_t2);
    printf("After empty:\n");
    printf("Empty?: %s\n", is_empty_hash_table(&h_t2) ? "yes" : "no");
    printf("Size: %d\n", Hash_Table_size(&h_t2));

    Hash_Table_add(&h_t2, "reused", 42);
    printf("After re-add: reused = %d\n", Hash_Table_get(&h_t2, "reused"));
    printf("Size: %d\n\n", Hash_Table_size(&h_t2));

    // Test 10: Print
    // Verifies print function works correctly
    printf("=== Test 10 ===\n\n");

    print_Hash_Table(&h_t);
    printf("\n");

    // Test 11: Stress test
    // Verifies correct behavior under heavy usage
    printf("=== Test 11 ===\n\n");

    Hash_Table h_t4 = create_hash_table();
    for(int i = 0; i < 10000; i++){
        sprintf(key, "k%d", i);
        Hash_Table_add(&h_t4, key, i);
    }

    printf("Size after 10000 inserts: %d\n", Hash_Table_size(&h_t4));

    errors = 0;
    for(int i = 0; i < 10000; i++){
        sprintf(key, "k%d", i);
        if(Hash_Table_get(&h_t4, key) != i) errors++;
    }
    printf("Errors: %d\n", errors);

    for(int i = 0; i < 10000; i++){
        sprintf(key, "k%d", i);
        Hash_Table_delete(&h_t4, key);
    }
    printf("Size after 10000 deletes: %d\n", Hash_Table_size(&h_t4));
    printf("Empty?: %s\n", is_empty_hash_table(&h_t4) ? "yes" : "no");

    destroy_hash_table(&h_t);
    destroy_hash_table(&h_t2);
    destroy_hash_table(&h_t3);
    destroy_hash_table(&h_t4);

    return 0;
}

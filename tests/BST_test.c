/*
BST_test.c

Run:
gcc BST_test.c ../Binary_Search_Tree/binary_search_tree.c ../Array/dynamic_array.c -o BST
./BST.exe

Purpose:
Tests the correctness of the Binary Search Tree implementation.

Covered scenarios:
- Empty BST handling
- General insert and search
- Duplicate prevention
- In-order print (sorted output)
- Min and max
- Delete leaf node
- Delete node with one child
- Delete node with two children
- Delete root (all cases: leaf, one child, two children)
- kth smallest and kth largest
- Invalid k handling
- Height tracking
- Empty after operations and reuse
- Operations on empty BST
- Stress testing
*/

#include <stdio.h>
#include <stdlib.h>
#include "../Binary_Search_Tree/binary_search_tree.h"

int main(){

    // Test 1: Empty BST
    // Verifies that a newly created BST is empty
    // and has size 0 without any operations
    printf("=== Test 1 ===\n\n");

    BST bst = create_BST();
    printf("Empty?: %s\n", is_empty_BST(&bst) ? "yes" : "no");
    printf("Size: %d\n\n", BST_length(&bst));

    // Test 2: General insert and search
    // Verifies elements are correctly inserted and found
    printf("=== Test 2 ===\n\n");

    BST_insert(&bst, 50);
    BST_insert(&bst, 30);
    BST_insert(&bst, 70);
    BST_insert(&bst, 20);
    BST_insert(&bst, 40);
    BST_insert(&bst, 60);
    BST_insert(&bst, 80);

    printf("Size after 7 inserts: %d\n", BST_length(&bst));
    printf("Search 50 (expect yes): %s\n", search_BST(&bst, 50) ? "yes" : "no");
    printf("Search 40 (expect yes): %s\n", search_BST(&bst, 40) ? "yes" : "no");
    printf("Search 99 (expect no): %s\n", search_BST(&bst, 99) ? "yes" : "no");
    printf("In-order (expect sorted): ");
    print_BST(&bst);
    printf("\n\n");

    // Test 3: Duplicate prevention
    // Verifies that inserting an existing value is rejected
    printf("=== Test 3 ===\n\n");

    BST_insert(&bst, 50);
    BST_insert(&bst, 30);
    printf("Size unchanged after duplicate inserts: %d\n\n", BST_length(&bst));

    // Test 4: Min and max
    // Verifies correct minimum and maximum retrieval
    printf("=== Test 4 ===\n\n");

    printf("Min (expect 20): %d\n", BST_min(&bst));
    printf("Max (expect 80): %d\n\n", BST_max(&bst));

    // Test 5: Delete leaf node
    // Verifies deletion of a node with no children
    printf("=== Test 5 ===\n\n");

    BST_delete(&bst, 20);
    printf("After deleting leaf 20:\n");
    printf("Search 20 (expect no): %s\n", search_BST(&bst, 20) ? "yes" : "no");
    printf("In-order: ");
    print_BST(&bst);
    printf("\n");
    printf("Size: %d\n\n", BST_length(&bst));

    // Test 6: Delete node with one child
    // Verifies deletion of a node with only one child
    printf("=== Test 6 ===\n\n");

    // 30 now has only right child (40) after deleting 20
    BST_delete(&bst, 30);
    printf("After deleting node with one child (30):\n");
    printf("Search 30 (expect no): %s\n", search_BST(&bst, 30) ? "yes" : "no");
    printf("Search 40 (expect yes): %s\n", search_BST(&bst, 40) ? "yes" : "no");
    printf("In-order: ");
    print_BST(&bst);
    printf("\n");
    printf("Size: %d\n\n", BST_length(&bst));

    // Test 7: Delete node with two children
    // Verifies deletion of a node with both children (uses inorder successor)
    printf("=== Test 7 ===\n\n");

    // 70 has two children: 60 and 80
    BST_delete(&bst, 70);
    printf("After deleting node with two children (70):\n");
    printf("Search 70 (expect no): %s\n", search_BST(&bst, 70) ? "yes" : "no");
    printf("Search 60 (expect yes): %s\n", search_BST(&bst, 60) ? "yes" : "no");
    printf("Search 80 (expect yes): %s\n", search_BST(&bst, 80) ? "yes" : "no");
    printf("In-order: ");
    print_BST(&bst);
    printf("\n");
    printf("Size: %d\n\n", BST_length(&bst));

    // Test 8: Delete root
    // Verifies all three root deletion cases
    printf("=== Test 8 ===\n\n");

    // Case 1: root with two children
    BST bst2 = create_BST();
    BST_insert(&bst2, 50);
    BST_insert(&bst2, 30);
    BST_insert(&bst2, 70);

    BST_delete(&bst2, 50);
    printf("Delete root with two children (50):\n");
    printf("Search 50 (expect no): %s\n", search_BST(&bst2, 50) ? "yes" : "no");
    printf("In-order: ");
    print_BST(&bst2);
    printf("\n");
    printf("Size: %d\n", BST_length(&bst2));

    // Case 2: root with one child
    BST bst3 = create_BST();
    BST_insert(&bst3, 50);
    BST_insert(&bst3, 70);

    BST_delete(&bst3, 50);
    printf("Delete root with one child (50):\n");
    printf("Search 50 (expect no): %s\n", search_BST(&bst3, 50) ? "yes" : "no");
    printf("In-order: ");
    print_BST(&bst3);
    printf("\n");
    printf("Size: %d\n", BST_length(&bst3));

    // Case 3: root is a leaf
    BST bst4 = create_BST();
    BST_insert(&bst4, 50);

    BST_delete(&bst4, 50);
    printf("Delete root that is a leaf (50):\n");
    printf("Empty?: %s\n", is_empty_BST(&bst4) ? "yes" : "no");
    printf("Size: %d\n\n", BST_length(&bst4));

    // Test 9: kth smallest and kth largest
    // Verifies correct retrieval of kth ordered values
    printf("=== Test 9 ===\n\n");

    BST bst5 = create_BST();
    BST_insert(&bst5, 50);
    BST_insert(&bst5, 30);
    BST_insert(&bst5, 70);
    BST_insert(&bst5, 20);
    BST_insert(&bst5, 40);
    BST_insert(&bst5, 60);
    BST_insert(&bst5, 80);

    printf("In-order: ");
    print_BST(&bst5);
    printf("\n");
    printf("1st smallest (expect 20): %d\n", BST_kth_smallest(&bst5, 1));
    printf("3rd smallest (expect 40): %d\n", BST_kth_smallest(&bst5, 3));
    printf("7th smallest (expect 80): %d\n", BST_kth_smallest(&bst5, 7));
    printf("1st largest (expect 80): %d\n", BST_kth_largest(&bst5, 1));
    printf("3rd largest (expect 60): %d\n", BST_kth_largest(&bst5, 3));
    printf("7th largest (expect 20): %d\n\n", BST_kth_largest(&bst5, 7));

    // Test 10: Invalid k handling
    // Verifies correct error handling for out-of-range k values
    printf("=== Test 10 ===\n\n");

    printf("kth_smallest k=0 (invalid): ");
    BST_kth_smallest(&bst5, 0);
    printf("\n");
    printf("kth_smallest k=8 (invalid, size=7): ");
    BST_kth_smallest(&bst5, 8);
    printf("\n");
    printf("kth_largest k=0 (invalid): ");
    BST_kth_largest(&bst5, 0);
    printf("\n");
    printf("kth_largest k=8 (invalid, size=7): ");
    BST_kth_largest(&bst5, 8);
    printf("\n\n");

    // Test 11: Height tracking
    // Verifies BST height is computed correctly
    printf("=== Test 11 ===\n\n");

    BST bst6 = create_BST();
    printf("Height of empty BST (expect 0): %d\n", BST_height(&bst6));

    BST_insert(&bst6, 50);
    printf("Height after inserting root only (expect 1): %d\n", BST_height(&bst6));

    BST_insert(&bst6, 30);
    BST_insert(&bst6, 70);
    printf("Height after balanced 3-node tree (expect 2): %d\n", BST_height(&bst6));

    BST_insert(&bst6, 20);
    BST_insert(&bst6, 10);
    printf("Height after inserting left chain (expect 4): %d\n\n", BST_height(&bst6));

    // Test 12: Operations on empty BST
    // Verifies correct error handling for all operations on empty BST
    printf("=== Test 12 ===\n\n");

    BST bst7 = create_BST();
    printf("Search on empty BST (expect no): %s\n", search_BST(&bst7, 5) ? "yes" : "no");
    printf("Min on empty BST: ");
    BST_min(&bst7);
    printf("\n");
    printf("Max on empty BST: ");
    BST_max(&bst7);
    printf("\n");
    printf("Delete on empty BST: ");
    BST_delete(&bst7, 5);
    printf("kth_smallest on empty BST: ");
    BST_kth_smallest(&bst7, 1);
    printf("kth_largest on empty BST: ");
    BST_kth_largest(&bst7, 1);
    printf("\n\n");

    // Test 13: Empty after operations and reuse
    // Verifies BST can be reused after empty_BST
    printf("=== Test 13 ===\n\n");

    empty_BST(&bst5);
    printf("After empty_BST:\n");
    printf("Empty?: %s\n", is_empty_BST(&bst5) ? "yes" : "no");
    printf("Size: %d\n", BST_length(&bst5));

    BST_insert(&bst5, 100);
    BST_insert(&bst5, 50);
    BST_insert(&bst5, 150);
    printf("After re-insert:\n");
    printf("In-order: ");
    print_BST(&bst5);
    printf("\n");
    printf("Min (expect 50): %d\n", BST_min(&bst5));
    printf("Max (expect 150): %d\n", BST_max(&bst5));
    printf("Size: %d\n\n", BST_length(&bst5));

    // Test 14: Delete non-existent value
    // Verifies correct error handling when deleting a missing value
    printf("=== Test 14 ===\n\n");

    printf("Delete non-existent value (999): ");
    BST_delete(&bst5, 999);
    printf("Size unchanged: %d\n\n", BST_length(&bst5));

    // Test 15: Stress test
    // Verifies correct behavior under heavy usage:
    // large-scale inserts, searches, kth queries, and deletes
    printf("=== Test 15 ===\n\n");

    BST bst8 = create_BST();
    for(int i = 1; i <= 10000; i++){
        BST_insert_silent(&bst8, i);
    }

    printf("Size after 10000 inserts: %d\n", BST_length(&bst8));
    printf("Min (expect 1): %d\n", BST_min(&bst8));
    printf("Max (expect 10000): %d\n", BST_max(&bst8));
    printf("Height: %d\n", BST_height(&bst8));

    int errors = 0;
    for(int i = 1; i <= 10000; i++){
        if(!search_BST(&bst8, i)) errors++;
    }
    printf("Search errors: %d\n", errors);

    printf("1st smallest (expect 1): %d\n", BST_kth_smallest(&bst8, 1));
    printf("5000th smallest (expect 5000): %d\n", BST_kth_smallest(&bst8, 5000));
    printf("1st largest (expect 10000): %d\n", BST_kth_largest(&bst8, 1));

    for(int i = 1; i <= 10000; i++){
        BST_delete(&bst8, i);
    }

    printf("Size after 10000 deletes: %d\n", BST_length(&bst8));
    printf("Empty?: %s\n", is_empty_BST(&bst8) ? "yes" : "no");

    empty_BST(&bst);
    empty_BST(&bst2);
    empty_BST(&bst3);
    empty_BST(&bst4);
    empty_BST(&bst5);
    empty_BST(&bst6);
    empty_BST(&bst7);
    empty_BST(&bst8);

    return 0;
}

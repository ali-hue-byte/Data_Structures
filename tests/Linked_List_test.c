/*
CDLL_test.c

Purpose:
Tests the correctness of the Circular Doubly Linked List implementation.

Covered scenarios:
- Empty list handling
- Push back/front
- Insert after/before
- Front/back access
- Pop front/back
- Update node value
- Delete node
- Single element edge cases
- Node ownership validation
- Empty after operations
- Stress testing
*/

#include <stdio.h>
#include <stdlib.h>
#include "../Linked_List/linked_list.h"

int main(){

    // Test 1: Empty list
    // Verifies that a newly created list is empty
    // and has size 0 without any operations
    printf("=== Test 1 ===\n\n");

    Circular_Double_Linked_List lst = create_CDLL();
    printf("Empty?: %s\n", CDLL_is_empty(&lst) ? "yes" : "no");
    printf("Size: %d\n\n", CDLL_get_length(&lst));

    // Test 2: Push back
    // Verifies elements are added to the back correctly
    printf("=== Test 2 ===\n\n");

    CDLL_Node *n1 = CDLL_push_back(&lst, 10);
    CDLL_Node *n2 = CDLL_push_back(&lst, 20);
    CDLL_Node *n3 = CDLL_push_back(&lst, 30);

    printf("List: ");
    print_CDLL(&lst);
    printf("\n");
    printf("Front: %d\n", CDLL_front(&lst));
    printf("Back: %d\n", CDLL_back(&lst));
    printf("Size: %d\n\n", CDLL_get_length(&lst));

    // Test 3: Push front
    // Verifies elements are added to the front correctly
    printf("=== Test 3 ===\n\n");

    CDLL_push_front(&lst, 5);
    CDLL_push_front(&lst, 1);

    printf("List: ");
    print_CDLL(&lst);
    printf("\n");
    printf("Front: %d\n", CDLL_front(&lst));
    printf("Back: %d\n", CDLL_back(&lst));
    printf("Size: %d\n\n", CDLL_get_length(&lst));

    // Test 4: Insert after/before
    // Verifies insertion at arbitrary positions
    printf("=== Test 4 ===\n\n");

    CDLL_insert_after(&lst, n2, 25);
    printf("After insert_after(n2, 25): ");
    print_CDLL(&lst);
    printf("\n");

    CDLL_insert_before(&lst, n3, 28);
    printf("After insert_before(n3, 28): ");
    print_CDLL(&lst);
    printf("\n");
    printf("Size: %d\n\n", CDLL_get_length(&lst));

    // Test 5: Get node value
    // Verifies correct value retrieval from nodes
    printf("=== Test 5 ===\n\n");

    printf("Value of n1: %d\n", CDLL_get_node_value(&lst, n1));
    printf("Value of n2: %d\n", CDLL_get_node_value(&lst, n2));
    printf("Value of n3: %d\n\n", CDLL_get_node_value(&lst, n3));

    // Test 6: Update node value
    // Verifies value update works correctly
    printf("=== Test 6 ===\n\n");

    CDLL_update_node_value(&lst, n2, 99);
    printf("After update n2 to 99: ");
    print_CDLL(&lst);
    printf("\n");
    printf("Value of n2: %d\n\n", CDLL_get_node_value(&lst, n2));

    // Test 7: Pop front/back
    // Verifies elements are removed from front and back correctly
    printf("=== Test 7 ===\n\n");

    printf("Pop front: %d\n", CDLL_pop_front(&lst));
    printf("Pop back: %d\n", CDLL_pop_back(&lst));
    printf("List after pops: ");
    print_CDLL(&lst);
    printf("\n");
    printf("Size: %d\n\n", CDLL_get_length(&lst));

    // Test 8: Delete node
    // Verifies node deletion works correctly
    printf("=== Test 8 ===\n\n");

    CDLL_delete_node(&lst, n2);
    printf("After delete n2: ");
    print_CDLL(&lst);
    printf("\n");
    printf("Size: %d\n\n", CDLL_get_length(&lst));

    // Test 9: Node ownership validation
    // Verifies that operations reject nodes from other lists
    printf("=== Test 9 ===\n\n");

    Circular_Double_Linked_List lst2 = create_CDLL();
    CDLL_Node *foreign = CDLL_push_back(&lst2, 999);

    printf("Insert foreign node into lst: \n");
    CDLL_insert_after(&lst, foreign, 0);
    printf("Delete foreign node from lst: \n");
    CDLL_delete_node(&lst, foreign);
    printf("Update foreign node in lst: \n");
    CDLL_update_node_value(&lst, foreign, 0);
    printf("\n");

    // Test 10: Single element edge cases
    // Verifies all operations work with only one element
    printf("=== Test 10 ===\n\n");

    Circular_Double_Linked_List lst3 = create_CDLL();
    CDLL_Node *only = CDLL_push_back(&lst3, 42);

    printf("Front: %d\n", CDLL_front(&lst3));
    printf("Back: %d\n", CDLL_back(&lst3));
    printf("Pop front: %d\n", CDLL_pop_front(&lst3));
    printf("Empty?: %s\n", CDLL_is_empty(&lst3) ? "yes" : "no");

    CDLL_push_back(&lst3, 42);
    printf("Pop back: %d\n", CDLL_pop_back(&lst3));
    printf("Empty?: %s\n\n", CDLL_is_empty(&lst3) ? "yes" : "no");

    // Test 11: Empty after operations
    // Verifies list can be reused after empty_CDLL
    printf("=== Test 11 ===\n\n");

    empty_CDLL(&lst);
    printf("After empty_CDLL:\n");
    printf("Empty?: %s\n", CDLL_is_empty(&lst) ? "yes" : "no");
    printf("Size: %d\n", CDLL_get_length(&lst));

    CDLL_push_back(&lst, 100);
    CDLL_push_back(&lst, 200);
    printf("After re-push: ");
    print_CDLL(&lst);
    printf("\n\n");

    // Test 12: Stress test
    // Verifies correct behavior under heavy usage
    printf("=== Test 12 ===\n\n");

    Circular_Double_Linked_List lst4 = create_CDLL();
    for(int i = 0; i < 1000000; i++){
        CDLL_push_back(&lst4, i);
    }

    printf("Size: %d\n", CDLL_get_length(&lst4));
    printf("Front: %d\n", CDLL_front(&lst4));
    printf("Back: %d\n", CDLL_back(&lst4));

    for(int i = 0; i < 1000000; i++){
        if(CDLL_pop_front(&lst4) != i){
            printf("FAILED\n");
            return 1;
        }
    }
    printf("1000000 POP FRONT PASSED\n");
    printf("Empty?: %s\n", CDLL_is_empty(&lst4) ? "yes" : "no");

    empty_CDLL(&lst);
    empty_CDLL(&lst2);
    empty_CDLL(&lst3);

    return 0;
}

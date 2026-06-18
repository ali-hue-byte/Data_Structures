# Linked List

## Description

A Circular Doubly Linked List (CDLL) is a node-based data structure, where each node has its value and a pointer to the next and previous nodes. The last node also points to the first one, and vice versa, forming a circle.

Unlike a regular linked list, the (CDLL) gives an easier and faster access to the last element, and allows traversal in both directions. 


## How it works

### Structure
Internally, each node stores its value, a pointer to the next node, a pointer to the previous node, and a pointer to the list it belongs to. This last pointer is used as an ownership check — before any operation on a node, the function verifies that the node actually belongs to the list it's being used with, preventing accidental misuse across different lists.

### Circularity
Since the list is circular, the last node always points to the head, and the head always points back to the last node. This means that head->previous gives instant access to the tail at any time, without needing a separate tail pointer. This is what makes CDLL_back, CDLL_push_back, and CDLL_pop_back all O(1).

### Insertion/Deletion
When inserting or deleting a node, only the pointers of the neighboring nodes need to be updated, no elements are shifted like in an array. This is why every insertion and deletion in the CDLL is O(1), regardless of the size of the list.

## Operations

| Functions | Description | Time complexity |
|-----------|-------------|-----------------|
| create_CDLL | Creates a new Circular Doubly Linked List. | O(1) |
| CDLL_push_back | Adds a new node to the back of the linked list, and returns it for future uses. | O(1) |
| CDLL_push_front | Adds a new node to the front of the linked list, and returns it for future uses. | O(1) |
| CDLL_insert_after | Adds a new node after a given one. | O(1) |
| CDLL_insert_before | Adds a new node before a given one. | O(1) |
| CDLL_get_node_value | Returns the value stored in a given node. | O(1) |
| CDLL_front | Returns the value in the front of the Linked List. | O(1) |
| CDLL_back | Returns the value in the back of the Linked List | O(1) |
| CDLL_pop_front | Returns and removes the value in the front of the Linked List. | O(1) |
| CDLL_pop_back | Returns and removes the value in the back of the Linked List. | O(1) |
| CDLL_update_node_value | Changes the value at a given node. | O(1) |
| CDLL_delete_node | Deletes a given node. | O(1) |
| print_CDLL | Prints the Linked List. | O(n) |
| CDLL_get_length | Returns number of elements in the linked list. | O(1) |
| CDLL_is_empty | Checks if the Linked List is empty. | O(1) |
| empty_CDLL | Frees all the Nodes of the linked list. | O(n) |


## Example

```c

#include "linked_list.h"
#include <stdio.h>

int main(void) {
    Circular_Double_Linked_List lst = create_CDLL();

    Node *n1 = CDLL_push_back(&lst, 10);
    Node *n2 = CDLL_push_back(&lst, 20);
    Node *n3 = CDLL_push_back(&lst, 30);

    printf("List: ");
    print_CDLL(&lst); // 10 20 30
    printf("\n");

    CDLL_push_front(&lst, 5);
    printf("After push_front(5): ");
    print_CDLL(&lst); // 5 10 20 30
    printf("\n");

    CDLL_insert_after(&lst, n2, 25);
    printf("After insert_after(n2, 25): ");
    print_CDLL(&lst); // 5 10 20 25 30
    printf("\n");

    CDLL_insert_before(&lst, n3, 28);
    printf("After insert_before(n3, 28): ");
    print_CDLL(&lst); // 5 10 20 25 28 30
    printf("\n");

    printf("Front: %d\n", CDLL_front(&lst)); // 5
    printf("Back: %d\n", CDLL_back(&lst)); // 30

    printf("Pop front: %d\n", CDLL_pop_front(&lst)); // 5
    printf("Pop back: %d\n", CDLL_pop_back(&lst)); // 30

    printf("List: ");
    print_CDLL(&lst); // 10 20 25 28
    printf("\n");

    CDLL_update_node_value(&lst, n2, 99);
    printf("After update n2 to 99: ");
    print_CDLL(&lst); // 10 99 25 28
    printf("\n");

    CDLL_delete_node(&lst, n2);
    printf("After delete n2: ");
    print_CDLL(&lst); // 10 25 28
    printf("\n");

    printf("Size: %d\n", CDLL_get_length(&lst)); // 3
    
    printf("Empty? %s\n", CDLL_is_empty(&lst) ? "yes" : "no"); // no
    empty_CDLL(&lst);
    printf("Empty? %s\n", CDLL_is_empty(&lst) ? "yes" : "no"); // yes

    return 0;
}

```

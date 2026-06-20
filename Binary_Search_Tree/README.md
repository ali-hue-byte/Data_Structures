# Binary Search Tree

## Description

A BST is a data structure represented by a tree, where each node has at most two children (left and right). The left child always holds a value smaller than its parent, and the right child always holds a value greater than its parent. This property applies to every node in the tree, not just the root.

---
## How does it work

---
## Operations

| Functions | Description | Time complexity |
|-----------|-------------|-----------------|
| create_BST |||
| successor(Node *node) |||
| BST_insert(BST *bst, int value) |||
| BST_delete(BST *bst, int value) |||
| empty_node(BST *bst, Node *node) |||
| empty_BST(BST *bst) |||
| search_BST(BST *bst, int value) |||
| print_node(Node *node) |||
| print_BST(BST *bst) |||
| BST_length(BST *bst) |||
| is_empty_BST(BST *bst) |||
| is_leaf_BST_Node(Node *node) |||
| BST_min(BST *bst) |||
| BST_max(BST *bst) |||
| Node_height(Node *node) |||
| BST_height(BST *bst) |||
| nodes(Dynamic_Array *arr, Node *node) |||
| BST_get_values(BST *bst) |||
| BST_kth_smallest(BST *bst, int k) |||
| BST_kth_largest(BST *bst, int k) |||


---
## Example

```c

#include "binary_search_tree.h"
#include <stdio.h>

int main(void) {
    BST bst = create_BST();

    BST_insert(&bst, 10);
    BST_insert(&bst, 5);
    BST_insert(&bst, 15);
    BST_insert(&bst, 3);
    BST_insert(&bst, 7);
    BST_insert(&bst, 12);
    BST_insert(&bst, 20);
    BST_insert(&bst, 10); // Value already exists: 10

    printf("BST: ");
    print_BST(&bst); // 3 5 7 10 12 15 20
    printf("\n");

    printf("Size: %d\n", BST_length(&bst)); // 7
    printf("Height: %d\n", BST_height(&bst)); // 3
    printf("Min: %d\n", BST_min(&bst)); // 3
    printf("Max: %d\n", BST_max(&bst)); // 20

    printf("Search 7: %s\n", search_BST(&bst, 7) ? "found" : "not found"); // found
    printf("Search 99: %s\n", search_BST(&bst, 99) ? "found" : "not found"); // not found

    BST_delete(&bst, 3); // leaf
    printf("After delete 3: ");
    print_BST(&bst); // 5 7 10 12 15 20
    printf("\n");

    BST_delete(&bst, 15); // one child
    printf("After delete 15: ");
    print_BST(&bst); // 5 7 10 12 20
    printf("\n");

    BST_delete(&bst, 10); // root, two children
    printf("After delete root (10): ");
    print_BST(&bst); // 5 7 12 20
    printf("\n");

    BST_delete(&bst, 99); // Value not found

    printf("Size: %d\n", BST_length(&bst)); // 4
    printf("Height: %d\n", BST_height(&bst)); // 3

    empty_BST(&bst);
    printf("Empty? %s\n", is_empty_BST(&bst) ? "yes" : "no"); // yes
    print_BST(&bst); // BST is empty

    return 0;
}

```

---
## Visualisation of the BST used in the example

<img width="1723" height="283" alt="image" src="https://github.com/user-attachments/assets/72162ed8-a9a2-4ed1-bd87-f86de56bdb6f" />

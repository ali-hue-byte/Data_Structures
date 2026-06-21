# Binary Search Tree

## Description

A BST is a data structure represented by a tree, where each node has at most two children (left and right). The left child always holds a value smaller than its parent, and the right child always holds a value greater than its parent. This property applies to every node in the tree, not just the root.

---
## How does it work

### Structure
The BST is implemented using nodes principle. Each node holds a value, a pointer to its left child, a pointer to its right child, and a pointer to its parent. The parent pointer removes the need to track the parent manually during traversal, simplifying insertion, deletion, and other operations. The first inserted node becomes the root — the topmost node of the tree, which has no parent.

### BST property
The BST property is the rule that defines the structure of the tree: every value in the left subtree of a node is smaller than that node, and every value in the right subtree is greater. This rule applies to every node, not just the root.

This property is what makes the BST efficient — when searching for a value, at every node you instantly know which side to go. If the value is smaller go left, if larger go right. This eliminates half the remaining tree at each step, giving O(log n) search on average instead of O(n) like a regular unsorted tree.

### Successor
After deleting a node, it needs to be replaced with another one so the tree remains valid. But we can't use any node, it has to maintain the BST property, it must be bigger than every value on the left subtree of the deleted node, and smaller than every value on the right subtree. The only node that guarantees this is the smallest value in the right subtree, which is called the inorder successor. It is the leftmost node in the right subtree, which also means deleting it from its original position is always simple, it has at most one child.

### Insertion
Using the BST property, it is easy and fast to find the position of the new value. Starting from the root, the new value is compared at each node, if it is smaller we go left, if it is greater we go right, until we reach a NULL spot where the new node is inserted.

### Deletion
Once the node to delete is located using BST property, there are three cases to handle:
##### Leaf:
The node to delete has no children and is removed directly.
##### One child:
The parent of the node is linked directly to that child, bypassing the deleted node.
##### Two children:
The node is replaced with its inorder successor, which is then removed from its original position.

##### Special case: the root
The root has no parent, so it is handled separately. It also has the same three cases as every node : *leaf*, *one child* and *two children*.

---
## Limitations

A BST is not self-balancing. Inserting sorted data can degenerate the tree into a linked list.

Example:
```
inserting: 1 2 3 4 5

1
 \
  2
   \
    3
     \
      4
       \
        5
```
In this case, search, insertion and deletion become O(n).

Self-balancing trees such as AVL trees solve this issue.

---
## Operations

| Functions | Description | Time complexity |
|-----------|-------------|-----------------|
| create_BST | Creates a new Binary Search Tree | O(1) |
| successor(BST_Node *node) | Finds the successor of a Node, which is the smallest value in the right subtree. | - Average: O(log(n)) <br> - Worst case: O(n) |
| BST_insert(BST *bst, int value) | Inserts an element to it's corresponding place in the tree based on the BST property. | - Average: O(log(n)) <br> - Worst case: O(n) |
| BST_delete(BST *bst, int value) | Deletes an element from the BST. | - Average: O(log(n)) <br> - Worst case: O(n) |
| empty_node(BST *bst, BST_Node *node) | Helper recursive function: Frees every node starting from a given node. | O(n) |
| empty_BST(BST *bst) | Empties the BST, using empty_node function. | O(n) |
| search_BST(BST *bst, int value) | Checks if a value is in the BST. | - Average: O(log(n)) <br> - Worst case: O(n) |
| print_node(BST_Node *node) | Helper recursive function: Prints every value starting from a given node. | O(n) |
| print_BST(BST *bst) | Prints every element of the BST from smallest to largest, using print_node funtion. | O(n) |
| BST_length(BST *bst) | Returns number of elements in the BST. | O(1) |
| is_empty_BST(BST *bst) | Checks if the BST is empty. | O(1) |
| is_leaf_BST_Node(BST_Node *node) | Helper function: Checks if a Node is a leaf. | O(1) |
| BST_min(BST *bst) | Returns the minimum value in a BST. | - Average: O(log(n)) <br> - Worst case: O(n) |
| BST_max(BST *bst) | Returns the maximum value in a BST. | - Average: O(log(n)) <br> - Worst case: O(n) |
| Node_height(BST_Node *node) | Helper recursive function: returns the number of edges on the longest path from that node down to a leaf. | O(n) |
| BST_height(BST *bst) | Returns the height of the BST. | O(n) |
| nodes(Dynamic_Array *arr, BST_Node *node) | Helper recursive function: inserts every value to a dynamic array starting from a given node. | O(n) |
| BST_get_values(BST *bst) | Returns a dynamic array of the BST values (sorted). Caller is responsible for freeing the returned array's data (free(array.data)). | O(n) |
| BST_kth_smallest(BST *bst, int k) | Returns the kth smallest value in the BST. | O(n) |
| BST_kth_largest(BST *bst, int k) | Returns the kth largest value in the BST. | O(n) |


---
## Example

```c

#include "binary_search_tree.h"
#include "ds.h"
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

    printf("2nd smallest: %d\n", BST_kth_smallest(&bst, 2)); // 5
    printf("2nd largest: %d\n", BST_kth_largest(&bst, 2)); // 15

    Dynamic_Array values = BST_get_values(&bst);
    printf("Values: ");
    print_dynamic_array(&values); // 3 5 7 10 12 15 20
    printf("\n");
    free(values.data); // Don't forget to free data
    
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

/* This file provides necessary functions to implement a Binary Search Tree (BST).

   A BST is a tree where each node has at most two children (left and right).
   The left child always holds a value smaller than its parent, and the right
   child always holds a value greater than its parent. This property applies
   to every node in the tree, not just the root.

   The topmost node is called the root. Nodes with no children are called leaves.
   Nodes in between are called internal nodes.

   Possible operations :
   - insert: Adds a new value to the BST (no duplicates)
   - delete: Removes a value from the BST
   - search: Checks if a value is in the BST
   - min: Returns the minimum value of the BST
   - max: Returns the maximum value of the BST
   - kth_smallest: Returns the kth smallest value in the BST
   - kth_largest: Returns the kth largest value in the BST
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binary_search_tree.h"


// Creates a new Binary Search Tree
BST create_BST(){
    BST bst;
    bst.root = NULL;
    bst.size = 0;

    return bst;

}

// Finds the successor of a Node, which is the smallest value in the right subtree
BST_Node *successor(BST_Node *node){
    BST_Node *current = node->right;
    while(current->left != NULL){
        current = current->left;
    }
    return current;
}

// Inserts an element to it's corresponding place in the tree based on the BST property
void BST_insert(BST *bst, int value){
   
    BST_Node* new_Node = malloc(sizeof(BST_Node));
    new_Node->value = value;
    new_Node->left = NULL;
    new_Node->right = NULL;
    
    // If the BST is empty, the new Node is the root
    if(is_empty_BST(bst)){
        new_Node->parent = NULL;
        bst->root = new_Node;
        bst->size++;
        return;
    }

    BST_Node *current = bst->root;
    // Walk the tree to find the correct position
    while(true){
        if (value > current->value){ 
            if(current->right == NULL){ // Place found
                new_Node->parent = current;
                current->right = new_Node;
                bst->size++;
                return;
            }
            
            current = current->right; // Go to right
        }else if (value < current->value){
            if(current->left == NULL){ // Place found
                new_Node->parent = current;
                current->left = new_Node;
                bst->size++;
                return;
            }

            current = current->left; // Go to left
        }else{
            printf("Value already exists: %d\n", value);
            free(new_Node);
            return;
        }

    }

}

// Same function but doesn't print error messages
void BST_insert_silent(BST *bst, int value){
   
    BST_Node* new_Node = malloc(sizeof(BST_Node));
    new_Node->value = value;
    new_Node->left = NULL;
    new_Node->right = NULL;
    
    // If the BST is empty, the new Node is the root
    if(is_empty_BST(bst)){
        new_Node->parent = NULL;
        bst->root = new_Node;
        bst->size++;
        return;
    }

    BST_Node *current = bst->root;
    // Walk the tree to find the correct position
    while(true){
        if (value > current->value){ 
            if(current->right == NULL){ // Place found
                new_Node->parent = current;
                current->right = new_Node;
                bst->size++;
                return;
            }
            
            current = current->right; // Go to right
        }else if (value < current->value){
            if(current->left == NULL){ // Place found
                new_Node->parent = current;
                current->left = new_Node;
                bst->size++;
                return;
            }

            current = current->left; // Go to left
        }else{
            free(new_Node);
            return;
        }

    }

}


// Deletes an element from the BST
void BST_delete(BST *bst, int value){
    if(is_empty_BST(bst)){
        printf("BST is empty\n");
        return;
    }

    // Find the node to delete
    BST_Node *current = bst->root;
    while(current != NULL && current->value != value){
        if(value < current->value) current = current->left;
        else current = current->right;
    }

    if(current == NULL){
        printf("Value not found: %d\n", value);
        return;
    }

    // Case 1: two children — copy successor value and delete successor
    if(current->left != NULL && current->right != NULL){
        BST_Node *succ = successor(current);
        current->value = succ->value; // copy value down
        current = succ; // now delete the successor (has at most one child)
    }

    // Case 2: zero or one child
    BST_Node *child = (current->left != NULL) ? current->left : current->right;

    if(child != NULL) child->parent = current->parent;

    if(current->parent == NULL){ // node is root
        bst->root = child;
    }else if(current->parent->left == current){
        current->parent->left = child;
    }else{
        current->parent->right = child;
    }

    free(current);
    bst->size--;
}

// Helper recursive function: Frees every node starting from a given node
void empty_node(BST *bst, BST_Node *node){
    if(node == NULL) return;
    empty_node(bst, node->left);
    if (node != bst->root){
        if(node->parent->left == node) node->parent->left = NULL;
        if(node->parent->right == node) node->parent->right = NULL;
    }else{
        bst->root = NULL;
    }
    // Save right child before freeing to avoid use-after-free
    BST_Node *r = node->right;
    free(node);
    empty_node(bst, r);
}

// Empties the BST
void empty_BST(BST *bst){
   empty_node(bst, bst->root);
   bst->size = 0;
}

// Checks if a value is in the BST
bool search_BST(BST *bst, int value){
    if(is_empty_BST(bst)){
        return false;
    }
    BST_Node *current = bst->root;
    while(current != NULL){
        if (current->value == value){
            return true;
        }else if (value > current->value){
            current = current->right;
        }else if (value < current->value){
            current = current->left;
        }
    }
    return false;
}

// Helper recursive function: Prints every value starting from a given node
void print_node(BST_Node *node){
    if(node == NULL) return;
    print_node(node->left);
    printf("%d ", node->value);
    print_node(node->right);
}

// Prints the BST (sorted)
void print_BST(BST *bst){
    if(is_empty_BST(bst)) 
    {
        printf("BST is empty\n");
        return;
    }
    print_node(bst->root);
}

// Returns number of elements in the BST
int BST_length(BST *bst){
    return bst->size;
}

// Checks if the BST is empty
bool is_empty_BST(BST *bst){
    return bst->root == NULL;
}

// Checks if a Node is a leaf
bool is_leaf_BST_Node(BST_Node *node){
    return (node->left == NULL && node->right == NULL);
}

// Returns the minimum value in a BST
int BST_min(BST *bst){
    if(is_empty_BST(bst)){
        printf("BST is empty: ");
        return 0;
    }
    BST_Node *current = bst->root;
    while(current->left != NULL){
        current = current->left;
    }

    return current->value;
    
}

// Returns the maximum value in a BST
int BST_max(BST *bst){
    if(is_empty_BST(bst)){
        printf("BST is empty: ");
        return 0;
    }
    BST_Node *current = bst->root;
    while(current->right != NULL){
        current = current->right;
    }

    return current->value;
    
}

// Helper recursive function: returns the number of edges on 
// the longest path from that node down to a leaf
int Node_height(BST_Node *node){
    if(node == NULL) return 0;
    // Recursively compute height of left and right subtrees
    int left = Node_height(node->left);
    int right = Node_height(node->right);
    return 1 + (left > right ? left : right); // max(left, right)
}

// Returns the height of the BST
int BST_height(BST *bst){
    return Node_height(bst->root);
}


// Helper recursive function: inserts every value to a dynamic array starting from a given node
void nodes(Dynamic_Array *arr, BST_Node *node){
    if(node == NULL) return;
    nodes(arr, node->left);
    dynamic_array_append(arr, node->value);
    nodes(arr, node->right);
}

// Returns a dynamic array of the BST values (sorted) 
// Caller is responsible for freeing the returned array's data
Dynamic_Array BST_get_values(BST *bst){
     if(is_empty_BST(bst)) 
    {
        printf("BST is empty\n");
        return create_dynamic_array();
    }
    
    Dynamic_Array d_arr = create_dynamic_array();
    nodes(&d_arr, bst->root);
    return d_arr;
}

// Returns the kth smallest value in the BST
int BST_kth_smallest(BST *bst, int k){
    
    if(is_empty_BST(bst)){
        printf("BST is empty\n");
        return -1;
    }
    else if (k <= 0 || k > bst->size){
        printf("Invalid k: %d ", k);
        return -1;
    }
    else{
        Dynamic_Array bst_arr = BST_get_values(bst);
        int nb = dynamic_array_value(&bst_arr, k-1);
        free(bst_arr.data);
        return nb;
    }

    
}

// Returns the kth largest value in the BST
int BST_kth_largest(BST *bst, int k){
    if(is_empty_BST(bst)){
        printf("BST is empty: ");
        return -1;
    }
    else if (k <= 0 || k > bst->size){
        printf("Invalid k: %d: ", k);
        return -1;
    }
    else{
        Dynamic_Array bst_arr = BST_get_values(bst);
        int size = bst->size;
        int nb = dynamic_array_value(&bst_arr, size-k);
        free(bst_arr.data);
        return nb;
    }
}


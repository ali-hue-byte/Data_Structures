#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "../Array/dynamic_array.h"

typedef struct Node{
    int value;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    
} Node;

typedef struct BST{
    Node* root;
    int size;
} BST;

BST create_BST();
void BST_insert(BST *bst, int value);
void BST_delete(BST *bst, int value);
int BST_length(BST *bst);
bool is_empty_BST(BST *bst);
bool is_leaf_BST_Node(Node *node);
void print_BST(BST *bst);
void empty_BST(BST *bst);
bool search_BST(BST *bst, int value);
int BST_min(BST *bst);
int BST_max(BST *bst);
int BST_height(BST *bst);
Dynamic_Array BST_get_values(BST *bst);
int BST_kth_smallest(BST *bst, int k);
int BST_kth_largest(BST *bst, int k);

#endif

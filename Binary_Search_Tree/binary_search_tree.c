#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binary_search_tree.h"



BST create_BST(){
    BST bst;
    bst.root = NULL;
    bst.size = 0;

    return bst;

}

Node *successor(Node *node){
    Node *current = node->right;
    while(current->left != NULL){
        current = current->left;
    }
    return current;
}

void BST_insert(BST *bst, int value){
   
    Node* new_Node = malloc(sizeof(Node));
    new_Node->value = value;
    new_Node->left = NULL;
    new_Node->right = NULL;

    if(is_empty_BST(bst)){
        new_Node->parent = NULL;
        bst->root = new_Node;
        bst->size++;
        return;
    }

    Node *current = bst->root;
    while(true){
        if (value > current->value){
            if(current->right == NULL){
                new_Node->parent = current;
                current->right = new_Node;
                bst->size++;
                return;
            }
            
            current = current->right;
        }else if (value < current->value){
            if(current->left == NULL){
                new_Node->parent = current;
                current->left = new_Node;
                bst->size++;
                return;
            }

            current = current->left;
        }else{
            printf("Value already exists: %d\n", value);
            free(new_Node);
            return;
        }

    }

}


void BST_delete(BST *bst, int value){
    if(is_empty_BST(bst)){
        printf("BST is empty\n");
        return;
    }
    
    Node *current = bst->root;

    if(current->value == value){
        if(current->right == NULL && current->left == NULL){
            free(bst->root);
            bst->size--;
            bst->root = NULL;
            return;
        }else if (current->right == NULL){
            free(bst->root);
            bst->size--;
            bst->root = current->left;
            return;
        }else if (current->left == NULL){
            free(bst->root);
            bst->size--;
            bst->root = current->right;
            return;
        }else{
            Node *success = successor(current);
            Node *succ_parent = success->parent;

            Node *Right = current->right;
            Node *Left = current->left;

            Node *succ_right = success->right;
            if(success->right == NULL){

                free(bst->root);
                bst->size--;
                success->parent = NULL;
                if(success != current->right){
    
                    success->right = Right;
                    if(Right != NULL) Right->parent = success;
                    succ_parent->left = NULL;
                }
                success->left = Left;
                if(Left != NULL) Left->parent = success;
                bst->root = success;
                return;
                
            }else{
                 
                free(bst->root);
                bst->size--;
                success->parent = NULL;
                if(success != current->right){
    
                    success->right = Right;
                    if(Right != NULL) Right->parent = success;
                    succ_parent->left = succ_right;
                    succ_right->parent = succ_parent;
                }
                success->left = Left;
                if(Left != NULL) Left->parent = success;
                bst->root = success;
                return;
            }
        }
    }else{
        
        while(current->value != value){
            if (value < current->value){
                current = current->left;
            } else if (value > current->value){
                current = current->right;
            }
            if(current == NULL){
               printf("Value not found\n");
               return;
            }
        }


        if(current->right == NULL && current->left == NULL){
            if(current->parent->right == current) current->parent->right = NULL;
            if(current->parent->left == current) current->parent->left = NULL;
            free(current);
            bst->size--;
            return;
        }else if (current->right == NULL){
            if(current->parent->right == current) current->parent->right = current->left;
            if(current->parent->left == current) current->parent->left = current->left;
            current->left->parent = current->parent;
            free(current);
            bst->size--;
            return;
        }else if (current->left == NULL){
            if(current->parent->right == current) current->parent->right = current->right;
            if(current->parent->left == current) current->parent->left = current->right;
            current->right->parent = current->parent;
            free(current);
            bst->size--;
            return;
        }else{
            Node *success = successor(current);
            Node *succ_parent = success->parent;

            Node *Right = current->right;
            Node *Left = current->left;

            Node *succ_right = success->right;
            if(success->right == NULL){
                success->parent = current->parent;
                
                bst->size--;
                
                if(success != current->right){
    
                    success->right = Right;
                    if(Right != NULL) Right->parent = success;
                    succ_parent->left = NULL;
                }
                success->left = Left;
                if(Left != NULL) Left->parent = success;

                if(current->parent->right == current) current->parent->right = success;
                if(current->parent->left == current) current->parent->left = success;
                free(current);
                return;
                
            }else{
                 
                
                bst->size--;
                success->parent = current->parent;
                if(success != current->right){
    
                    success->right = Right;
                    if(Right != NULL) Right->parent = success;
                    succ_parent->left = succ_right;
                    if(succ_right != NULL) succ_right->parent = succ_parent;
                }
                success->left = Left;
                if(Left != NULL) Left->parent = success;
                if(current->parent->right == current) current->parent->right = success;
                if(current->parent->left == current) current->parent->left = success;
                free(current);
                return;
            }
        }

        
    }
}

void empty_node(BST *bst, Node *node){
    if(node == NULL) return;
    empty_node(bst, node->left);
    if (node != bst->root){
        if(node->parent->left == node) node->parent->left = NULL;
        if(node->parent->right == node) node->parent->right = NULL;
    }else{
        bst->root = NULL;
    }
    Node *r = node->right;
    free(node);
    empty_node(bst, r);
}

void empty_BST(BST *bst){
   empty_node(bst, bst->root);
   bst->size = 0;
}

bool search_BST(BST *bst, int value){
    if(is_empty_BST(bst)){
        return false;
    }
    Node *current = bst->root;
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

void print_node(Node *node){
    if(node == NULL) return;
    print_node(node->left);
    printf("%d ", node->value);
    print_node(node->right);
}
void print_BST(BST *bst){
    if(is_empty_BST(bst)) 
    {
        printf("BST is empty\n");
        return;
    }
    print_node(bst->root);
}

int BST_length(BST *bst){
    return bst->size;
}

bool is_empty_BST(BST *bst){
    return bst->root == NULL;
}

bool is_leaf_BST_Node(Node *node){
    return (node->left == NULL && node->right == NULL);
}

int BST_min(BST *bst){
    if(is_empty_BST(bst)){
        printf("BST is empty: ");
        return 0;
    }
    Node *current = bst->root;
    while(current->left != NULL){
        current = current->left;
    }

    return current->value;
    
}

int BST_max(BST *bst){
    if(is_empty_BST(bst)){
        printf("BST is empty: ");
        return 0;
    }
    Node *current = bst->root;
    while(current->right != NULL){
        current = current->right;
    }

    return current->value;
    
}


int Node_height(Node *node){
    if(node == NULL) return 0;
    int left = Node_height(node->left);
    int right = Node_height(node->right);
    return 1 + (left > right ? left : right);
}
int BST_height(BST *bst){
    return Node_height(bst->root);
}



void nodes(Dynamic_Array *arr, Node *node){
    if(node == NULL) return;
    nodes(arr, node->left);
    dynamic_array_append(arr, node->value);
    nodes(arr, node->right);
}

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


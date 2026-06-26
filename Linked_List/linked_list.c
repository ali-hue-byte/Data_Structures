/*
  This file provides necessary functions to implement a Circular Doubly Linked List (CDLL).

  A Linked List is implemented using nodes, each node has a pointer to the next one.
  Nodes of a doubly Linked list have also a pointer to the previous node.
  And a circular Linked List is a Linked List where the last element points to the first.

  A Circular Doubly Linked List has all characteristics of those Linked List types.

  Possible operations :
  - push_back: Add an element to the back of the linked list
  - push_front: Add an element to the front of the linked list
  - insert: Add a new element after or before a node
  - update: Change a value in a specific node
  - delete: Removes a node

*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "linked_list.h"


// Creates a new Circular Doubly Linked List
Circular_Double_Linked_List create_CDLL(){
    Circular_Double_Linked_List CDLL;
    CDLL.head = NULL;
    CDLL.size = 0;
    return CDLL;
}

// Adds a new node to the back of the linked list
CDLL_Node *CDLL_push_back(Circular_Double_Linked_List *lst, int value){
    CDLL_Node *newNode = malloc(sizeof(CDLL_Node));
    newNode->data = value;
    newNode->CDLL = lst; 
    if(CDLL_is_empty(lst)){
        // New node is the header and points to itself
        newNode->next = newNode;
        newNode->previous = newNode;
        lst->head = newNode;
        
    }else{
        // New node is head's previous and last Node's next
        CDLL_Node *last = lst->head->previous; 

        newNode->next = lst->head;
        newNode->previous = last;
        lst->head->previous = newNode; 
        last->next = newNode;
    }
    lst->size++;
    return newNode;
}

// Adds a new node to the front of the linked list
CDLL_Node *CDLL_push_front(Circular_Double_Linked_List *lst, int value){
    CDLL_Node *newNode = malloc(sizeof(CDLL_Node));
    newNode->data = value;
    newNode->CDLL = lst;
    if(CDLL_is_empty(lst)){
        // New node is the header and points to itself
        newNode->next = newNode;
        newNode->previous = newNode;
        lst->head = newNode;
        
    }else{
        // New node is the new head
        CDLL_Node *last = lst->head->previous; 

        newNode->next = lst->head;
        newNode->previous = last;

        lst->head->previous = newNode;
        last->next = newNode;

        lst->head = newNode;
    }
    lst->size++;
    return newNode;
}

// Adds a new node after a given one
CDLL_Node *CDLL_insert_after(Circular_Double_Linked_List *lst, CDLL_Node *node, int value){
    if(node == NULL || node->CDLL != lst){
        printf("Node doesn't belong to this list\n");
        return NULL;
    }

    if(CDLL_is_empty(lst)){
        printf("The linked list is empty \n");
        return NULL;
    }

    CDLL_Node *newNode = malloc(sizeof(CDLL_Node));
    CDLL_Node *node_next = node->next;

    newNode->data = value;
    newNode->CDLL = lst;
    lst->size++;
    
    // Adds the new node between the given node and it's next
    newNode->previous = node;
    newNode->next = node_next;

    node_next->previous = newNode;
    node->next = newNode;

    return newNode;

}
// Adds a new node before a given one
CDLL_Node *CDLL_insert_before(Circular_Double_Linked_List *lst, CDLL_Node *node, int value){
    if(node == NULL || node->CDLL != lst){
        printf("Node doesn't belong to this list\n");
        return NULL;
    }

    if(CDLL_is_empty(lst)){
        printf("The linked list is empty \n");
        return NULL;
    }

    CDLL_Node *newNode = malloc(sizeof(CDLL_Node));
    CDLL_Node *node_previous = node->previous;

    newNode->data = value;
    newNode->CDLL = lst;
    lst->size++;

    // Adds the new node between the given node and it's previous
    newNode->next = node;
    newNode->previous = node_previous;
    node_previous->next = newNode;
    node->previous = newNode;
    return newNode;

}

// Returns the value stored in a given node
int CDLL_get_node_value(Circular_Double_Linked_List *lst, CDLL_Node *node){
    if(node == NULL || node->CDLL != lst){
        printf("Node doesn't belong to this list ");
        return -1;
    }
    return node->data;
}

// Returns the value in the front of the Linked List
int CDLL_front(Circular_Double_Linked_List *lst){
    if(CDLL_is_empty(lst)){
        printf("The linked list is empty ");
        return -1;
    }
    return lst->head->data;
}

// Returns the value in the back of the Linked List
int CDLL_back(Circular_Double_Linked_List *lst){
    if(CDLL_is_empty(lst)){
        printf("The linked list is empty ");
        return -1;
    }
    return lst->head->previous->data;
}

// Returns and removes the value in the front of the Linked List
int CDLL_pop_front(Circular_Double_Linked_List *lst){
    if(CDLL_is_empty(lst)){
        printf("The linked list is empty ");
        return -1;
    }
    CDLL_Node *old = lst->head;
    int val = old->data;
    
    if(old == old->next){
        lst->head = NULL;
    }else {
        CDLL_Node *new_head = old->next;
        CDLL_Node *head_previous = old->previous;
        
        new_head->previous = head_previous;
        head_previous->next = new_head;

        lst->head = new_head;
    }

    
    free(old);
    lst->size--;

    return val;
    
}

// Returns and removes the value in the back of the Linked List
int CDLL_pop_back(Circular_Double_Linked_List *lst){
    if(CDLL_is_empty(lst)){
        printf("The linked list is empty ");
        return -1;
    }
    CDLL_Node *old = lst->head->previous;
    int val = old->data;
    
    if(old == old->next){
        lst->head = NULL;
    }else {
        CDLL_Node *new_last = old->previous;
        new_last->next = lst->head;
        lst->head->previous = new_last;
    }

    
    free(old);
    lst->size--;

    return val;
    
}

// Changes the value at a given node
void CDLL_update_node_value(Circular_Double_Linked_List *lst, CDLL_Node *node, int value){
    if(node == NULL || node->CDLL != lst){
        printf("Node doesn't belong to this list \n");
        return;
    }
    node->data = value;
}

// Deletes a given node
void CDLL_delete_node(Circular_Double_Linked_List *lst, CDLL_Node *node){
    if(node == NULL || node->CDLL != lst){
        printf("Node doesn't belong to this list \n");
        return;
    }
    if(node == node->next){
        lst->head = NULL;
    }else{
        CDLL_Node *previous = node->previous;
        CDLL_Node *next = node->next;
        previous->next = next;
        next->previous = previous;

        if (lst->head == node) {
            lst->head = next;
        }

    }
    
    free(node);
    lst->size--;
}

// Prints the Linked List
void print_CDLL(Circular_Double_Linked_List *lst){
    if(CDLL_is_empty(lst)){
        printf("The linked list is empty\n");
        return;
    }
    CDLL_Node *current = lst->head;
    CDLL_Node *head = current;
    
    do{
        printf("%d ", current->data);
        current = current->next;
    }while(current != head);
}

// Returns number of elements in the linked list
int CDLL_get_length(Circular_Double_Linked_List *lst){
    return lst->size;
}

// Checks if the Linked List is empty
bool CDLL_is_empty(Circular_Double_Linked_List *lst){
    return lst->head == NULL;
}

// Frees all the Nodes of the linked list
void empty_CDLL(Circular_Double_Linked_List *lst){
    if(lst->head == NULL) return;
    
    CDLL_Node *head = lst->head;
    CDLL_Node *current = head;
    CDLL_Node *next;
    do{
        next = current->next;
        free(current);
        current = next;
    }while(current != head);
    lst->size = 0;
    lst->head = NULL;
}


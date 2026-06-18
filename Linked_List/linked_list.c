/*
  This file provides necessary functions to implement a Circular Doubly Linked List (CDLL).

  A Linked List is implemented using nodes, each node has a pointer to the next one.
  Nodes of a doubly Linked list have also a pointer to the previous node.
  And a circular Linked List is a Linked List where the last element points to the first.

  Do a Circular Doubly Linked List had all characteristics of those Linked list types.

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



Circular_Double_Linked_List create_CDLL(){
    Circular_Double_Linked_List CDLL;
    CDLL.head = NULL;
    CDLL.size = 0;
    return CDLL;
}

Node *CDLL_push_back(Circular_Double_Linked_List *lst, int value){
    Node *newNode = malloc(sizeof(Node));
    newNode->data = value;
    newNode->CDLL = lst;
    if(CDLL_is_empty(lst)){
        newNode->next = newNode;
        newNode->previous = newNode;
        lst->head = newNode;
        
    }else{
        Node *last = lst->head->previous; 
        newNode->next = lst->head;
        newNode->previous = last;
        lst->head->previous = newNode;
        last->next = newNode;
    }
    lst->size++;
    return newNode;
}
Node *CDLL_push_front(Circular_Double_Linked_List *lst, int value){
    Node *newNode = malloc(sizeof(Node));
    newNode->data = value;
    newNode->CDLL = lst;
    if(CDLL_is_empty(lst)){
        newNode->next = newNode;
        newNode->previous = newNode;
        lst->head = newNode;
        
    }else{
        Node *last = lst->head->previous; 
        newNode->next = lst->head;
        newNode->previous = last;
        lst->head->previous = newNode;
        last->next = newNode;
        lst->head = newNode;
    }
    lst->size++;
    return newNode;
}

Node *CDLL_insert_after(Circular_Double_Linked_List *lst, Node *node, int value){
    if(node == NULL || node->CDLL != lst){
        printf("Node doesn't belong to this list\n");
        return NULL;
    }

    Node *newNode = malloc(sizeof(Node));
    Node *node_next = node->next;

    newNode->data = value;
    newNode->CDLL = lst;
    lst->size++;

    newNode->previous = node;
    newNode->next = node_next;
    node_next->previous = newNode;
    node->next = newNode;
    return newNode;

}

Node *CDLL_insert_before(Circular_Double_Linked_List *lst, Node *node, int value){
    if(node == NULL || node->CDLL != lst){
        printf("Node doesn't belong to this list\n");
        return NULL;
    }

    Node *newNode = malloc(sizeof(Node));
    Node *node_previous = node->previous;

    newNode->data = value;
    newNode->CDLL = lst;
    lst->size++;

    newNode->next = node;
    newNode->previous = node_previous;
    node_previous->next = newNode;
    node->previous = newNode;
    return newNode;

}

int CDLL_get_node_value(Circular_Double_Linked_List *lst, Node *node){
    if(node == NULL || node->CDLL != lst){
        printf("Node doesn't belong to this list ");
        return -1;
    }
    return node->data;
}

int CDLL_front(Circular_Double_Linked_List *lst){
    if(CDLL_is_empty(lst)){
        printf("The linked list is empty ");
        return -1;
    }
    return lst->head->data;
}

int CDLL_back(Circular_Double_Linked_List *lst){
    if(CDLL_is_empty(lst)){
        printf("The linked list is empty ");
        return -1;
    }
    return lst->head->previous->data;
}

int CDLL_pop_front(Circular_Double_Linked_List *lst){
    if(CDLL_is_empty(lst)){
        printf("The linked list is empty ");
        return -1;
    }
    Node *old = lst->head;
    int val = old->data;
    
    if(old == old->next){
        lst->head = NULL;
    }else {
        Node *new_head = old->next;
        Node *head_previous = old->previous;
        
        new_head->previous = head_previous;
        head_previous->next = new_head;

        lst->head = new_head;
    }

    
    free(old);
    lst->size--;

    return val;
    
}


int CDLL_pop_back(Circular_Double_Linked_List *lst){
    if(CDLL_is_empty(lst)){
        printf("The linked list is empty ");
        return -1;
    }
    Node *old = lst->head->previous;
    int val = old->data;
    
    if(old == old->next){
        lst->head = NULL;
    }else {
        Node *new_last = old->previous;
        new_last->next = lst->head;
        lst->head->previous = new_last;
    }

    
    free(old);
    lst->size--;

    return val;
    
}

void CDLL_update_node_value(Circular_Double_Linked_List *lst, Node *node, int value){
    if(node == NULL || node->CDLL != lst){
        printf("Node doesn't belong to this list \n");
        return;
    }
    node->data = value;
}

void CDLL_delete_node(Circular_Double_Linked_List *lst, Node *node){
    if(node == NULL || node->CDLL != lst){
        printf("Node doesn't belong to this list \n");
        return;
    }
    if(node == node->next){
        lst->head = NULL;
    }else{
        Node *previous = node->previous;
        Node *next = node->next;
        previous->next = next;
        next->previous = previous;

        if (lst->head == node) {
            lst->head = next;
        }

    }
    
    free(node);
    lst->size--;
}

void print_CDLL(Circular_Double_Linked_List *lst){
    if(CDLL_is_empty(lst)){
        printf("The linked list is empty\n");
        return;
    }
    Node *current = lst->head;
    Node *head = current;
    
    do{
        printf("%d ", current->data);
        current = current->next;
    }while(current != head);
}

int CDLL_get_length(Circular_Double_Linked_List *lst){
    return lst->size;
}

bool CDLL_is_empty(Circular_Double_Linked_List *lst){
    return lst->head == NULL;
}


void empty_CDLL(Circular_Double_Linked_List *lst){
    if(CDLL_is_empty(lst)){
        printf("Linked list is already empty\n");
        return;
    }
    Node *head = lst->head;
    Node *current = head;
    Node *next;
    do{
        next = current->next;
        free(current);
        current = next;
    }while(current != head);
    lst->size = 0;
    lst->head = NULL;
}

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Circular_Double_Linked_List Circular_Double_Linked_List;

typedef struct CDLL_Node{
    int data;
    struct CDLL_Node *next;
    struct CDLL_Node *previous;
    Circular_Double_Linked_List *CDLL;
} CDLL_Node;

struct Circular_Double_Linked_List{
    CDLL_Node *head;
    int size;
};

Circular_Double_Linked_List create_CDLL();
CDLL_Node *CDLL_push_back(Circular_Double_Linked_List *lst, int value);
CDLL_Node *CDLL_push_front(Circular_Double_Linked_List *lst, int value);
CDLL_Node *CDLL_insert_after(Circular_Double_Linked_List *lst, CDLL_Node *node, int value);
CDLL_Node *CDLL_insert_before(Circular_Double_Linked_List *lst, CDLL_Node *node, int value);
int CDLL_get_node_value(Circular_Double_Linked_List *lst, CDLL_Node *node);
int CDLL_front(Circular_Double_Linked_List *lst);
int CDLL_back(Circular_Double_Linked_List *lst);
int CDLL_pop_front(Circular_Double_Linked_List *lst);
int CDLL_pop_back(Circular_Double_Linked_List *lst);
void CDLL_update_node_value(Circular_Double_Linked_List *lst, CDLL_Node *node, int value);
void CDLL_delete_node(Circular_Double_Linked_List *lst, CDLL_Node *node);
void print_CDLL(Circular_Double_Linked_List *lst);
int CDLL_get_length(Circular_Double_Linked_List *lst);
bool CDLL_is_empty(Circular_Double_Linked_List *lst);
void empty_CDLL(Circular_Double_Linked_List *lst);


#endif

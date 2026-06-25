#ifndef Graph_H
#define Graph_H

#include "../Array/dynamic_array.h"

typedef struct Vertex Vertex;

typedef struct elem_Graph{
   int key;
   Vertex *value;
   struct elem_Graph *next;
}elem_Graph;

typedef struct {
    elem_Graph **pair;
    int size;
    int capacity;
}Hash_Table_Graph;


int Hash_function(int key, int capacity);

Hash_Table_Graph  create_hash_table_graph();
bool is_empty_hash_table_graph(Hash_Table_Graph *h_t);
bool key_in_hash_table_graph(Hash_Table_Graph *h_t, int key);
void hash_table_graph_add(Hash_Table_Graph *h_t, int key, Vertex *value);
Vertex *hash_table_graph_get(Hash_Table_Graph *h_t, int key);
void hash_table_graph_delete(Hash_Table_Graph *h_t, int key);
void hash_table_graph_empty(Hash_Table_Graph *h_t);
void destroy_hash_table_graph(Hash_Table_Graph *h_t);
int hash_table_graph_size(Hash_Table_Graph *h_t);
void hash_table_graph_update(Hash_Table_Graph *h_t, int key, Vertex *value);





typedef struct Edge { 
    int weight;
    int destination_id;
    struct Edge *next_Edge;

}Edge;

struct Vertex {
    int id;
    int value;
    Edge *Edges_list;
    
};

typedef struct {
    Hash_Table_Graph vertices;
    int next_id;
    bool is_weighted;
    bool is_direct;
} Graph;

Graph create_graph(bool is_weighted, bool is_direct);
int add_vertex_graph(Graph *graph, int value);
void add_edge_graph(Graph *graph, int from, int to, int weight, bool is_id);
int get_edge_weight_graph(Graph *graph, int from, int to, bool is_id);
bool edge_exists_graph(Graph *graph, int from, int to, bool is_id);
Dynamic_Array get_neighbors_ids(Graph *graph, int id);
Dynamic_Array get_neighbors_values(Graph *graph, int value);
bool is_empty_graph(Graph *graph);
int graph_length(Graph *graph);
bool vertex_id_exists_graph(Graph *graph, int id);
bool vertex_value_exists_graph(Graph *graph, int value);
void print_graph_ids(Graph *graph);
void print_graph_values(Graph *graph);
void remove_edge_graph(Graph *graph, int from, int to, bool is_id);
void remove_vertex_graph(Graph *graph, int nb, bool is_id);


#endif

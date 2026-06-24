#ifndef Graph_H
#define Graph_H


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




#endif

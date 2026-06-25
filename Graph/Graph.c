#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"



Graph create_graph(bool is_weighted, bool is_direct){
    Graph graph;
    
    graph.next_id = 0;
    graph.vertices = create_hash_table_graph();
    graph.is_direct = is_direct;
    graph.is_weighted = is_weighted;
    return graph;
}

int add_vertex_graph(Graph *graph, int value){
    Vertex *new_vertex = malloc(sizeof(Vertex));
    new_vertex->value = value;
    new_vertex->id = graph->next_id;
    new_vertex->Edges_list = NULL;
    hash_table_graph_add(&graph->vertices, new_vertex->id, new_vertex);
    
    
    graph->next_id++;
    return new_vertex->id;
}



void add_edge_graph(Graph *graph, int from, int to, int weight, bool is_id){
    
    if(is_id){
        Edge *new_edge = malloc(sizeof(Edge));
        Vertex *v_to = hash_table_graph_get(&graph->vertices, to);
        if(v_to == NULL) {
            printf("Id not found: %d\n", to);
            free(new_edge);
            return;
        }
        Vertex *v_from = hash_table_graph_get(&graph->vertices, from);
        if(v_from == NULL) {
            printf("Id not found: %d\n", from);
            free(new_edge);
            return;
        }
        new_edge->weight = graph->is_weighted ? weight : 0;
        new_edge->destination_id = to;
        new_edge->next_Edge = v_from->Edges_list;
        v_from->Edges_list = new_edge;
        
        

        if(!graph->is_direct){
            Edge *new_edge2 = malloc(sizeof(Edge));
            new_edge2->weight = graph->is_weighted ? weight : 0;
            new_edge2->destination_id = from;
            new_edge2->next_Edge = v_to->Edges_list;
            v_to->Edges_list = new_edge2;
            

        }
        

    }else{
        elem_Graph *current_to = NULL;
        elem_Graph *current_from = NULL;
        for(int i = 0; i < graph->vertices.capacity; i++){
            if(current_to != NULL) break;
            current_to = graph->vertices.pair[i];
            while(current_to != NULL){
                if(current_to->value->value == to) break;
                current_to = current_to->next;
            }
        }
        for(int i = 0; i < graph->vertices.capacity; i++){
            if(current_from != NULL) break;
            current_from = graph->vertices.pair[i];
            while(current_from != NULL){
                if(current_from->value->value == from) break;
                current_from = current_from->next;
            }
        }

        if(current_to == NULL) {
            printf("Value doesn't exist: %d\n", to);
            return;
        }
        if(current_from == NULL) {
            printf("Value doesn't exist: %d\n", from);
            return;
        }


        Edge *new_edge = malloc(sizeof(Edge));
        Vertex *v_to = current_to->value;
        
        Vertex *v_from = current_from->value;
        
        new_edge->weight = graph->is_weighted ? weight : 0;
        new_edge->destination_id = v_to->id;
        
        new_edge->next_Edge = v_from->Edges_list;
        v_from->Edges_list = new_edge;

        if(!graph->is_direct){
            Edge *new_edge2 = malloc(sizeof(Edge));
            new_edge2->weight = graph->is_weighted ? weight : 0;
            new_edge2->destination_id = v_from->id;
            new_edge2->next_Edge = v_to->Edges_list;
            v_to->Edges_list = new_edge2;

        }
    }
        
    
}

int get_edge_weight_graph(Graph *graph, int from, int to, bool is_id){
    if(graph->is_weighted == false){
        printf("Graph is not weighted: ");
        return -1;
    }
    if (is_id){
        Vertex *v_from = hash_table_graph_get(&graph->vertices, from);
        Edge *current = v_from->Edges_list;
        while(current != NULL){
            if (current->destination_id == to) return current->weight;
            current = current->next_Edge;
        }
        return -1;

    }else{
        
        elem_Graph *current_from = NULL;
        for(int i = 0; i < graph->vertices.capacity; i++){
            if(current_from != NULL) break;
            current_from = graph->vertices.pair[i];
            while(current_from != NULL){
                if(current_from->value->value == from) break;
                current_from = current_from->next;
            }
        }

        elem_Graph *current_to = NULL;
        for(int i = 0; i < graph->vertices.capacity; i++){
            if(current_to != NULL) break;
            current_to = graph->vertices.pair[i];
            while(current_to != NULL){
                if(current_to->value->value == to) break;
                current_to = current_to->next;
            }
        }

        if(current_from == NULL || current_from->value->value != from) return -1;
        if(current_to == NULL || current_to->value->value != to) return -1;
        Edge *edge = current_from->value->Edges_list;
        while(edge != NULL){
            if(edge->destination_id == current_to->value->id) return edge->weight;
            edge = edge->next_Edge;
        }
        return -1;
        
    }
    
}

Dynamic_Array get_neighbors_ids(Graph *graph, int id){
    if(!vertex_id_exists_graph(graph, id)){
        printf("Id doesn't exist\n");
        return create_dynamic_array();
    }
    Dynamic_Array d_array = create_dynamic_array();
    Vertex *v = hash_table_graph_get(&graph->vertices, id);
    Edge *current = v->Edges_list;
    while(current != NULL){
        dynamic_array_append(&d_array, current->destination_id);
        current = current->next_Edge;
    }
    return d_array;

}

Dynamic_Array get_neighbors_values(Graph *graph, int value){

    elem_Graph *current = NULL;
    for(int i = 0; i < graph->vertices.capacity; i++){
        if(current != NULL) break;
        current = graph->vertices.pair[i];
        while(current != NULL){
            if(current->value->value == value) break;
            current = current->next;
        }
    }
    if(current == NULL || current->value->value != value){
        printf("Value doesn't exist\n");
        return create_dynamic_array();
    }
    
    Dynamic_Array d_array = create_dynamic_array();

    Edge *edge = current->value->Edges_list;
    while(edge != NULL){
        Vertex *v = hash_table_graph_get(&graph->vertices, edge->destination_id);
        dynamic_array_append(&d_array, v->value);
        edge = edge->next_Edge;
    }
    return d_array;
}


bool edge_exists_graph(Graph *graph, int from, int to, bool is_id){
    if (is_id){
        Vertex *v_from = hash_table_graph_get(&graph->vertices, from);
        Edge *current = v_from->Edges_list;
        while(current != NULL){
            if (current->destination_id == to) return true;
            current = current->next_Edge;
        }
        return false;

    }else{
        
        elem_Graph *current_from = NULL;
        for(int i = 0; i < graph->vertices.capacity; i++){
            if(current_from != NULL) break;
            current_from = graph->vertices.pair[i];
            while(current_from != NULL){
                if(current_from->value->value == from) break;
                current_from = current_from->next;
            }
        }

        elem_Graph *current_to = NULL;
        for(int i = 0; i < graph->vertices.capacity; i++){
            if(current_to != NULL) break;
            current_to = graph->vertices.pair[i];
            while(current_to != NULL){
                if(current_to->value->value == to) break;
                current_to = current_to->next;
            }
        }

        if(current_from == NULL || current_from->value->value != from) return false;
        if(current_to == NULL || current_to->value->value != to) return false;
        Edge *edge = current_from->value->Edges_list;
        while(edge != NULL){
            if(edge->destination_id == current_to->value->id) return true;
            edge = edge->next_Edge;
        }
        return false;
        
    }
}

bool is_empty_graph(Graph *graph){
    return graph->vertices.size == 0;
}

int graph_length(Graph *graph){
    return graph->vertices.size;
}

bool vertex_id_exists_graph(Graph *graph, int id){
    return key_in_hash_table_graph(&graph->vertices, id);
}


bool vertex_value_exists_graph(Graph *graph, int value){
    for(int i = 0; i < graph->vertices.capacity; i++){
        elem_Graph *current = graph->vertices.pair[i];
        while(current != NULL){
            if(current->value->value == value) return true;
            current = current->next;
        }
    }
    return false;
}

void print_graph_ids(Graph *graph){
    if(is_empty_graph(graph)) {
        printf("Graph is empty\n");
        return;
    }

    printf("Id  :  Neighbors(weight)\n");
    for(int i = 0; i<graph->vertices.capacity; i++){
        elem_Graph *current = graph->vertices.pair[i];
        if(current == NULL) continue;
        
        while(current != NULL){
            printf("%d  : ", current->key);
            Edge *current_v = current->value->Edges_list;
            while(current_v != NULL){
                printf("%d(%d) ", current_v->destination_id, current_v->weight);
                current_v = current_v->next_Edge;
            }
            printf("\n");
            current = current->next;
        }
        
    }
}

void print_graph_values(Graph *graph){
    if(is_empty_graph(graph)) {
        printf("Graph is empty\n");
        return;
    }

    printf("Value  :  Neighbors(weight)\n");
    for(int i = 0; i<graph->vertices.capacity; i++){
        elem_Graph *current = graph->vertices.pair[i];
        if(current == NULL) continue;
        
        while(current != NULL){
            printf("%d  : ", current->value->value);
            Edge *current_v = current->value->Edges_list;
            while(current_v != NULL){
                int id = current_v->destination_id;
                Vertex *id_vertex = hash_table_graph_get(&graph->vertices, id);
                printf("%d(%d) ", id_vertex->value, current_v->weight);
                current_v = current_v->next_Edge;
            }
            printf("\n");
            current = current->next;
        }
    }
}

void remove_edge_graph(Graph *graph, int from, int to, bool is_id){
    if(is_id){
        bool found = false;
        Vertex *from_v = hash_table_graph_get(&graph->vertices, from);
        if(from_v == NULL){
            printf("Id doesn't exist: %d\n", from);
            return;
        }
        Edge *current = from_v->Edges_list;
        if (current == NULL){
            printf("Edge doesn't exist\n");
            return;
        }
        if(current->destination_id == to){
            from_v->Edges_list = current->next_Edge;
            free(current);
            if(graph->is_direct) return;
            found = true;
            
        }
        if(!found){
            Edge *old = current;
            current = current->next_Edge;
            while(current != NULL){
                if(current->destination_id == to){
                    old->next_Edge = current->next_Edge;
                    free(current);
                    if(graph->is_direct) return;
                    break;
                }
                old = current;
                current = current->next_Edge;
            }
        }
       

        if(!graph->is_direct){
            Vertex *to_v = hash_table_graph_get(&graph->vertices, to);
            if(to_v == NULL){
            printf("Id doesn't exist: %d\n", to);
            return;
        }
            Edge *current2 = to_v->Edges_list;
            if(current2 == NULL){
                printf("Edge doesn't exist\n");
                return;
            }
            if(current2->destination_id == from){
                to_v->Edges_list = current2->next_Edge;
                free(current2);
                return;
            }
            Edge *old2 = current2;
            current2 = current2->next_Edge;
            while(current2 != NULL){
                if(current2->destination_id == from){
                    old2->next_Edge = current2->next_Edge;
                    free(current2);
                    return;

                }
                old2 = current2;
                current2 = current2->next_Edge;
            }
        }
        printf("Edge doesn't exist\n");
    }else{

        elem_Graph *current_from = NULL;
        for(int i = 0; i < graph->vertices.capacity; i++){
            if(current_from != NULL) break;
            current_from = graph->vertices.pair[i];
            while(current_from != NULL){
                if(current_from->value->value == from) break;
                current_from = current_from->next;
            }
        }

        elem_Graph *current_to = NULL;
        for(int i = 0; i < graph->vertices.capacity; i++){
            if(current_to != NULL) break;
            current_to = graph->vertices.pair[i];
            while(current_to != NULL){
                if(current_to->value->value == to) break;
                current_to = current_to->next;
            }
        }

        if(current_from == NULL || current_from->value->value != from) {
            printf("Value doesn't exist: %d\n", from);
            return;
        }
        if(current_to == NULL || current_to->value->value != to)  {
            printf("Value doesn't exist: %d\n", to);
            return;
        }

        bool found = false;
        Edge *current = current_from->value->Edges_list;
        if (current == NULL){
            printf("Edge doesn't exist\n");
            return;
        }
        if(current->destination_id == current_to->value->id){
            current_from->value->Edges_list = current->next_Edge;
            free(current);
            if(graph->is_direct) return;
            found = true;
            
        }
        if(!found){
            Edge *old = current;
            current = current->next_Edge;
            while(current != NULL){
                if(current->destination_id == current_to->value->id){
                    old->next_Edge = current->next_Edge;
                    free(current);
                    if(graph->is_direct) return;
                    break;
                }
                old = current;
                current = current->next_Edge;
            }
        }

        if(!graph->is_direct){
            
            Edge *current2 = current_to->value->Edges_list;
            if(current2 == NULL){
                printf("Edge doesn't exist\n");
                return;
            }
            if(current2->destination_id == current_from->value->id){
                current_to->value->Edges_list = current2->next_Edge;
                free(current2);
                return;
            }
            Edge *old2 = current2;
            current2 = current2->next_Edge;
            while(current2 != NULL){
                if(current2->destination_id == current_from->value->id){
                    old2->next_Edge = current2->next_Edge;
                    free(current2);
                    return;

                }
                old2 = current2;
                current2 = current2->next_Edge;
            }
        }
        printf("Edge doesn't exist\n");



    }
}

void remove_vertex_graph(Graph *graph, int nb, bool is_id){
    if(is_id){
        Vertex *vert = hash_table_graph_get(&graph->vertices, nb);
        if(vert == NULL){
            printf("Id doesn't exist: %d\n", nb);
            return;
        }
        Edge *current = vert->Edges_list;
        while(current != NULL){
            Edge *next = current->next_Edge;
            free(current);
            current = next;
        }
        hash_table_graph_delete(&graph->vertices, nb);

        for(int i = 0; i < graph->vertices.capacity; i++){
            elem_Graph *current = graph->vertices.pair[i];
            if(current == NULL) continue;
        
            while(current != NULL){
                
                Edge *current_v = current->value->Edges_list;

                while(current_v != NULL && current_v->destination_id == nb){
                    current->value->Edges_list = current_v->next_Edge;
                    Edge *s = current_v->next_Edge;
                    free(current_v);
                    current_v = s;

                }

                if(current_v != NULL){
                    Edge *old = current_v;
                    current_v = current_v->next_Edge;
                    while(current_v != NULL){
                        if(current_v->destination_id == nb){
                            old->next_Edge = current_v->next_Edge;
                            free(current_v);
                            current_v = old->next_Edge;
                        }else{
                            old = current_v;
                            current_v = current_v->next_Edge;

                        }
                    
                    }

                }
                
                current = current->next;
            }
        
        }
        

    }else{
        elem_Graph *current_from = NULL;
        for(int i = 0; i < graph->vertices.capacity; i++){
            if(current_from != NULL) break;
            current_from = graph->vertices.pair[i];
            while(current_from != NULL){
                if(current_from->value->value == nb) break;
                current_from = current_from->next;
            }
        }
        if(current_from == NULL || current_from->value->value != nb){
            printf("Value doesn't exist: %d\n", nb);
            return;
        }

        Vertex *vert = current_from->value;
        int id = vert->id;
        
        Edge *current = vert->Edges_list;
        while(current != NULL){
            Edge *next = current->next_Edge;
            free(current);
            current = next;
        }
        hash_table_graph_delete(&graph->vertices, id);

        for(int i = 0; i < graph->vertices.capacity; i++){
            elem_Graph *current = graph->vertices.pair[i];
            if(current == NULL) continue;
        
            while(current != NULL){
                
                Edge *current_v = current->value->Edges_list;

                while(current_v != NULL && current_v->destination_id == id){
                    current->value->Edges_list = current_v->next_Edge;
                    Edge *s = current_v->next_Edge;
                    free(current_v);
                    current_v = s;

                }

                if(current_v != NULL){
                    Edge *old = current_v;
                    current_v = current_v->next_Edge;
                    while(current_v != NULL){
                        if(current_v->destination_id == id){
                            old->next_Edge = current_v->next_Edge;
                            free(current_v);
                            current_v = old->next_Edge;
                        }else{
                            old = current_v;
                            current_v = current_v->next_Edge;

                        }
                    
                    }

                }
                
                current = current->next;
            }
        
        }

    }

}

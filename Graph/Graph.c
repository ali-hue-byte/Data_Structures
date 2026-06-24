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


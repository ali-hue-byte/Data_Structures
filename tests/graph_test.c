/*
Graph_test.c

Purpose:
Tests the correctness of the Graph implementation.

Covered scenarios:
- Empty graph handling
- Undirected unweighted: add vertices and edges (by value and by id)
- Directed unweighted: edge directionality
- Undirected weighted: edge weights
- Directed weighted: full graph type
- Duplicate vertex prevention
- Edge existence check (by id and by value)
- Get neighbors (by id and by value)
- Get edge weight (by id and by value)
- Remove edge (by id and by value)
- Remove vertex and its connected edges (by id and by value)
- Non-existent vertex/edge error handling
- Empty after operations and reuse
- Print correctness (by ids and by values)
- Stress test
*/

#include <stdio.h>
#include <stdlib.h>
#include "../Graph/Graph.h"

int main(){

    // Test 1: Empty graph
    // Verifies that a newly created graph is empty
    // and has 0 vertices and 0 edges
    printf("=== Test 1 ===\n\n");

    Graph g = create_graph(false, false);
    printf("Empty?: %s\n", is_empty_graph(&g) ? "yes" : "no");
    printf("Vertices: %d\n", graph_length(&g));
    printf("Edges: %d\n\n", graph_edges_nb(&g));

    // Test 2: Undirected unweighted graph (by value)
    // Verifies vertices and edges are added correctly,
    // and that undirected edges exist in both directions
    printf("=== Test 2 ===\n\n");

    int id_a = add_vertex_graph(&g, 1);
    int id_b = add_vertex_graph(&g, 2);
    int id_c = add_vertex_graph(&g, 3);
    int id_d = add_vertex_graph(&g, 4);

    add_edge_graph(&g, 1, 2, 0, false); // by value
    add_edge_graph(&g, 2, 3, 0, false);
    add_edge_graph(&g, 3, 4, 0, false);
    add_edge_graph(&g, 1, 4, 0, false);

    printf("Vertices: %d\n", graph_length(&g));
    printf("Edges (expect 4): %d\n", graph_edges_nb(&g));
    printf("Edge 1->2 (expect yes): %s\n", edge_exists_graph(&g, 1, 2, false) ? "yes" : "no");
    printf("Edge 2->1 undirected (expect yes): %s\n", edge_exists_graph(&g, 2, 1, false) ? "yes" : "no");
    printf("Edge 1->3 (expect no): %s\n", edge_exists_graph(&g, 1, 3, false) ? "yes" : "no");
    printf("Vertex 1 exists (expect yes): %s\n", vertex_value_exists_graph(&g, 1) ? "yes" : "no");
    printf("Vertex 9 exists (expect no): %s\n\n", vertex_value_exists_graph(&g, 9) ? "yes" : "no");

    // Test 3: Undirected unweighted graph (by id)
    // Verifies the same operations work correctly using IDs
    printf("=== Test 3 ===\n\n");

    printf("Edge id_a->id_b by id (expect yes): %s\n", edge_exists_graph(&g, id_a, id_b, true) ? "yes" : "no");
    printf("Edge id_b->id_a by id undirected (expect yes): %s\n", edge_exists_graph(&g, id_b, id_a, true) ? "yes" : "no");
    printf("Edge id_a->id_c by id (expect no): %s\n", edge_exists_graph(&g, id_a, id_c, true) ? "yes" : "no");
    printf("Vertex id_a exists (expect yes): %s\n", vertex_id_exists_graph(&g, id_a) ? "yes" : "no");
    printf("Vertex 99 exists (expect no): %s\n\n", vertex_id_exists_graph(&g, 99) ? "yes" : "no");

    // Test 4: Directed unweighted graph
    // Verifies that edges only exist in the specified direction
    printf("=== Test 4 ===\n\n");

    Graph g2 = create_graph(false, true);
    int id1 = add_vertex_graph(&g2, 10);
    int id2 = add_vertex_graph(&g2, 20);
    int id3 = add_vertex_graph(&g2, 30);

    add_edge_graph(&g2, 10, 20, 0, false); // by value
    add_edge_graph(&g2, 20, 30, 0, false);

    printf("Directed edge 10->20 (expect yes): %s\n", edge_exists_graph(&g2, 10, 20, false) ? "yes" : "no");
    printf("Reverse 20->10 (expect no): %s\n", edge_exists_graph(&g2, 20, 10, false) ? "yes" : "no");
    printf("Directed edge 20->30 (expect yes): %s\n", edge_exists_graph(&g2, 20, 30, false) ? "yes" : "no");
    printf("Reverse 30->20 (expect no): %s\n", edge_exists_graph(&g2, 30, 20, false) ? "yes" : "no");
    printf("Edges (expect 2): %d\n\n", graph_edges_nb(&g2));

    // Test 5: Undirected weighted graph
    // Verifies weights are stored and retrieved correctly
    printf("=== Test 5 ===\n\n");

    Graph g3 = create_graph(true, false);
    int wa = add_vertex_graph(&g3, 100);
    int wb = add_vertex_graph(&g3, 200);
    int wc = add_vertex_graph(&g3, 300);

    add_edge_graph(&g3, 100, 200, 15, false); // by value
    add_edge_graph(&g3, 200, 300, 42, false);
    add_edge_graph(&g3, wa, wc, 7, true);     // by id

    printf("Weight 100->200 by value (expect 15): %d\n", get_edge_weight_graph(&g3, 100, 200, false));
    printf("Weight 200->100 undirected by value (expect 15): %d\n", get_edge_weight_graph(&g3, 200, 100, false));
    printf("Weight 200->300 by value (expect 42): %d\n", get_edge_weight_graph(&g3, 200, 300, false));
    printf("Weight wa->wc by id (expect 7): %d\n", get_edge_weight_graph(&g3, wa, wc, true));
    printf("Edges (expect 3): %d\n\n", graph_edges_nb(&g3));

    // Test 6: Directed weighted graph
    // Verifies all four graph type combinations work correctly
    printf("=== Test 6 ===\n\n");

    Graph g4 = create_graph(true, true);
    int da = add_vertex_graph(&g4, 5);
    int db = add_vertex_graph(&g4, 10);
    int dc = add_vertex_graph(&g4, 15);

    add_edge_graph(&g4, da, db, 100, true); // by id
    add_edge_graph(&g4, db, dc, 200, true);
    add_edge_graph(&g4, dc, da, 300, true);

    printf("Weight da->db by id (expect 100): %d\n", get_edge_weight_graph(&g4, da, db, true));
    printf("Weight db->dc by id (expect 200): %d\n", get_edge_weight_graph(&g4, db, dc, true));
    printf("Weight dc->da by id (expect 300): %d\n", get_edge_weight_graph(&g4, dc, da, true));
    printf("Reverse db->da (expect no): %s\n", edge_exists_graph(&g4, db, da, true) ? "yes" : "no");
    printf("Edges (expect 3): %d\n\n", graph_edges_nb(&g4));

    // Test 7: Duplicate vertex prevention
    // Verifies that adding an existing value is rejected
    printf("=== Test 7 ===\n\n");

    printf("Add duplicate value 1: ");
    add_vertex_graph(&g, 1);
    printf("\n");
    printf("Vertices unchanged (expect 4): %d\n\n", graph_length(&g));

    // Test 8: Get neighbors by id and by value
    // Verifies correct neighbor retrieval in both modes
    printf("=== Test 8 ===\n\n");

    Dynamic_Array nb_ids = get_neighbors_ids(&g, id_a);
    printf("Neighbors of id_a by id: ");
    print_dynamic_array(&nb_ids);
    printf("\n");

    Dynamic_Array nb_vals = get_neighbors_values(&g, 1);
    printf("Neighbors of value 1 by value: ");
    print_dynamic_array(&nb_vals);
    printf("\n\n");

    // Test 9: Remove edge by value and by id
    // Verifies edge removal works in both directions for undirected graph
    printf("=== Test 9 ===\n\n");

    printf("Before remove edge 1-2: Edges=%d\n", graph_edges_nb(&g));
    remove_edge_graph(&g, 1, 2, false); // by value
    printf("After remove edge 1-2 by value:\n");
    printf("Edge 1->2 (expect no): %s\n", edge_exists_graph(&g, 1, 2, false) ? "yes" : "no");
    printf("Edge 2->1 (expect no): %s\n", edge_exists_graph(&g, 2, 1, false) ? "yes" : "no");
    printf("Edges (expect 3): %d\n", graph_edges_nb(&g));

    remove_edge_graph(&g, id_c, id_d, true); // by id
    printf("After remove edge id_c-id_d by id:\n");
    printf("Edge 3->4 (expect no): %s\n", edge_exists_graph(&g, 3, 4, false) ? "yes" : "no");
    printf("Edges (expect 2): %d\n\n", graph_edges_nb(&g));

    // Test 10: Remove vertex by value and by id
    // Verifies vertex removal also cleans up all connected edges
    printf("=== Test 10 ===\n\n");

    // Add edges back first
    add_edge_graph(&g, 1, 2, 0, false);
    add_edge_graph(&g, 3, 4, 0, false);
    printf("Edges before remove vertex: %d\n", graph_edges_nb(&g));

    remove_vertex_graph(&g, 1, false); // by value
    printf("After remove vertex 1 by value:\n");
    printf("Vertex 1 exists (expect no): %s\n", vertex_value_exists_graph(&g, 1) ? "yes" : "no");
    printf("Edge 1->4 gone (expect no): %s\n", edge_exists_graph(&g, 1, 4, false) ? "yes" : "no");
    printf("Edge 4->1 gone (expect no): %s\n", edge_exists_graph(&g, 4, 1, false) ? "yes" : "no");
    printf("Vertices (expect 3): %d\n", graph_length(&g));

    remove_vertex_graph(&g, id_b, true); // by id
    printf("After remove vertex id_b by id:\n");
    printf("Vertex id_b exists (expect no): %s\n", vertex_id_exists_graph(&g, id_b) ? "yes" : "no");
    printf("Vertices (expect 2): %d\n\n", graph_length(&g));

    // Test 11: Non-existent vertex and edge error handling
    // Verifies correct error messages for invalid operations
    printf("=== Test 11 ===\n\n");

    printf("Add edge to non-existent value: ");
    add_edge_graph(&g2, 10, 99, 0, false);
    printf("Add edge to non-existent id: ");
    add_edge_graph(&g2, id1, 99, 0, true);
    printf("Remove non-existent edge by value: ");
    remove_edge_graph(&g2, 10, 30, false);
    printf("Remove non-existent vertex by value: ");
    remove_vertex_graph(&g2, 999, false);
    printf("Remove non-existent vertex by id: ");
    remove_vertex_graph(&g2, 99, true);
    printf("Get neighbors of non-existent id: ");
    Dynamic_Array empty_nb = get_neighbors_ids(&g2, 99);
    printf("\n");
    printf("Get weight on unweighted graph: ");
    get_edge_weight_graph(&g2, 10, 20, false);
    printf("\n\n");

    // Test 12: Print graph by ids and by values
    // Verifies print functions work correctly
    printf("=== Test 12 ===\n\n");

    printf("Print directed weighted graph by ids:\n");
    print_graph_ids(&g4);
    printf("\n");
    printf("Print directed weighted graph by values:\n");
    print_graph_values(&g4);
    printf("\n");
    printf("Print empty graph:\n");
    Graph g_empty = create_graph(false, false);
    print_graph_ids(&g_empty);
    printf("\n");

    // Test 13: Empty after operations and reuse
    // Verifies graph can be reused after empty_graph
    printf("=== Test 13 ===\n\n");

    empty_graph(&g4);
    printf("After empty_graph:\n");
    printf("Empty?: %s\n", is_empty_graph(&g4) ? "yes" : "no");
    printf("Vertices: %d\n", graph_length(&g4));
    printf("Edges: %d\n", graph_edges_nb(&g4));

    int ra = add_vertex_graph(&g4, 1);
    int rb = add_vertex_graph(&g4, 2);
    add_edge_graph(&g4, ra, rb, 50, true);
    printf("After re-add:\n");
    printf("Vertices: %d\n", graph_length(&g4));
    printf("Edges: %d\n", graph_edges_nb(&g4));
    printf("Edge ra->rb (expect yes): %s\n\n", edge_exists_graph(&g4, ra, rb, true) ? "yes" : "no");

    // Test 14: Stress test
    // Verifies correct behavior under heavy usage:
    // large-scale vertex/edge additions, lookups, and removals
    printf("=== Test 14 ===\n\n");

    Graph g5 = create_graph(true, true);

    for(int i = 0; i < 10000; i++){
        add_vertex_graph(&g5, i);
    }
    printf("Vertices after 10000 inserts: %d\n", graph_length(&g5));

    // Connect each vertex to the next (chain)
    for(int i = 0; i < 9999; i++){
        add_edge_graph(&g5, i, i+1, i*2, false); // by value
    }
    printf("Edges after 9999 inserts: %d\n", graph_edges_nb(&g5));

    // Verify all edges exist and weights are correct
    int errors = 0;
    for(int i = 0; i < 9999; i++){
        if(!edge_exists_graph(&g5, i, i+1, false)) errors++;
        if(get_edge_weight_graph(&g5, i, i+1, false) != i*2) errors++;
    }
    printf("Edge/weight errors: %d\n", errors);

    // Remove all vertices
    for(int i = 0; i < 10000; i++){
        remove_vertex_graph(&g5, i, false);
    }
    printf("Vertices after 10000 removals: %d\n", graph_length(&g5));
    printf("Edges after 10000 removals: %d\n", graph_edges_nb(&g5));
    printf("Empty?: %s\n", is_empty_graph(&g5) ? "yes" : "no");

    destroy_graph(&g);
    destroy_graph(&g2);
    destroy_graph(&g3);
    destroy_graph(&g4);
    destroy_graph(&g5);
    destroy_graph(&g_empty);
    destroy_dynamic_array(&nb_ids);
    destroy_dynamic_array(&nb_vals);
    destroy_dynamic_array(&empty_nb);

    return 0;
}

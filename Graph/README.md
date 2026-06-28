# Graph

## Description

A graph is a non-linear data structure that represents relationships between elements. It consists of vertices, which are nodes that hold values, and edges, which are connections between vertices.
Unlike linear structures such as arrays or linked lists, a graph has no fixed shape, any vertex can be connected to any other vertex, in any direction, with or without a weight.

---
## How it works

### Structure

The graph is implemented as adjacency list, using a combination of hash table and linked list. 
#### - Hash table
The hash table stores each vertex's ID as the key and a pointer to the vertex as the value. This allows fast O(1) average access to any vertex by its ID.

Hash_Table_Graph.c file contains hash table functions used in the graph implementation.
#### - Vertices and edges linked list
Each vertex stores an ID, a value, and a pointer to the head of its edge linked list. Each edge stores the destination vertex's ID, its weight (if the graph is weighted), and a pointer to the next edge in the list.

### Types

A graph can be weighted or unweighted, and directed or undirected. These two properties are independent, giving 4 possible combinations. This implementation lets the user choose the desired type at creation.

   - Weighted: each edge has a numerical value representing its weight, such as distance or cost.
   - Unweighted: edges have no weight, they simply indicate a connection between two vertices.
   - Directed: edges have a direction. A connected to B does not mean B is connected to A.
   - Undirected: edges have no direction. If A is connected to B, then B is also connected to A.

### Id vs value 

Every vertex has both an ID and a value. The ID is assigned automatically at insertion and is used internally as the hash table key. The value is the data the user actually stores.
Most functions let the user choose to work with IDs or values using the `is_id` parameter.

#### - ID-based operations

Since the ID is the hash table key, looking up a vertex by ID is O(1) on average. This makes ID-based insertion, deletion, and search fast.
#### - Value-based operations
The hash table is keyed by ID, not value. So searching by value requires walking the entire hash table until a match is found — O(n) where n is the number of vertices. Value-based operations are slower but more intuitive since the user doesn't need to track IDs manually.
#### - Recommendation
Save the ID returned by add_vertex_graph and use it for all subsequent operations on that vertex for best performance.

### Key features

 - Chosing type: The user can chose the type of created graph using `is_direct` and `is_weighted` tags.
 - Automatic ID assignment: IDs are assigned sequentially starting from 0 and returned to the user by add_vertex_graph, which is what enables the O(1) hash table lookup.
 - Automatic reverse edges: in undirected graphs, adding an edge between A and B automatically creates two edge nodes internally — one in A's list and one in B's list. The graph_edges_nb function accounts for this by dividing the internal count by 2 to return the logical number of edges.
 - Duplicate vertex prevention: add_vertex_graph checks if a vertex with the same value already exists before inserting, preventing duplicates.
 - Flexible lookup: every operation that involves finding a vertex supports both ID-based (O(1) average) and value-based (O(n)) lookup through the is_id parameter.

---
## Operations

| Function | Description | Time complexity |
|----------|-------------|-----------------|
| create_graph(bool is_weighted, bool is_direct) | Creates a new graph with desired type. | O(1) |
| add_vertex_graph(Graph *graph, int value) | Adds a new value to the graph, and assigns an ID to it. |O(v): where v is number of vertices (Adding is O(1) on average, but it checks the existence of the value, so it makes it O(v)). |
| add_edge_graph(Graph *graph, int from, int to, int weight, bool is_id) | Creates a new connection between two vertices, by IDs or values. | - Add by IDs: O(1) and O(v) in worst case. <br> - Add by value: O(v) |
| get_edge_weight_graph(Graph *graph, int from, int to, bool is_id) | Returns the weight of an edge. | - Get by IDs: O(1) and O(e) in worst case, where e is number of edges. <br> - Get by value: O(v+e) in worst case|
| get_neighbors_ids(Graph *graph, int id) | Returns a dynamic array of the IDs of all neighbors of a given vertex. | O(e) |
| get_neighbors_values(Graph *graph, int value) | Returns a dynamic array of the values of all neighbors of a given vertex. | O(v+e) in worst case |
| edge_exists_graph(Graph *graph, int from, int to, bool is_id) | Checks if a connection exists. | - Search by id: O(e) in worst case. <br> - Search by value: O(v+e) in worst case. |
| is_empty_graph(Graph *graph) | Checks if graph is empty. | O(1) |
| graph_length(Graph *graph) | Returns number of vertices in the graph. | O(1) |
| graph_edges_nb(Graph *graph) | Returns number of edges in the graph. | O(1) |
| vertex_id_exists_graph(Graph *graph, int id) | Checks if a vertex exists by ID. | - O(1) average <br> - O(v) in worst case |
| vertex_value_exists_graph(Graph *graph, int value) | Checks if a vertex exists by value. | O(v) in worst case |
| print_graph_ids(Graph *graph) | Prints the graph with IDs representation. | O(v+e) |
| print_graph_values(Graph *graph) | Prints the graph with values representation. | O(v+e) |
| remove_edge_graph(Graph *graph, int from, int to, bool is_id) | Deletes a connection between two IDs or values. | - remove by IDs: O(1) on average and O(e) in worst case. <br> - remove by value: O(v+e) in worst case |
| remove_vertex_graph(Graph *graph, int nb, bool is_id) | Removes a vertex from the graph. | O(v+e) |
| empty_graph(Graph *graph) | Empties the graph, and it can be reused. | O(v+e) |
| destroy_graph(Graph *graph) | Destroys the graph. Called when graph is no longer needed. | O(v+e) |

---
## Example

```c
#include "Graph/Graph.h"
#include <stdio.h>

int main(void) {

    // Undirected weighted graph
    Graph g1 = create_graph(true, false);

    int a = add_vertex_graph(&g1, 10);
    int b = add_vertex_graph(&g1, 20);
    int c = add_vertex_graph(&g1, 30);
    int d = add_vertex_graph(&g1, 40);

    add_edge_graph(&g1, a, b, 5, true);
    add_edge_graph(&g1, a, c, 3, true);
    add_edge_graph(&g1, b, d, 7, true);
    add_edge_graph(&g1, c, d, 2, true);

    printf("Undirected weighted graph:\n");
    print_graph_values(&g1);
    // 10 : 30(3) 20(5)
    // 40 : 30(2) 20(7)
    // 30 : 40(2) 10(3)
    // 20 : 40(7) 10(5)
    printf("\n");

    printf("Vertices: %d\n", graph_length(&g1)); // 4
    printf("Edges: %d\n", graph_edges_nb(&g1)); // 4
    printf("Weight 10-20: %d\n", get_edge_weight_graph(&g1, 10, 20, false)); // 5
    printf("Edge 10-40 exists? %s\n", edge_exists_graph(&g1, a, d, true) ? "yes" : "no"); // no

    Dynamic_Array neighbors = get_neighbors_values(&g1, 10);
    printf("\n");
    printf("Neighbors of 10: ");
    print_dynamic_array(&neighbors); // 30 20
    printf("\n");
    printf("\n");
    free(neighbors.data);

    remove_edge_graph(&g1, 10, 20, false);
    printf("After removing edge 10-20:\n");
    print_graph_values(&g1);
    printf("\n");

    remove_vertex_graph(&g1, 30, false);
    printf("After removing vertex 30:\n");
    print_graph_values(&g1);
    printf("\n");

    destroy_graph(&g1);

    // Directed unweighted graph
    Graph g2 = create_graph(false, true);

    int x = add_vertex_graph(&g2, 1);
    int y = add_vertex_graph(&g2, 2);
    int z = add_vertex_graph(&g2, 3);

    add_edge_graph(&g2, x, y, 0, true);
    add_edge_graph(&g2, y, z, 0, true);
    add_edge_graph(&g2, x, z, 0, true);

    printf("Directed unweighted graph:\n");
    print_graph_ids(&g2);
    // 0 : 2(0) 1(0)
    // 1 : 2(0)
    // 2 :
    printf("\n");
    printf("Edge 1->2 exists? %s\n", edge_exists_graph(&g2, y, z, true) ? "yes" : "no"); // yes
    printf("Edge 2->1 exists? %s\n", edge_exists_graph(&g2, z, y, true) ? "yes" : "no"); // no
    printf("Edges: %d\n", graph_edges_nb(&g2)); // 3

    destroy_graph(&g2);

    return 0;
}

```
---
## Visualisation

### Graph representation (IDs)

<img width="928" height="517" alt="image" src="https://github.com/user-attachments/assets/9f9bb0b2-f3cd-459e-b988-85488dcebd14" />

### Adjacency list and hash table representation

<img width="1423" height="840" alt="image" src="https://github.com/user-attachments/assets/1a030738-a234-410a-9a9a-c39725684d22" />



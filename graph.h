#ifndef _GRAPH_H
#define _GRAPH_H

typedef struct graph_edge *GraphEdge; 
struct graph_edge {
    int adjacency_index;
    int weight;
    GraphEdge next;
};

typedef struct graph_vertex *GraphVertex;
struct graph_vertex{
    int value;
    GraphEdge first_edge;
};

typedef struct graph_adjacency *AdjacencyGraph;
struct graph_adjacency{
    int vertex_count;
    int edge_count;
    GraphVertex vertexs;
};


extern AdjacencyGraph adjacency_graph_create( int vertex_count );
extern void adjacency_graph_dispose( AdjacencyGraph *graph );
extern GraphEdge adjacency_graph_add_edge( AdjacencyGraph graph, 
                                            GraphVertex vertex, 
                                            int adjacency_index, 
                                            int weight );
extern GraphEdge adjacency_graph_add_edge_ex( AdjacencyGraph graph, 
                                            int value_s, 
                                            int value_d, 
                                            int weight );
static int* calculate_adjacency_graph_indegree( AdjacencyGraph graph ); 
extern void adjacency_graph_topsort( AdjacencyGraph graph, int *sorted_indexs );
static int adjacency_graph_find_vertex_index(AdjacencyGraph graph, int value);

struct table_entry {
    int is_known;
    int distance;
    int path_index;
};
typedef struct table_entry *TableEntry;

#define NotAVertex (-1)

static void init_table( AdjacencyGraph graph, int start_index, TableEntry table );
extern TableEntry graph_create_table( int table_size );
extern void graph_dispose_table( TableEntry *table );

static int get_smallest_distance_unknown_vertex_index( TableEntry table, int table_size );
static void Dijkstra( AdjacencyGraph graph,  TableEntry table );
extern void graph_get_shortest_path_dijkstra( AdjacencyGraph graph, 
                                                int start_vertex_value, 
                                                TableEntry table );
extern void graph_print_shortest_path( AdjacencyGraph graph, 
                                        TableEntry table, 
                                        int start_index, 
                                        void (*print_value_func)(int value) );
extern void graph_print_shortest_path_ex( AdjacencyGraph graph, 
                                            TableEntry table, 
                                            int value, 
                                            void (*print_value_func)(int value) );
extern void graph_get_shortest_path_unweight( AdjacencyGraph graph,
                                                int start_vertex_value,
                                                TableEntry table );
                                                
#endif
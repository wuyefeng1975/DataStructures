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

#endif
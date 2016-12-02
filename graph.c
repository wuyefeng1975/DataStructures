#include <stddef.h>
#include <stdio.h>
#include "assert.h"
#include "mem.h"
#include "graph.h"
#include "list.h"

AdjacencyGraph adjacency_graph_create(int vertex_count ) {
    AdjacencyGraph graph;
    NEW( graph );
    graph->vertex_count = vertex_count;
    graph->edge_count = 0;
    graph->vertexs = CALLOC( vertex_count, sizeof(struct graph_vertex) );

    return graph;
}

static void clear_vertex_edge( GraphVertex vertex ){
    GraphEdge edge = vertex->first_edge;
    while( edge != NULL ) {
        GraphEdge temp = edge;
        edge = edge->next;
        FREE( temp );
    }
    vertex->first_edge = NULL;
} 


void adjacency_graph_dispose( AdjacencyGraph *graph ) {
    
    for( int i = 0; i < (*graph)->vertex_count; i++ ) {
        GraphVertex vertex = (*graph)->vertexs + i; 
        clear_vertex_edge( vertex );
    }
    
    FREE( (*graph)->vertexs );
    FREE( *graph );
    *graph = NULL;
}

GraphEdge adjacency_graph_add_edge( AdjacencyGraph graph, GraphVertex vertex, 
                                    int adjacency_index, int weight ){
    GraphEdge new_edge;
    NEW( new_edge );
    new_edge->adjacency_index = adjacency_index;
    new_edge->weight = weight;
    new_edge->next = NULL;

    GraphEdge *edge = &(vertex->first_edge);
    while( *edge != NULL ) {
        edge = &(*edge)->next;
    }
    *edge = new_edge;
    graph->edge_count++;
    
    return new_edge;
}
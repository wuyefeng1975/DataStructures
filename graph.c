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

static int adjacency_graph_find_vertex_index(AdjacencyGraph graph, int value) {
    for( int i = 0; i < graph->vertex_count; i++ ) {
        GraphVertex vertex = graph->vertexs + i;
        if( vertex->value == value )
            return i;
    }
    return -1;
}

GraphEdge adjacency_graph_add_edge_ex( AdjacencyGraph graph, 
                                            int value_s, 
                                            int value_d, 
                                            int weight ){
    int index_s = adjacency_graph_find_vertex_index( graph, value_s );
    int index_d = adjacency_graph_find_vertex_index( graph, value_d );
    if( index_s < 0 || index_d < 0 )
        return NULL;

    return adjacency_graph_add_edge( graph, graph->vertexs + index_s, 
                                    index_d, weight );
}

int* calculate_adjacency_graph_indegree( AdjacencyGraph graph ) {
    int *indegree = CALLOC( graph->vertex_count, sizeof( int ) );
    for( int i = 0; i < graph->vertex_count; i++ ) 
        *(indegree + i) = 0;
        
    GraphVertex vertexs = graph->vertexs;
    for( int i = 0; i < graph->vertex_count; i++ ) {
        GraphVertex vertex = vertexs + i;
        for( GraphEdge edge = vertex->first_edge; edge != NULL; edge = edge->next ) {
            int index = edge->adjacency_index;
            *(indegree + index) += 1;
        }
    }

    return indegree; 
}

void adjacency_graph_topsort( AdjacencyGraph graph, int *sorted_indexs ) {
    int count = 0;
    int *indegrees = calculate_adjacency_graph_indegree( graph );
    
    List queue = List_create( sizeof( int ), NULL, NULL );
    NodePosition pos_last = queue->header;
    for( int i = 0; i < graph->vertex_count; i++ ) {
        if( *(indegrees + i) == 0 )
            pos_last = List_insert( queue, pos_last, &i );
    }

    NodePosition pos;
    while( ( pos = queue->header->next ) != NULL ) {
        int adj_index = *(int*)queue->header->next->element;
        List_pop_front( queue );
        
        *(sorted_indexs + count) = adj_index; 
        count++;

        GraphVertex vertex = graph->vertexs + adj_index;
        GraphEdge edge = vertex->first_edge;
        for( ; edge != NULL; edge = edge->next ) {
            int index = edge->adjacency_index;   
            if( --(*(indegrees + index)) == 0 ) {
                List_push_back( queue, &index );
            }
        }
    }
    if( count != graph->vertex_count ) {
        printf( "Graph has a cycle\n" );
    }
    
    FREE( indegrees );
    List_dispose( &queue );
}
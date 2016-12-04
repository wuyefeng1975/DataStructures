#include <stddef.h>
#include <stdio.h>
#include <limits.h>
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

int adjacency_graph_find_vertex_index(AdjacencyGraph graph, int value) {
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

void init_table( AdjacencyGraph graph, int start_index, TableEntry table ) {
    for( int i = 0; i < graph->vertex_count; i++ ) {
        (table + i)->is_known = 0;
        (table + i)->distance = INT_MAX;
        (table + i)->path_index = NotAVertex;
    }
    (table + start_index)->distance = 0;
}

//this function is not efficiency, it should be refactory
int get_smallest_distance_unknown_vertex_index( TableEntry table, int table_size ) {
    int min = INT_MAX;
    int index = NotAVertex;
    for( int i = 0; i < table_size; i++ ) {
        TableEntry entry =  table + i;
        if( entry->distance < min && entry->is_known == 0 ) {
            index = i;
            min = entry->distance;
        }
    }
    return index;
}

void Dijkstra( AdjacencyGraph graph,  TableEntry table ) {
    for(;;) {
        int table_size = graph->vertex_count;
        //inefficient, shold be modified
        int source_index = get_smallest_distance_unknown_vertex_index( table, table_size );
        if( source_index == NotAVertex )
            break;
        
        TableEntry source_entry = table + source_index;
        source_entry->is_known = 1;
        GraphEdge edge = (graph->vertexs + source_index)->first_edge;
        while( edge != NULL ) {
            int destination_index = edge->adjacency_index;
            TableEntry destination_entry = table + destination_index;

            if( destination_entry->is_known == 0 ) {
                 if( source_entry->distance + edge->weight < destination_entry->distance ) {
                     destination_entry->distance = source_entry->distance + edge->weight;
                     destination_entry->path_index = source_index;
                 }
            }
            edge = edge->next;
        }
    }
}

void graph_print_shortest_path( AdjacencyGraph graph, TableEntry table, int start_index, 
                                void (*print_value_func)(int value) ) {
    TableEntry entry = table + start_index;
    if( entry->path_index != NotAVertex ) {
        graph_print_shortest_path( graph, table, entry->path_index, print_value_func );
        printf( " to " );
    }
    (*print_value_func)( (graph->vertexs + start_index)->value );
}

void graph_print_shortest_path_ex( AdjacencyGraph graph, 
                                    TableEntry table, 
                                    int value, 
                                    void (*print_value_func)(int value) ) {
    int index = adjacency_graph_find_vertex_index( graph, value );
    graph_print_shortest_path( graph, table, index, print_value_func );
}

void graph_get_shortest_path_dijkstra( AdjacencyGraph graph, int start_vertex_value, TableEntry table ) {
    int index = adjacency_graph_find_vertex_index( graph, start_vertex_value );
    init_table( graph, index, table );
    Dijkstra( graph, table );
}

TableEntry graph_create_table( int table_size ) {
    return CALLOC( table_size, sizeof( struct table_entry ) );
}

void graph_dispose_table( TableEntry *table ) {
    FREE( *table );
    *table = NULL;
}

void graph_get_shortest_path_unweight( AdjacencyGraph graph,
                                        int start_vertex_value,
                                        TableEntry table ){
    int source_index = adjacency_graph_find_vertex_index( graph, start_vertex_value );
    init_table( graph, source_index, table );
    GraphVertex source_vertex = graph->vertexs + source_index;

    List queue = List_create( sizeof( int ), NULL, NULL );
    List_push_back( queue, &source_index );

    while( queue->header->next != NULL ) {
        source_index = *(int*)queue->header->next->element;
        List_pop_front( queue );

        TableEntry source_entry = table + source_index;
        source_entry->is_known = 1;
        
        GraphVertex source_vertex = graph->vertexs + source_index;
        GraphEdge edge = source_vertex->first_edge;
        while( edge != NULL ) {
            int dest_index = edge->adjacency_index;
            GraphVertex dest_vertex = graph->vertexs + dest_index;
            TableEntry dest_entry = table + dest_index;
            if( dest_entry->distance == INT_MAX  ) {
                dest_entry->distance = source_entry->distance + 1;
                dest_entry->path_index = source_index;

                List_push_back( queue, &dest_index );
            }
            edge = edge->next;
        }
    }

    List_dispose( &queue );
}
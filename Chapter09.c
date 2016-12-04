#include <stddef.h>
#include <stdio.h>
#include "graph.h"
#include "assert.h"
#include "mem.h"
#include "graph.h"

void test_adjacency_graph();
AdjacencyGraph init_adjacency_graph_1();
void printf_adjacency_graph( AdjacencyGraph graph );

void Exercise_09_03();

AdjacencyGraph init_adjacency_graph_2();
void printf_vertex_value( int value );
void Exercise_09_05();

int main()
{
    //test_adjacency_graph();
    
    //Exercise_09_03();
    Exercise_09_05();

    return 0;
}

void Exercise_09_05() {
    AdjacencyGraph graph = init_adjacency_graph_2();
    TableEntry table = graph_create_table( graph->vertex_count );
    
    graph_get_shortest_path_unweight( graph, 'A', table );
    for( int i = 0; i < graph->vertex_count; i++ ) {
        graph_print_shortest_path( graph, table, i, &printf_vertex_value );
        printf( "\n" );
    }
    
    graph_get_shortest_path_dijkstra( graph, 'A', table );
    for( int i = 0; i < graph->vertex_count; i++ ) {
        graph_print_shortest_path( graph, table, i, &printf_vertex_value );
        printf( "\n" );
    }

    graph_dispose_table( & table );
    adjacency_graph_dispose( &graph );
}

void printf_vertex_value( int value ) {
    printf( "%c", value );
}

AdjacencyGraph init_adjacency_graph_2(){
    int vertex_count = 7;
    AdjacencyGraph graph = adjacency_graph_create( vertex_count );
    for( int i = 0; i < vertex_count; i++ ) {
        GraphVertex v = graph->vertexs + i;
        v->value = 'A' + i;
        v->first_edge = NULL;
    }
    
    adjacency_graph_add_edge_ex( graph, 'A', 'B', 5 );
    adjacency_graph_add_edge_ex( graph, 'A', 'C', 3 );
    adjacency_graph_add_edge_ex( graph, 'B', 'C', 2 );
    adjacency_graph_add_edge_ex( graph, 'B', 'E', 3 );
    adjacency_graph_add_edge_ex( graph, 'B', 'G', 1 );
    adjacency_graph_add_edge_ex( graph, 'C', 'D', 7 );
    adjacency_graph_add_edge_ex( graph, 'C', 'E', 7 );
    adjacency_graph_add_edge_ex( graph, 'D', 'A', 2 );
    adjacency_graph_add_edge_ex( graph, 'D', 'F', 6 );
    adjacency_graph_add_edge_ex( graph, 'E', 'D', 2 );
    adjacency_graph_add_edge_ex( graph, 'E', 'F', 1 );
    adjacency_graph_add_edge_ex( graph, 'G', 'E', 1 );

    return graph;
}

void Exercise_09_03() {
    AdjacencyGraph graph = init_adjacency_graph_1();
    printf_adjacency_graph( graph );

    int *sorted_indexs = CALLOC( graph->vertex_count, sizeof( int ) );
    adjacency_graph_topsort( graph, sorted_indexs );
    for( int i = 0; i < graph->vertex_count; i++ ) {
        int index = *(sorted_indexs + i);
        printf ( "%c\t", (graph->vertexs + index)->value );
    }
    printf( "\n" );

    FREE( sorted_indexs );
    adjacency_graph_dispose( &graph );
}

AdjacencyGraph init_adjacency_graph_1(){
    int vertex_count = 11;
    AdjacencyGraph graph = adjacency_graph_create( vertex_count );
    for( int i = 0; i < vertex_count; i++ ) {
        GraphVertex v = graph->vertexs + i;
        if( i < vertex_count - 2 ) {
            v->value = 'A' + i;
        } else if ( i == vertex_count - 1 ) {
            v->value = 'S';
        } else {
            v->value = 'T';
        }
        v->first_edge = NULL;
    }
    
    adjacency_graph_add_edge_ex( graph, 'A', 'B', 2 );
    adjacency_graph_add_edge_ex( graph, 'A', 'E', 2 );
    adjacency_graph_add_edge_ex( graph, 'B', 'C', 2 );
    adjacency_graph_add_edge_ex( graph, 'C', 'T', 4 );
    adjacency_graph_add_edge_ex( graph, 'D', 'A', 3 );
    adjacency_graph_add_edge_ex( graph, 'D', 'E', 3 );
    adjacency_graph_add_edge_ex( graph, 'F', 'C', 1 );
    adjacency_graph_add_edge_ex( graph, 'E', 'C', 2 );
    adjacency_graph_add_edge_ex( graph, 'E', 'F', 3 );
    adjacency_graph_add_edge_ex( graph, 'E', 'I', 3 );
    adjacency_graph_add_edge_ex( graph, 'F', 'C', 1 );
    adjacency_graph_add_edge_ex( graph, 'F', 'T', 3 );

    adjacency_graph_add_edge_ex( graph, 'G', 'D', 2 );
    adjacency_graph_add_edge_ex( graph, 'G', 'E', 1 );
    adjacency_graph_add_edge_ex( graph, 'G', 'H', 6 );

    adjacency_graph_add_edge_ex( graph, 'H', 'E', 2 );
    adjacency_graph_add_edge_ex( graph, 'H', 'I', 6 );
    adjacency_graph_add_edge_ex( graph, 'I', 'F', 1 );
    adjacency_graph_add_edge_ex( graph, 'I', 'T', 4 );
    adjacency_graph_add_edge_ex( graph, 'S', 'A', 1 );
    adjacency_graph_add_edge_ex( graph, 'S', 'D', 4 );
    adjacency_graph_add_edge_ex( graph, 'S', 'G', 6 );

    return graph;
}

void printf_adjacency_graph( AdjacencyGraph graph ) {
    printf( "Graph vertex count is: %d\n", graph->vertex_count );
    printf( "Graph edge count is: %d\n", graph->edge_count );

    GraphVertex vertexs = graph->vertexs;
    for( int i = 0; i < graph->vertex_count; i++ ) {
        GraphVertex vertex = vertexs + i;
        printf( "Vertex: %c\n", vertex->value );

        for( GraphEdge edge = vertex->first_edge; edge != NULL; edge = edge->next ) {
            GraphVertex vertex_2 = vertexs + edge->adjacency_index;
            printf( "  edge(%c, %c) weight is: %d\n",
                    vertex->value, vertex_2->value, edge->weight );
        }
    }
}

void test_adjacency_graph() {
    AdjacencyGraph graph = adjacency_graph_create( 10 );
    GraphVertex v0 = graph->vertexs;
    v0->value = 99;
    v0->first_edge = NULL;

    GraphVertex v1 = v0 + 1;
    v1->value = 88;
    v1->first_edge = NULL;

    GraphVertex v2 = v0 + 2;
    v2->value = 7;
    v2->first_edge = NULL;

    adjacency_graph_add_edge( graph, v0, 1, 2 );
    adjacency_graph_add_edge( graph, v0, 2, 1 );
    
    printf_adjacency_graph( graph );

    adjacency_graph_dispose( &graph );
}
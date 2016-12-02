#include <stddef.h>
#include <stdio.h>
#include "graph.h"
#include "assert.h"
#include "mem.h"
#include "graph.h"

void test_adjacency_graph();

int main()
{
    test_adjacency_graph();
    return 0;
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
    
    GraphVertex vertexs = graph->vertexs;
    for( int i = 0; i < graph->vertex_count; i++ ) {
        GraphVertex vertex = vertexs + i;
        printf( "Vertex: %d\n", vertex->value );

        for( GraphEdge edge = vertex->first_edge; edge != NULL; edge = edge->next ) {
            GraphVertex vertex_2 = vertexs + edge->adjacency_index;
            printf( "  edge(%d, %d) weight is: %d\n",
                    vertex->value, vertex_2->value, edge->weight );
        }
    }
    printf( "Graph edge count is: %d\n", graph->edge_count );

    adjacency_graph_dispose( &graph );
}
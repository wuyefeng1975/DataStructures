#include <stddef.h>
#include <stdio.h>
#include "graph.h"

void Exercise_03();
void printf_adjacency_graph( AdjacencyGraph graph );
AdjacencyGraph init_adjacency_graph_1();
void DFS( AdjacencyGraph graph, GraphVertex vertex, int *visited, int *ordered, int *orderedNum );

int main()
{
    Exercise_03();
    return 0;
}

void Exercise_03() 
{
    AdjacencyGraph graph = init_adjacency_graph_1();
    int visited[7] = {0, 0, 0, 0, 0, 0, 0};
    int ordered[7] = {1, 2, 3, 4, 5, 6, 7};
    int orderedNum = 6;
    for( int i = 0; i < graph->vertex_count; i++ )
    {
        GraphVertex vertex = graph->vertexs + i;
        int index = vertex->value - 'A';
        if( visited[index] == 0 )
            DFS( graph, vertex, visited, ordered, &orderedNum );
    }
    for( int i = 0; i < 7; i++ )
        printf( "%c\n", ordered[i] );
    
    adjacency_graph_dispose( &graph );
}

void DFS( AdjacencyGraph graph, GraphVertex vertex, int *visited, int *ordered, int *orderedNum )
{
    int index = vertex->value - 'A';
    visited[index] = 1;
    for( GraphEdge edge = vertex->first_edge; edge != NULL; edge = edge->next ) 
    {
        GraphVertex next_vertex = graph->vertexs + edge->adjacency_index;
        index = next_vertex->value - 'A';
        if( visited[index] == 0 ) 
        {
            DFS( graph, next_vertex, visited, ordered, orderedNum );
        }
    }
    ordered[(*orderedNum)--] = vertex->value;
}

AdjacencyGraph init_adjacency_graph_1()
{
    int vertex_count = 7;
    AdjacencyGraph graph = adjacency_graph_create( vertex_count );
    for( int i = 0; i < vertex_count; i++ ) 
    {
        GraphVertex v = graph->vertexs + i;
        v->value = 'A' + i;
        v->first_edge = NULL;
    }
    
    adjacency_graph_add_edge_ex( graph, 'A', 'B', 1 );
    adjacency_graph_add_edge_ex( graph, 'A', 'C', 1 );
    adjacency_graph_add_edge_ex( graph, 'B', 'E', 1 );
    adjacency_graph_add_edge_ex( graph, 'B', 'G', 1 );
    adjacency_graph_add_edge_ex( graph, 'G', 'E', 1 );
    adjacency_graph_add_edge_ex( graph, 'G', 'F', 1 );
    adjacency_graph_add_edge_ex( graph, 'C', 'F', 1 );
    adjacency_graph_add_edge_ex( graph, 'D', 'A', 1 );
    adjacency_graph_add_edge_ex( graph, 'D', 'B', 1 );
    adjacency_graph_add_edge_ex( graph, 'D', 'C', 1 );
    adjacency_graph_add_edge_ex( graph, 'D', 'G', 1 );
    adjacency_graph_add_edge_ex( graph, 'D', 'F', 1 );
    
    return graph;
}

void printf_adjacency_graph( AdjacencyGraph graph ) 
{
    printf( "Graph vertex count is: %d\n", graph->vertex_count );
    printf( "Graph edge count is: %d\n", graph->edge_count );

    GraphVertex vertexs = graph->vertexs;
    for( int i = 0; i < graph->vertex_count; i++ ) 
    {
        GraphVertex vertex = vertexs + i;
        printf( "Vertex: %c\n", vertex->value );

        for( GraphEdge edge = vertex->first_edge; edge != NULL; edge = edge->next ) 
        {
            GraphVertex vertex_2 = vertexs + edge->adjacency_index;
            printf( "  edge(%c, %c) weight is: %d\n",
                    vertex->value, vertex_2->value, edge->weight );
        }
    }
}
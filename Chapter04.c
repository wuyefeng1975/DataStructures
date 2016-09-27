#include <stdio.h>
#include <stdbool.h>
#include "List.h"
#include "binary_tree.h"


int int_compare( const void* elem1, const void* elem2 ) {
    int int1 = *(int*)elem1;
    int int2 = *(int*)elem2;
    if( int1 < int2 )
        return -1;
    else if( int1 == int2 )
        return 0;
    
    return 1;
}

void int_element_print( void* element ) {
    printf( "%d", *(int*)element );
}

void Exerice_04_09()
{
    printf( "<E-04-09>\n" );

    BinaryTree tree = BinaryTree_create( sizeof( int ), NULL, &int_compare );
    tree->print_element_func = &int_element_print;
    
    int i = 3;
    int j = 2;
    int k = 5;
    int l = 1;
    int m = 4;
    int n = 6;
    int o = 7;

    SearchTree_insert( tree, &i );
    SearchTree_insert( tree, &j );
    SearchTree_insert( tree, &k );
    SearchTree_insert( tree, &l );
    SearchTree_insert( tree, &m );
    SearchTree_insert( tree, &n );
    SearchTree_insert( tree, &o );
    BinaryTree_print( tree );

    SearchTree_delete( tree, &i );
    BinaryTree_print( tree );

    BinaryTree_dispose( &tree );
    
    printf( "</E-04-09>\n" );
}


int main()
{
    Exerice_04_09();

    return 0;
}

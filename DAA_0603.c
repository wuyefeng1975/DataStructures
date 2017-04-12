#include <stdio.h>
#include <stddef.h>
#include "assert.h"
#include "mem.h"
#include "utility_integer.h"
#include "binary_tree.h"

void Execrise_04();
void int_element_print( void* element ) ;
int int_compare( const void* elem1, const void* elem2 ) ;

int main()
{
    Execrise_04();
}

void Execrise_04()
{
    BinaryTree tree = BinaryTree_create( sizeof( int ), NULL, &int_compare );
    tree->print_element_func = &int_element_print;
    
    /*
    int i = 1;
    int j = 2;
    int k = 3;
    int l = 4;
    int m = 5;
    int n = 6;
    */
    /*
    int i = 6;
    int j = 5;
    int k = 4;
    int l = 3;
    int m = 2;
    int n = 1;
    */
    int i = 3;
    int j = 6;
    int k = 5;
    int l = 1;
    int m = 2;
    int n = 4;

    AvlTree_insert( tree, &i );
    AvlTree_insert( tree, &j );
    AvlTree_insert( tree, &k );
    AvlTree_insert( tree, &l );
    AvlTree_insert( tree, &m );
    AvlTree_insert( tree, &n );
    
    BinaryTree_print( tree );
    BinaryTree_dispose( &tree );
}

int int_compare( const void* elem1, const void* elem2 ) 
{
    int int1 = *(int*)elem1;
    int int2 = *(int*)elem2;
    if( int1 < int2 )
        return -1;
    else if( int1 == int2 )
        return 0;
    
    return 1;
}

void int_element_print( void* element ) 
{
    printf( "%d", *(int*)element );
}

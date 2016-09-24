#include <stdio.h>
#include <stddef.h>
#include "list.h"
#include "mem.h"
#include "except.h"
#include "assert.h"
#include "binary_tree.h"
#include <math.h>

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

void test_list() {
    List list = List_create( sizeof(int), NULL, &int_compare );
    int k = 2;
    NodePosition pos = list->header;
    for( int i = 0; i < 10; i++ ) {
        pos = List_insert( list, pos, &i );
    }
    List_push_back( list, &k );
    List_push_back( list, &k );
    pos = list->header;
    while( ( pos = pos->next ) != NULL ) {
        printf( "%d\n", *(int*)pos->element );
    }
    
    List_dispose( &list );
    if( list == NULL ) {
        printf ( "NULL\n");
    }
}

void test_stack() {
    int i = 10;
    List stack = List_create( sizeof(int), NULL, &int_compare );
    List_push_front( stack, &i );
    i = 9;
    List_push_front( stack, &i );
    printf( "first is: %d\n", *(int*)List_first( stack ) );
    List_pop_front( stack );
    List_dispose( &stack );
}

void Test_TRY_CATCH() {
    struct Except_T zeroExcept = { "Can not be zero" };
    TRY
    int i = 0;
    int j = 0;
    if( j == 0 )
        RAISE( zeroExcept );
    printf( "Hello World\n" );
    EXCEPT(zeroExcept)
    printf( "Shit\n");
    Except_flag = Except_entered;
    END_TRY
    printf( "Out Try catch\n");
    
}

void test_binary_tree() {
    BinaryTree tree = BinaryTree_create( sizeof( int ), NULL, &int_compare );
    tree->print_element_func = &int_element_print;
    
    int i = 3;
    int j = 1;
    int k = 4;
    int l = 6;
    int m = 9;
    int n = 2;
    int o = 5;
    int p = 7;

    SearchTree_insert( tree, &i );
    SearchTree_insert( tree, &j );
    SearchTree_insert( tree, &k );
    SearchTree_insert( tree, &l );
    SearchTree_insert( tree, &m );
    SearchTree_insert( tree, &n );
    SearchTree_insert( tree, &o );
    SearchTree_insert( tree, &p );
    
    printf( "tree height is:%d\n", BinaryTree_height( tree->root ) );
    printf( "tree node count is:%d\n", BinaryTree_node_count( tree->root ) );
    BinaryTree_print( tree );
    
    int tt = 3;
    BinaryTreeNode node = SearchTree_find_min( tree->root );
    node = SearchTree_find( tree, &tt );
    if( node != NULL )
        (*tree->print_element_func)(node->element);
    else
        printf( "Not Found!" );
    printf("\n");
    printf("\n");
    
    BinaryTree_print( tree );
    tt = 4;
    SearchTree_delete( tree, &tt );
    BinaryTree_print( tree );

    /*
    tt = 5;
    SearchTree_delete( tree, &tt );
    BinaryTree_print( tree );
    tt = 6;
    SearchTree_delete( tree, &tt );
    BinaryTree_print( tree );
    tt = 7;
    SearchTree_delete( tree, &tt );
    BinaryTree_print( tree );
    */
    BinaryTree_dispose( &tree );
}

void test_avl_tree() {
    BinaryTree tree = BinaryTree_create( sizeof( int ), NULL, &int_compare );
    tree->print_element_func = &int_element_print;
    
    int i = 3;
    int j = 2;
    int k = 5;
    int l = 1;
    int m = 4;
    int n = 6;
    int o = 7;
    //int p = 7;
    //int q = 8;

    AvlTree_insert( tree, &i );
    AvlTree_insert( tree, &j );
    AvlTree_insert( tree, &k );
    AvlTree_insert( tree, &l );
    AvlTree_insert( tree, &m );
    AvlTree_insert( tree, &n );
    AvlTree_insert( tree, &o );
    //AvlTree_insert( tree, &p );
    //AvlTree_insert( tree, &q );
    
    BinaryTree_print( tree );
    
    AvlTree_delete( tree, &l );
    BinaryTree_print( tree );

    //AvlTree_delete( tree, &k );
    //BinaryTree_print( tree );
    
    BinaryTree_dispose( &tree );
/*
    tree = BinaryTree_create( sizeof( int ), NULL, &int_compare );
    tree->print_element_func = &int_element_print;

    int result = pow( 2, 5 ) - 1;
    for( int i = 1; i <= result; i++ ) {
        AvlTree_insert( tree, &i );
    }
    BinaryTree_print( tree );
    BinaryTree_dispose( &tree );
    */
}

int main() {
    //Test_TRY_CATCH();
    //test_list();
    //test_stack();
    //test_binary_tree();
    test_avl_tree();
}
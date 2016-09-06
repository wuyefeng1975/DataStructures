#include <stdio.h>
#include <stddef.h>
#include "list.h"
#include "mem.h"
#include "except.h"
#include "assert.h"
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

void test_list() {
    List list = List_create( sizeof(int) );
    int i = 0;
    int j = 1;
    int k = 2;
    int l = 3;
    int m = 4;
    NodePosition pos = list->header;
    for( int i = 0; i < 10; i++ ) {
        pos = List_insert( list, pos, &i, NULL );
    }
    List_push_back( list, &k, NULL );
    List_push_back( list, &k, NULL );
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
    List stack = List_create( sizeof(int) );
    List_push_front( stack, &i, NULL );    
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
    
    int j = 11;
    int m = 9;
    int n = 8;
    int k = 20;
    int i = 1;
    SearchTree tree = NULL;
    
    tree = SearchTree_insert( tree, &j, &int_compare );
    tree = SearchTree_insert( tree, &m, &int_compare );
    tree = SearchTree_insert( tree, &n, &int_compare );
    tree = SearchTree_insert( tree, &k, &int_compare );
    tree = SearchTree_insert( tree, &i, &int_compare );
    
    BinaryTree_print( tree );
    BinaryTree_make_empty( &tree );
}

int main() {
    //Test_TRY_CATCH();
    //test_list();
    //test_stack();
    test_binary_tree();
}
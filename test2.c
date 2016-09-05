#include <stdio.h>
#include <stddef.h>
#include "list.h"
#include "mem.h"
#include "except.h"
#include "assert.h"
//#include "binary_tree.h"

int int_compair( const void* elem1, const void* elem2 ) {
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
        pos = List_insert( list, list->header, &i, NULL );
    }
    
    for( pos = list->header->next; pos != NULL; pos = pos->next )
        printf( "%d\n", *(int*)pos->element );

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

int compare_int( void const *a, void const *b ) {
    if( *(int*)a > *(int*)b ) {
        return 1;
    } else if( *(int*)a < *(int*)b ) {
        return -1;
    } else {
        return 0;
    }
}

void test_binary_tree() {
    /*
    int j = 11;
    int m = 9;
    int n = 8;
    int k = 20;
    int i = 1;
    SearchTree tree = NULL;
    
    tree = SearchTree_insert( tree, &j, &compare_int );
    tree = SearchTree_insert( tree, &m, &compare_int );
    tree = SearchTree_insert( tree, &n, &compare_int );
    tree = SearchTree_insert( tree, &k, &compare_int );
    tree = SearchTree_insert( tree, &i, &compare_int );
    printf( "Node Count is:%d\n", SearchTree_node_count(tree) );
    SearchTree_print( tree, 0 );
    
    SearchTree_makeEmpty( &tree );
    */
}

int main() {
    //Test_TRY_CATCH();
    //test_list();
    test_stack();
    //test_binary_tree();
}
#include <stdio.h>
#include "stack.h"
#include "list.h"
#include "mem.h"


void test_list() {
    int i = 1;
    int j = 2;
    int k = 3;
    int l = 4;
    
    List list = List_create();

    
    List_insert( list, list, &i );
    List_insert( list, list, &j );
    List_insert( list, list, &k );
    Position pos = List_find( list, &i );
    List_insert( list, pos, &l );
    List_delete( list, &j );
    pos = list->next;
    while( pos ) {
        printf( "%d\t", *(int*)pos->element) ;
        pos = pos->next;
    }
    List_makeEmpty( list );

    if( List_isEmpty( list ) ) 
        printf( "Empty\n" );
    else
        printf( "Not empty\n" );
    
    if( List_isLast( list ) ) 
        printf( "Last\n" );
    else
        printf( "Not last\n" );

    List_dispose( &list );

}

void test_stack() {
    int i = 1;
    int j = 2;
    int k = 3;
    int l = 4;
    int m = 5;
    int n = 6;
    Stack_T stack = Stack_create();
    Stack_push( stack, &n );
    Stack_push( stack, &l );
    Stack_pop( stack );
    Stack_dispose( &stack );
}

int main() {
    printf( "Hello World\n" );

    //test_stack();
    test_list();
}
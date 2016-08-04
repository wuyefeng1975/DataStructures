#include <stdio.h>
#include "stack.h"
#include "list.h"
#include "mem.h"

#include "except.h"
#include "assert.h"
#include <setjmp.h>


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

int main() {
    printf( "Hello World\n" );
    Test_TRY_CATCH();
    
    //test_stack();
    test_list();
}
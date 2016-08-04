#include <stddef.h>
#include "assert.h"
#include "mem.h"
#include "stack.h"

#define T Stack_T


T Stack_create() {
    T stack;
    NEW( stack );
    stack->next = NULL;

    return stack;
}

void Stack_dispose( T *stack ) {
    assert( *stack );
    Stack_makeEmpty( *stack );
    FREE( *stack );
    stack = NULL;
}

void Stack_push( T stack, void *element ) {
    T p;
    NEW( p );
    p->element = element;
    p->next = stack->next;
    stack->next = p;
}

void* Stack_pop( T stack ) {
    if( stack == NULL ) 
        return NULL;

    void* element;
    T top = stack->next;
    if( top != NULL ) {
        element = top->element;
        stack->next = top->next;
        FREE( top );
    }
    
    return element;
}

void Stack_makeEmpty( T stack ) {
    while( stack->next ) {
        Stack_pop( stack );
    }
}

int Stack_isEmpty( T stack ) {
    return stack->next == NULL;
}

void* Stack_top( T stack ) {
    if( stack == NULL || stack->next == NULL )
        return NULL;

    return stack->next->element;
}
#include <stddef.h>
#include "assert.h"
#include "mem.h"
#include "list.h"

List List_create( size_t data_size, 
                    void (*assign)(void*, const void*),
                    int (*compare)(const void*, const void*) ) {
    List list;
    NEW( list );

    NodePosition header;
    NEW( header );
    header->next = NULL;
    list->header = header;
    list->size = 0;
    list->data_size = data_size;
    list->assign_func = assign;
    list->compare_func = compare;

    return list;
}

void List_dispose( List *list ) {
    assert( *list );
    
    List_make_empty( *list );
    FREE( (*list)->header );
    FREE( *list );
    *list = NULL;
}

void List_make_empty( List list ) {
    assert( list );
    
    while( list->header->next != NULL ) {
        List_delete( list, list->header->next );
    }
}

NodePosition List_insert( List list, NodePosition pos, void *element ){
    assert( list );
    assert( pos );
    
    NodePosition new_position;
    NEW( new_position );
    
    void* ptr = ALLOC( list->data_size );
    if( list->assign_func != NULL )
        (*list->assign_func)( ptr, element );
    else
        COPY( ptr, element, list->data_size );
    new_position->element = ptr;
    new_position->next = pos->next;
    pos->next = new_position;
    (list->size)++;
    return new_position;
}

NodePosition List_find_previous( List list, NodePosition pos ) {
    assert( list );

    NodePosition previous = list->header;
    while( previous != NULL && previous->next != pos )
        previous = previous->next;
    
    return previous;
}

NodePosition List_delete( List list, NodePosition pos ) {
    assert( list );
    assert( pos );

    NodePosition previous = List_find_previous( list, pos );
    if( previous == NULL )
        return NULL;
    previous->next = pos->next;
    FREE( pos->element );
    FREE( pos );
    (list->size)--;

    return previous->next;
}

NodePosition List_find( List list, void* element ) {
    assert( list );
    assert( list->compare_func );

    NodePosition pos = list->header->next;
    while( pos != NULL ) {
        if( (*list->compare_func)( pos->element, element ) == 0 )
            break;
        pos = pos->next;
    }

    return pos;
}

void List_push_front( List list, void* element ) {
    assert( list );

    List_insert( list, list->header, element );
}

void List_pop_front( List list ) {
    assert( list );
    
    List_delete( list, list->header->next );
}

void List_push_back( List list, void* element ) {
    assert( list );
    
    NodePosition pos = list->header;
    while( pos->next != NULL ) {
        pos = pos->next;
    }    
    List_insert( list, pos, element );
}

void List_pop_back( List list ) {
    assert( list );
    
    NodePosition pos = list->header;
    while( pos->next != NULL ) {
        pos = pos->next;
    }
    List_delete( list, pos );
}

void* List_first( List list ) {
    assert( list );

    if( list->header->next == NULL )
        return NULL;

    return list->header->next->element;
}

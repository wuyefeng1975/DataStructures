#include <stddef.h>
#include "assert.h"
#include "mem.h"
#include "stack.h"
#include <stdio.h>
#include "List.h"

List List_create() {
    Position header;
    NEW( header );
    header->next = NULL;

    return header;
}

void List_dispose( List *list ) {
    List_makeEmpty( *list );
    Position header = List_header( *list );
    FREE( header );
    *list = NULL;
}

void List_makeEmpty( List list ) {
    Position first = List_first( list );
    for( Position next; first; first = next ) {
        next = first->next;
        FREE( first );
    }
    Position header =  List_header( list );
    header->next = NULL;
}

void List_insert( List list, Position pos, void* element ) {
    Position temp;
    NEW( temp );
    temp->element = element;
    temp->next = pos->next;
    pos->next = temp;
}

void List_delete( List list, void* element ) {
    Position previous = List_findPrevious( list, element );
    if( previous != NULL ) {
        Position pos = previous->next;
        previous->next = pos->next;
        FREE( pos ); 
    }
}

Position List_find( List list, void* element ) {
    Position pos = List_first( list );
    while( pos != NULL && pos->element != element ) {
        pos = pos->next;
    }
    return pos;
}

Position List_findPrevious( List list, void* element ) {
    Position pos = List_header( list );
    while( !List_isLast( pos ) && element != pos->next->element ) {
        pos = pos->next;
    }
    return pos;
}

Position List_header( List list ) {
    return list;
}

Position List_first( List list ) {
    Position header = List_header( list );
    return header->next;
}

int List_isEmpty( List list ) {
    Position header = List_header( list );
    return header->next == NULL;
}

int List_isLast( Position pos ) {
    return pos->next == NULL;
}

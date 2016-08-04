#include <stddef.h>
#include "assert.h"
#include "mem.h"
#include "stack.h"
#include <stdio.h>
#include "List.h"


List List_create() {
    List list;
    NEW( list );
    list->next = NULL;

    return list;
}

void List_dispose( List *list ) {
    List_makeEmpty( *list );
    FREE( *list );
    list = NULL;
}

void List_makeEmpty( List list ) {
    Position next;
    for( Position pos = list->next; pos; pos = next ) {
        next = pos->next;
        FREE( pos );
    }
    list->next = NULL;
}

void List_insert( List list, Position pos, void* element ) {
    Position tempCell;
    NEW( tempCell );
    tempCell->element = element;
    tempCell->next = pos->next;
    pos->next = tempCell;
}

void List_delete( List list, void* element ) {
    Position previousPos = List_findPrevious( list, element );
    if( previousPos != NULL ) {
        Position pos = previousPos->next;
        previousPos->next = pos->next;
        FREE( pos ); 
    }
}

Position List_find( List list, void* element ) {
    Position pos = list->next;
    while( pos != NULL && pos->element != element ) {
        pos = pos->next;
    }
    return pos;
}

Position List_findPrevious( List list, void* element ) {
    Position pos = list;
    while( !List_isLast( pos ) && element != pos->next->element ) {
        pos = pos->next;
    }
    return pos;
}

int List_isEmpty( List list ) {
    return list->next == NULL;
}

int List_isLast( Position pos ) {
    return pos->next == NULL;
}

#ifndef _LIST_H
#define _LIST_H

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

struct Node
{
    void* element;
    Position next;
};

extern List List_create();
extern void List_dispose( List *list );
extern void List_makeEmpty( List list );
extern void List_insert( List list, Position pos, void* element );
extern void List_delete( List list, void* element );
extern Position List_find( List list, void* element );
extern Position List_findPrevious( List list, void* element );

extern int List_isEmpty( List list );
extern int List_isLast( Position pos );

#endif
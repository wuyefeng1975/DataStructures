#ifndef _LIST_H
#define _LIST_H

typedef struct ListNode *PtrToNode;
typedef PtrToNode NodePosition;
typedef struct List *List;

struct ListNode
{
    void* element;
    NodePosition next;
};

struct List {
    size_t data_size;
    NodePosition header;
};

extern List List_create( size_t data_size );
extern void List_dispose( List *list );
extern void List_make_empty( List list );
extern NodePosition List_find_previous( List list, NodePosition pos );
extern NodePosition List_insert( List list, NodePosition pos, void *elementvoid, void (*assign)(void*, const void*) );
extern NodePosition List_delete( List list, NodePosition pos );
extern NodePosition List_find( List list, void* element, int (*compair)(const void*, const void*) );
extern void List_push_front( List list, void* element, void (*assign)(void*, const void*) );
extern void List_pop_front( List list );
extern void* List_first( List list );
#endif
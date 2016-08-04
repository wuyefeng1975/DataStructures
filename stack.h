#ifndef STACK_H
#define STACK_H

#define T Stack_T
typedef struct T *T;

struct T {
    void *element;
    T next;
};

extern T Stack_create();
extern void Stack_dispose( T *stack );
extern void Stack_push( T stack, void *element );
extern void* Stack_pop( T stack );
extern void Stack_makeEmpty( T stack );

extern int Stack_isEmpty( T list );
extern void* Stack_top( T stack );

#undef T
#endif
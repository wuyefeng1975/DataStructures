#ifndef MEM_H
#define MEM_H

#include <string.h>
#include "except.h"

extern const Except_T Mem_Failed;
extern void *Mem_alloc( long nbytes, const char *file, int line );
extern void *Mem_calloc( long count, long nbytes, const char *file, int line );
extern void *Mem_copy( void* destination, void* source, long nbytes, const char *file, int line );

#define ALLOC(nbytes) Mem_alloc((nbytes), __FILE__, __LINE__)
#define CALLOC(count, nbytes) Mem_alloc((count), (nbytes), __FILE__, __LINE__)
#define COPY(destination, source, nbytes) Mem_copy((destination), (source), (nbytes), __FILE__, __LINE__)
#define NEW(p) ((p) = ALLOC((long)sizeof *(p)))
#define NEW0(p) ((p) = CALLOC(1, (long)sizeof *(p)))

extern void Mem_free( void *ptr, const char *file, int line );
#define FREE(ptr) ((void)(Mem_free(ptr, __FILE__, __LINE__)), ptr = 0)

extern void *Mem_resize( void *ptr, long nbytes, const char *file, int line );
#define RESIZE(ptr, nbytes) ((ptr) = Mem_resize( ptr, nbytes, __FILE__, __LINE__))
#endif
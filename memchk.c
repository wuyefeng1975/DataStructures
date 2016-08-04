#include <stdlib.h> 
#include <string.h> 
#include "assert.h" 
#include "except.h" 
#include "mem.h"

static struct descriptor {
    struct descriptor *free;
    struct descriptor *link;
    const void *ptr;
    long size;
    const char *file;
    int line;
} *htab[2048];

static struct descriptor freelist = { &freelist };
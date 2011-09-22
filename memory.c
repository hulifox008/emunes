#include <stdlib.h>
#include <assert.h>
#include "memory.h"

unsigned char * memory_allocate(int size)
{
    assert(size>0);
    return (unsigned char*)malloc(size);
}

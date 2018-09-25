#ifndef COLLECTIONS_C_MEMORY
#define COLLECTIONS_C_MEMORY 1


#include <stddef.h>


void *allocate(size_t size);

void deallocate(void *ptr);


#endif

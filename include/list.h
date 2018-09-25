#ifndef COLLECTIONS_C_LIST
#define COLLECTIONS_C_LIST 1


#include <stdint.h>
#include "error.h"


typedef struct LinkedList LinkedList;


CollectionError list_new(LinkedList **list);

uint64_t list_count(LinkedList *list);

CollectionError list_push(LinkedList *list, void *value);

CollectionError list_pop(LinkedList *list, void **value);

void list_free(LinkedList *list);


#endif

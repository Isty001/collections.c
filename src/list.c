#include <mem_pool.h>
#include "list.h"
#include "memory.h"
#include "error_internal.h"


static FixedMemPool *ENTRY_POOL = NULL;


typedef struct Entry Entry;

struct Entry {
    struct Entry *next;
    struct Entry *prev;
    void *val;
};

struct LinkedList {
    uint64_t count;
    Entry *first;
    Entry *last;
};


CollectionError list_new(LinkedList **list)
{
    *list = allocate(sizeof(LinkedList));

    if (NULL == *list) {
        return COLL_ERR_ALLOC;
    }
    (*list)->count = 0;

    return COLL_ERR_OK;
}

static Entry *allocate_entry(void *val)
{
    if (!ENTRY_POOL) {
        if (MEM_POOL_ERR_OK != pool_fixed_init(&ENTRY_POOL, sizeof(Entry), 100)) {
            return NULL;
        }
    }
    Entry *entry;

    if (MEM_POOL_ERR_OK != pool_fixed_alloc(ENTRY_POOL, (void **) &entry)) {
        return NULL;
    }
    entry->val = val;
    entry->prev = NULL;
    entry->next = NULL;

    return entry;
}

static void deallocate_entry(Entry *entry)
{
    pool_fixed_free(ENTRY_POOL, entry);
}

uint64_t list_count(LinkedList *list)
{
    return list->count;
}

CollectionError list_push(LinkedList *list, void *value)
{
    Entry *entry = allocate_entry(value);
    check_alloc(entry);

    if (0 != list->count) {
        entry->prev = list->last;
        list->last->next = entry;
        list->last = entry;
    } else {
        list->first = entry;
        list->last = entry;
    }
    list->count++;

    return COLL_ERR_OK;
}

CollectionError list_pop(LinkedList *list, void **value)
{
    if (0 == list->count) {
        *value = NULL;
        return COLL_ERR_EMPTY;
    }

    Entry *last = list->last;

    if (--list->count) {
        list->last = last->prev;
        list->last->next = NULL;
    } else {
        list->first = NULL;
        list->last = NULL;
    }

    *value = last->val;
    deallocate_entry(last);

    return COLL_ERR_OK;
}

void list_free(LinkedList *list)
{
    deallocate(list);
}

void list_deinit()
{
    if (ENTRY_POOL) {
        pool_fixed_destroy(ENTRY_POOL);
    }
}


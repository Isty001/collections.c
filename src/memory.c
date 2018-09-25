#include <mem_pool.h>
#include "list_internal.h"


static VariableMemPool *COMMON_POOL = NULL;


void collections_init(void)
{
    pool_variable_init(&COMMON_POOL, 200, 10);
}

void collections_deinit(void)
{
    pool_variable_destroy(COMMON_POOL);
    list_deinit();
}

void *allocate(size_t size)
{
    void *ptr;

    if (MEM_POOL_ERR_OK != pool_variable_alloc(COMMON_POOL, size, &ptr)) {
        return NULL;
    }

    return ptr;
}

void deallocate(void *ptr)
{
    pool_variable_free(COMMON_POOL, ptr);
}

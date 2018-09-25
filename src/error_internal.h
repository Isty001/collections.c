#ifndef COLLECTIONS_C_ERROR_INTERNAL
#define COLLECTIONS_C_ERROR_INTERNAL 1


#include "error.h"


#define check_alloc(expr) \
    if (NULL == (expr)) return COLL_ERR_ALLOC;


#endif

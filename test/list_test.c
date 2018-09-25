#include <ctest.h>
#include <collections-c/list.h>


CTEST(list, push_pop)
{
    LinkedList *list;

    ASSERT_EQUAL(COLL_ERR_OK, list_new(&list));

    int a = 10;
    int b = 20;
    int c = 30;

    ASSERT_EQUAL(COLL_ERR_OK, list_push(list, &a));
    ASSERT_EQUAL(1, list_count(list));

    ASSERT_EQUAL(COLL_ERR_OK, list_push(list, &b));
    ASSERT_EQUAL(2, list_count(list));
 
    ASSERT_EQUAL(COLL_ERR_OK, list_push(list, &c));
    ASSERT_EQUAL(3, list_count(list));

    int *ret = NULL;
    ASSERT_EQUAL(COLL_ERR_OK, list_pop(list, (void **) &ret));
    ASSERT_EQUAL(30, *ret);
    ASSERT_EQUAL(2, list_count(list));

    ASSERT_EQUAL(COLL_ERR_OK, list_pop(list, (void **) &ret));
    ASSERT_EQUAL(20, *ret);
    ASSERT_EQUAL(1, list_count(list));

    ASSERT_EQUAL(COLL_ERR_OK, list_pop(list, (void **) &ret));
    ASSERT_EQUAL(10, *ret);
    ASSERT_EQUAL(0, list_count(list));

    ASSERT_EQUAL(COLL_ERR_EMPTY, list_pop(list, (void **) &ret));
    ASSERT_NULL(ret);
    ASSERT_EQUAL(0, list_count(list));
}

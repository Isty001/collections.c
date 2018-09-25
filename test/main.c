#define CTEST_MAIN


#include <locale.h>
#include <ctest.h>
#include <collections-c/init.h>


int main(int argc, const char **argv)
{
    collections_init();

    int code = ctest_main(argc, argv);

    collections_deinit();

    return code;
}

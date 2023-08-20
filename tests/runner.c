#include <stdio.h>
#include <string.h>

#include "parser.h"

int tests_run = 0;

#define FAIL() printf("\n %s() failed @ line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define _verify(test) do { int r=test(); tests_run++; if(r) return r; } while(0)

int test_hello_world()
{
    uint8_t scroll = 0;
    parse_byte('H',
        &cursor,
        *screen_buffer,
        &scroll);
    _assert( (char) screen_buffer[cursor.row][cursor.col - 1] ==  'H');
}


int all_tests()
{
    test_hello_world();
    return 0;
}


int main(int argc, char **argv)
{
    int result = all_tests();
    if (result == 0)
        printf("PASSED\n");
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}


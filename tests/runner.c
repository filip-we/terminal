#include <stdio.h>
#include "parser.h"
//#include "screen.h"

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
    _assert( (&screen_buffer) == 'H');
}

int square_01() {
    int x=5;
    _assert(x == 25);
    return 0;
}

int all_tests() {
    _verify(square_01);
    return 0;
}

int main(int argc, char **argv) {
    int result = all_tests();
    if (result == 0)
        printf("PASSED\n");
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}


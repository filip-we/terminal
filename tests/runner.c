#include <stdio.h>
#include <string.h>

#include "parser.h"

#define ROW_LENGTH 8
#define COL_LENGTH 8

int tests_run = 0;

#define FAIL() printf("\n %s() failed @ line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define _verify(test) do { int r=test(); tests_run++; if(r) return r; } while(0)

uint8_t scroll;


int _cmp_arrays(char a[], char b[], int n)
{
    uint8_t i;
    for (i = 0; i < n; i++)
    {
        if (a[i] != b[i]) return 1;
    }
}


void print_screen_buffer(char *buff)
{
    char border[ROW_LENGTH] = "========";
    printf("%s \n", border);
    uint8_t row;
    for (row = 0; row < ROW_LENGTH; row ++)
    {
        printf("|%.*s|\n", ROW_LENGTH, (buff + row * COL_LENGTH));
    }
    printf("%s \n", border);
}


int test_hello_world()
{
    scroll = 0;
    char buff[ROW_LENGTH][COL_LENGTH];
    parse_byte('H',
        &cursor,
        *buff,
        &scroll);
    _assert( (char) buff[cursor.row][cursor.col - 1] ==  'H');
    return 0;
}


int test_carrige_return()
{
    scroll = 0;
    char buff[ROW_LENGTH][COL_LENGTH];
    char input[12] = "ABCDEFG";
    //input[0] = 0x0a;
    uint8_t i;
    //for (i = 0; i < sizeof(input); i++);
    for (i = 0; i < 12; i++);
        printf("%i: %c\n", input[i]);
        parse_byte(input[i],
            &cursor,
            *buff,
            &scroll);

    //print_screen_buffer(*buff);
    //printf("%s", *(screen_buffer + ROW_LENGTH));
    _assert(
        //(char) strcmp(*(buff + ROW_LENGTH), input) == 0
        (char) _cmp_arrays(buff, input, 4) == 0
    );
    return 0;
}


int all_tests()
{
    _verify(test_hello_world);
    _verify(test_carrige_return);
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


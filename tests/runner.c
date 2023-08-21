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
        //printf("%c, %c \n", a[i], b[i]);
        if (a[i] != b[i]) return 1;
    }
    return 0;
}


void print_screen_buffer(char *buff)
{
    char border[ROW_LENGTH + 2] = "==========";
    printf("%s \n", border);
    uint8_t row;
    for (row = 0; row < ROW_LENGTH; row ++)
    {
        printf("|");
        for (uint8_t col = 0; col < COL_LENGTH; col++)
        {
            if (buff[row * COL_LENGTH + col] >= 0x20)
            {
                printf("%c", buff[row * COL_LENGTH + col]);
            }
            else
            {
                printf(" ");
            }
        }
        printf("|\n");
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
    print_screen_buffer(*buff);
    _assert( (char) buff[cursor.row][cursor.col - 1] ==  'H');
    return 0;
}


int test_carrige_return()
{
    cursor.row = 0;
    cursor.col = 0;
    scroll = 0;
    char buff[ROW_LENGTH][COL_LENGTH];
    char input[12] = "ABC DEFGHIJK";
    input[3] = 0x0a;
    for (uint8_t i = 0; i < sizeof(input); i++)
    {
        parse_byte(input[i],
            &cursor,
            *buff,
            &scroll);
    }

    print_screen_buffer(*buff);
    char expected[12] = "ABC      DEF";
    _assert(_cmp_arrays(expected, *buff, 12) == 0);
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


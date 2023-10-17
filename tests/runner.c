#define SCREEN_ROWS 12
#define SCREEN_COLUMNS 12

#include <stdio.h>
#include <string.h>

#include "parser.h"


int tests_run = 0;

#define FAIL() printf("\n %s() failed @ line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define _verify(test) do { int r=test(); tests_run++; if(r) return r; } while(0)

uint8_t scroll;


void _init_test()
{
    cursor.row = 0;
    cursor.col = 0;
    scroll = 0;
}


int _cmp_arrays(char* a, char* b, int n)
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
    char border[SCREEN_ROWS + 2] = "==============";
    printf("%s \n", border);
    uint8_t row;
    for (row = 0; row < SCREEN_COLUMNS; row ++)
    {
        printf("|");
        for (uint8_t col = 0; col < SCREEN_COLUMNS; col++)
        {
            if (buff[row * SCREEN_COLUMNS + col] >= 0x20 )
            {
                printf("%c", buff[row * SCREEN_COLUMNS + col]);
            }
            else if (buff[row * SCREEN_COLUMNS + col] == 0)
                printf(" ");
            else
            {
                printf("!");
            }
        }
        printf("|\n");
    }
    printf("%s \n", border);
}


int test_hello_world()
{
    scroll = 0;
    char buff[SCREEN_ROWS][SCREEN_COLUMNS];
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
    char buff[SCREEN_ROWS * SCREEN_COLUMNS] = {0};
    char input[12] = "ABCD__123456";
    input[4] = 0x1B;
    input[5] = 'E';
    for (uint8_t i = 0; i < sizeof(input); i++)
    {
        parse_byte(input[i],
            &cursor,
            buff,
            &scroll);
    }

    print_screen_buffer(buff);
    char expected[32] = {'A', 'B', 'C', 'D', 0, 0, 0, 0, 0, 0, 0, 0, '1', '2', '3', '4'};
    _assert(_cmp_arrays(expected, buff, 10) == 0);
    return 0;
}

int test_set_cursor()
{
    cursor.row = 0;
    cursor.col = 0;
    scroll = 0;
    char buff[SCREEN_ROWS * SCREEN_COLUMNS] = {0};
    char input[16] = "_[0;10H1234";
    input[0] = 0x1B;
    for (uint8_t i = 0; i < sizeof(input); i++)
    {
        parse_byte(input[i],
            &cursor,
            buff,
            &scroll);
    }
    print_screen_buffer(buff);
    char expected[18] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '1', '2', '3', '4', 0, 0, 0};
    _assert(_cmp_arrays(expected , buff, 10) == 0);
    return 0;
}


int test_clear_screen()
{
    char buff[SCREEN_ROWS * SCREEN_COLUMNS] = {
        '1', '2', '3', '4',  '5', '6', '7', '8',  'A', 'B', 'C', 'D',
        'A', 'A', 'A', 'A',  'A', 'A', 'A', 'A',  'A', 'A', 'A', 'A',
        'A', 'A', 'A', 'A',  'A', 'A', 'A', 'A',  'A', 'A', 'A', 'A'
    };
    print_screen_buffer(buff);
    cursor.row = 0;
    cursor.col = 1;
    scroll = 0;
    char input[4] = "_[0J";
    input[0] = 0x1B;
    for (uint8_t i = 0; i < sizeof(input); i++)
    {
        parse_byte(input[i],
            &cursor,
            buff,
            &scroll);
    }
    print_screen_buffer(buff);
    char expected[18] = {
        'A', 'A', 'A', 'A',  'A', 'A', 'A', 'A',  'A', 'A', 'A', 'A',
        'A', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' '};
    _assert(_cmp_arrays(expected , buff, 18) == 0);
    return 0;
}

int all_tests()
{
    _verify(test_hello_world);
    _verify(test_carrige_return);
    _verify(test_set_cursor);
    _verify(test_clear_screen);
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


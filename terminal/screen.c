#include <string.h>

#include "screen.h"


void advance_scrolling()
{
    // Clean next row.
    //memset(screen_buffer[screen_buff_scroll + SCREEN_ROWS], 0, sizeof(char) * SCREEN_COLUMNS);
    memset(
        *(screen_buffer +
            ((cursor.row + screen_buff_scroll) * SCREEN_COLUMNS) +
            (cursor.col )),
            0,
            sizeof(char) * SCREEN_COLUMNS);
    screen_buff_scroll ++;
}


void screen_write_char(char ch, uint8_t row, uint8_t col)
{
    screen_buffer[screen_buff_scroll + row][col] = ch;
}


void screen_write_char_at_cursor(char ch,
    struct Cursor * cursor,
    char* screen_buffer,
    uint8_t* screen_buff_scroll)
{
    *(screen_buffer +
        ((cursor -> row + *screen_buff_scroll) * SCREEN_COLUMNS) +
        (cursor -> col )) = ch;
    (*cursor).col ++;

    *(screen_buffer + 1) = (char) (*screen_buff_scroll + 49);
    if (cursor -> col == SCREEN_COLUMNS)
    {
        cursor -> col = 0;
        cursor -> row ++;
        if (cursor -> row == SCREEN_ROWS)
        {
            cursor -> row = SCREEN_ROWS - 1;
            //advance_scrolling();
            //memset(screen_buffer[screen_buff_scroll + SCREEN_ROWS], 0, sizeof(char) * SCREEN_COLUMNS);
            * screen_buff_scroll ++;
        }
    }
}


void screen_display_test_image(unsigned char* font_map)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            print_char(font_map, (x + y * 16), x * 8, y * 16);
        }
    }
}

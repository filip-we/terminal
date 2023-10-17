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
    uint8_t* scroll)
{
    *(screen_buffer +
        ((cursor -> row + *scroll) * SCREEN_COLUMNS) +
        (cursor -> col )) = ch;
}


void increase_cursor(struct Cursor * cursor, uint8_t* scroll)
{
    (*cursor).col ++;
    if (cursor -> col == SCREEN_COLUMNS)
    {
        cursor -> col = 0;
        cursor -> row ++;
        if (cursor -> row == SCREEN_ROWS)
        {
            cursor -> row = SCREEN_ROWS - 1;
            (*scroll) ++;
        }
    }
}


void decrease_cursor(struct Cursor * cursor, uint8_t* scroll)
{
    (*cursor).col --;
    if (cursor -> col == -1)
    {
        (*cursor).col = SCREEN_COLUMNS - 1;
        (*cursor).row --;
        if (cursor -> row == -1)
        {
            (*cursor).row = 0;
            (*cursor).col = 0;
        }

    }

}


void cursor_up(struct Cursor * cursor, uint8_t* scroll, uint8_t lines)
{
    if ( lines == 0 )
        lines = 1;
    (*cursor).row -= lines;
    if ( (*cursor).row >= SCREEN_ROWS )
        (*cursor).row = SCREEN_ROWS;
    if ( (*cursor).row < 0 )
        (*cursor).row = 0;
}


void cursor_down(struct Cursor * cursor, uint8_t* scroll, uint8_t lines)
{
    if ( lines == 0 )
        lines = 1;
    cursor_up(cursor, scroll, lines);
}


void cursor_right(struct Cursor * cursor, uint8_t* scroll, uint8_t rows)
{
    if ( rows == 0 )
        rows = 1;
    (*cursor).row += rows;
    if ( (*cursor).row > SCREEN_ROWS )
        (*cursor).row = SCREEN_ROWS;
    if ( (*cursor).row < 0 )
        (*cursor).row = 0;
}


void cursor_left(struct Cursor * cursor, uint8_t* scroll, uint8_t rows)
{
    if (rows == 0)
        rows = 1;
    cursor_right(cursor, scroll, -rows);
}


void clear_screen(struct Cursor * cursor, uint8_t* scroll, char* screen_buffer, uint8_t p)
{
    // SCREEN_COLUMNS is defined in screen.h and not in tests/runner.c as I thought.
    if (p == 0)
    {
        for (int c = cursor -> col; c < SCREEN_COLUMNS; c++)
        {
            *(screen_buffer +
                    ((cursor -> row + *scroll) * SCREEN_COLUMNS) +
                    c) = ' ';
        }

        for (int r = (cursor -> row + screen_buff_scroll + 1); r < SCREEN_ROWS; r++)
        {
            for (int c = 0; c < SCREEN_COLUMNS; c ++)
            {
                *(screen_buffer + r * SCREEN_COLUMNS + c) = ' ';
            }
        }
    }
}

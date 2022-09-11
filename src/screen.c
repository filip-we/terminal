#include "screen.h"
#include "IBM_VGA_8x16.h"

#include "pico/stdlib.h"
#include "bsp/board.h"


void advance_scrolling()
{
    // Clean next row.
    memset(screen_buffer[screen_buff_scroll + SCREEN_ROWS], 0, sizeof(char) * SCREEN_COLUMNS);
    screen_buff_scroll ++;

}

void screen_write_char(char ch, uint8_t row, uint8_t col)
{
    screen_buffer[screen_buff_scroll + row][col] = ch;
}


void screen_write_char_at_cursor(char ch)
{
    screen_buffer[screen_buff_scroll + cursor.row][cursor.col] = ch;
    cursor.col ++;
    if (cursor.col == SCREEN_COLUMNS)
    {
        cursor.col = 0;
        cursor.row ++;
        if (cursor.row == SCREEN_ROWS)
        {
            cursor.row = SCREEN_ROWS - 1;
            advance_scrolling();
        }
    }
}


void screen_display_test_image()
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            print_char(IBM_VGA_8x16, (x + y * 16), x * 8, y * 16);
        }
    }
}



void screen_update()
{
    for (int row = 0; row < SCREEN_ROWS; row++)
    {
        for (int col = 0; col < SCREEN_COLUMNS; col++)
        {
            print_char(IBM_VGA_8x16,
                screen_buffer[screen_buff_scroll + row][col],
                col * FONT_WIDTH,
                row * FONT_HEIGHT);
        }
    }
}


void screen_init()
{
    sleep_ms(100); // Allow the screen to wake up after power off.
    screen_hw_init();
    fill_display();
    screen_buff_scroll = 0;
    screen_update();
}

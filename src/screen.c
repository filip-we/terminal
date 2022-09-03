#include "IBM_VGA_8x16.h"
#include "hardware/screen_interface.h"

#include "hardware/screen_interface.c"

#define FONT_WIDTH 16
#define FONT_HEIGHT 16

// These need to be changed if screen rotation is changed.
#ifndef SCREEN_COLUMNS
#define SCREEN_COLUMNS 20
#endif
#ifndef SCREEN_ROWS
#define SCREEN_ROWS 15
#endif

char screen_buffer[SCREEN_COLUMNS][SCREEN_ROWS];


void screen_display_char(char ch, uint8_t col, uint8_t row)
{
    screen_buffer[col][row] = ch;
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
                screen_buffer[col][row],
                col * FONT_WIDTH,
                row * FONT_HEIGHT);
        }
    }
}


void screen_init()
{
    struct RGB bg_color;
    bg_color.red = 0x01;
    bg_color.green = 0x10;
    bg_color.blue = 0x0A;

    sleep_ms(100); // Allow the screen to wake up after power off.
    screen_hw_init();
    fill_display(&bg_color);
}

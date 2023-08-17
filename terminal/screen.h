#ifndef screen_h
#define screen_h

#define FONT_WIDTH 16
#define FONT_HEIGHT 16

// These need to be changed if screen rotation is changed.
#ifndef SCREEN_COLUMNS
#define SCREEN_COLUMNS 8//15
#endif
#ifndef SCREEN_ROWS
#define SCREEN_ROWS 8//20
#endif
#ifndef SCREEN_BUFFER_NR_OF_ROWS
#define SCREEN_BUFFER_NR_OF_ROWS 255
#endif
#ifndef SCREEN_GRID_SIZE
#define SCREEN_GRID_SIZE 300
#endif

#include <stdint.h>
#include <stdbool.h>

static char screen_buffer[SCREEN_BUFFER_NR_OF_ROWS][SCREEN_COLUMNS];

static uint8_t screen_buff_scroll;

static struct Cursor {
    uint8_t row;
    uint8_t col;
} cursor;

void screen_write_char(char ch, uint8_t row, uint8_t col);
void screen_write_char_at_cursor(
    char ch,
    struct Cursor *,
    char* screen_buffer,
    uint8_t* screen_buff_scroll);
void screen_update();

#endif

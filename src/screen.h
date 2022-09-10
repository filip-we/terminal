#ifndef screen_h
#define screen_h
#include "hardware/screen_interface.h"

void screen_write_char(char ch, uint8_t row, uint8_t col);
void screen_write_char_at_cursor(char ch);
void screen_display_test_image();
void screen_set_bg_color(RGB *color);
void screen_update();
void screen_init();

struct Cursor {
    uint8_t row;
    uint8_t col;
} cursor;


#endif

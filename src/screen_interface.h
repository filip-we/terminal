#ifndef screen_interface_h
#define screen_interface_h

#define SCREEN_SOFTRESET                0x01
#define SCREEN_SLEEP_IN                 0x10
#define SCREEN_SLEEP_OUT                0x11
#define SCREEN_NORMALDISP               0x13
#define SCREEN_INVERTOFF                0x20
#define SCREEN_INVERTON                 0x21
#define SCREEN_GAMMA_SET                0x26
#define SCREEN_DISPLAY_OFF              0x28
#define SCREEN_DISPLAY_ON               0x29
#define SCREEN_COLUMN_ADDR_SET          0x2A
#define SCREEN_PAGE_ADDR_SET            0x2B
#define SCREEN_MEMORY_WRITE             0x2C
#define SCREEN_MEMORY_ACCESS_CTL        0x36
#define SCREEN_PIXEL_FORMAT_SET         0x3A
#define SCREEN_FRAME_RATE_CTL           0xB1
#define SCREEN_DISPLAY_FUNCTION_CTL     0xB6
#define SCREEN_ENTRYMODE                0xB7
#define SCREEN_POWER_CTL_1              0xC0
#define SCREEN_POWER_CTL_2              0xC1
#define SCREEN_VCOM_CTL_1               0xC5
#define SCREEN_VCOM_CTL_2               0xC7
#define SCREEN_POWER_CTL_A              0xCB
#define SCREEN_POWER_CTL_B              0xCF
#define SCREEN_DRIVER_TIMING_A          0xE8
#define SCREEN_DRIVER_TIMING_B          0xEA
#define SCREEN_POWER_ON_SEQUENCE_CTL    0xED
#define SCREEN_PUMP_RATIO_CTL           0xF7
#define SCREEN_ENABLE_3G                0xF2

#define SCREEN_MADCTL_MY                0x80
#define SCREEN_MADCTL_MX                0x40
#define SCREEN_MADCTL_MV                0x20
#define SCREEN_MADCTL_ML                0x10
#define SCREEN_MADCTL_RGB               0x00
#define SCREEN_MADCTL_BGR               0x08
#define SCREEN_MADCTL_MH                0x04

#ifndef SCREEN_PIN_START
#define SCREEN_PIN_START  6
#endif
#ifndef SCREEN_RST
#define SCREEN_RST  (SCREEN_PIN_START     )
#endif
#ifndef SCREEN_RD
#define SCREEN_RD   (SCREEN_PIN_START + 1 )
#endif
#ifndef SCREEN_WR
#define SCREEN_WR   (SCREEN_PIN_START + 2 )
#endif
#ifndef SCREEN_CD
#define SCREEN_CD   (SCREEN_PIN_START + 3 )
#endif
#ifndef SCREEN_CS
#define SCREEN_CS   (SCREEN_PIN_START + 4 )
#endif
#ifndef SCREEN_DATA
#define SCREEN_DATA 14
#endif

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH 320
#endif
#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT 240
#endif
#ifndef SCREEN_ORIENTATION
#define SCREEN_ORIENTATION 1
#endif

#include "pico/stdlib.h"

typedef struct rgb {
    unsigned int red    : 5;
    unsigned int green  : 6;
    unsigned int blue   : 5;
} RGB;

RGB bg_color;
RGB fg_color;

void fill_display();
void print_char(unsigned char *font_map, unsigned char char_nr, uint16_t x_pos, uint16_t y_pos);
void screen_hw_init();
void set_screen_data(char data);
void screen_write_command(char cmd);
void screen_write_data(char data);
void screen_write_color_data(RGB *color);


#endif

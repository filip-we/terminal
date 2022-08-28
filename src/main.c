/*
 * Terminal: A tiny VT100-inspired physical terminal for Linux.
 *
 */

//#include <stdlib.h>
//#include <stdio.h>
#include "config.h"

#include "pico/stdlib.h"
#include "bsp/board.h"
#include "tusb.h"

#include "screen_interface.c"
#include "IBM_VGA_8x16.h"


struct RGB {
    unsigned int red    : 6;
    unsigned int green  : 5;
    unsigned int blue   : 6;
};

static void start_communications();
static void fill_display(struct RGB *rgb);
static void print_char(unsigned char *font_map, unsigned char char_nr, uint16_t x_pos, uint16_t y_pos);

static void start_communications()
{
    stdio_init_all();
    gpio_set_function(PICO_DEFAULT_UART_TX_PIN , GPIO_FUNC_UART);
    gpio_set_function(PICO_DEFAULT_UART_RX_PIN , GPIO_FUNC_UART);
    gpio_set_dir(PICO_DEFAULT_UART_TX_PIN, GPIO_OUT);
    gpio_set_dir(PICO_DEFAULT_UART_RX_PIN, GPIO_IN);

}

static void print_char(unsigned char *font_map, unsigned char char_nr, uint16_t x_pos, uint16_t y_pos)
{
    screen_write_command(SCREEN_COLUMN_ADDR_SET);
    screen_write_data(x_pos >> 8);
    screen_write_data(x_pos & 0xFF);
    screen_write_data((x_pos + 7) >> 8);
    screen_write_data((x_pos + 7) & 0xFF);

    screen_write_command(SCREEN_PAGE_ADDR_SET);
    screen_write_data(y_pos >> 8);
    screen_write_data(y_pos & 0xFF);
    screen_write_data((y_pos + 31) >> 8);
    screen_write_data((y_pos + 31) & 0xFF);

    screen_write_command(SCREEN_MEMORY_WRITE);
    struct RGB color;
    color.red = 0;
    color.green = 0b1111;
    color.blue = 0b11111;

    char row;
    for (uint16_t y = 0; y < 16 ; y++)
    {
        row = font_map[char_nr * 16 + y];
        for (uint16_t x = 0; x < 8; x++)
        {
            if (row & 128)
            {
                screen_write_data(0xFF);
                screen_write_data(0xFF);
            }
            else
            {
                screen_write_data((color.red << 3) + (color.green >> 5));
                screen_write_data((color.blue >> 3) + ((color.green << 3) & 0xFF));
            }
            row = row << 1;
        }
    }
}

static void fill_display(struct RGB *rgb)
{
    screen_write_command(SCREEN_ORIENTATION ? SCREEN_PAGE_ADDR_SET : SCREEN_COLUMN_ADDR_SET);
    screen_write_data(0);
    screen_write_data(0);
    screen_write_data(SCREEN_WIDTH >> 8);
    screen_write_data(SCREEN_WIDTH & 0xFF);

    screen_write_command(SCREEN_ORIENTATION ? SCREEN_COLUMN_ADDR_SET : SCREEN_PAGE_ADDR_SET);
    screen_write_data(0);
    screen_write_data(0);
    screen_write_data(SCREEN_HEIGHT >> 8);
    screen_write_data(SCREEN_HEIGHT & 0xFF);

    screen_write_command(SCREEN_MEMORY_WRITE);
    for (uint32_t y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (uint32_t x = 0; x < SCREEN_WIDTH; x++)
        {
            screen_write_data((rgb -> red << 3) + (rgb -> green >> 5));
            screen_write_data((rgb -> blue >> 3) + ((rgb -> green << 3) & 0xFF));
        }
    }
}


int main (void)
{
    uint32_t time = 0;
    uint32_t led_pin = PICO_DEFAULT_LED_PIN;

    start_communications();

    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    gpio_put(led_pin, 0);

    // Allow the screen to wake up after power off.
    sleep_ms(100);

    struct RGB bg_color;
    bg_color.red = 0x01;
    bg_color.green = 0x01;
    bg_color.blue = 0x0F;

    screen_init();
    fill_display(&bg_color);
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            print_char(IBM_VGA_8x16, (x + y * 16), x * 8, y * 16);
        }
    }

    printf("TinyUSB-Init\r\n");
    tusb_init();
    gpio_put(led_pin, true);
    printf("Loop\r\n");
    while (true)
    {
        printf("Host-task\r\n");
        tuh_task();

        time ++;
        if (time > 1000)
        {
            printf("LED off!\r\n");
            time = 0;
            gpio_put(led_pin, true);
        }
        else if (time > 500)
        {
            gpio_put(led_pin, false);
        }
    }
    return 0;
}

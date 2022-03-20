/*
 * Terminal: A tiny VT100-inspired physical terminal for Linux.
 *
 */

//#include <stdlib.h>
//#include <stdio.h>

#include "pico/stdlib.h"

// TinyUSB imports
#include "bsp/board.h"
#include "tusb.h"

// Own code
#include "screen_interface.c"

static void display_test();

int main (void)
{
    uint32_t led_pin = PICO_DEFAULT_LED_PIN;
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    gpio_put(led_pin, 0);

    // Allow the screen to wake up after power off.
    sleep_ms(100);

    screen_init();
    display_test();
    while (true)
    {
        gpio_put(led_pin, true);
        sleep_ms(500);
        gpio_put(led_pin, false);
        sleep_ms(500);
    }
    return 0;
}

static void display_test()
{
    screen_write_command(SCREEN_COLUMN_ADDR_SET);
    screen_write_data(0x00);
    screen_write_data(0x00);

    screen_write_data(SCREEN_HEIGHT >> 8);
    screen_write_data(SCREEN_HEIGHT & 0xFF);

    char red, green, blue;
    blue = 0;
    green = 0;
    for (char r = 0; r < SCREEN_WIDTH; r++)
    {
        screen_write_command(SCREEN_PAGE_ADDR_SET);
        screen_write_data(r >> 8);
        screen_write_data(r);

        screen_write_data(SCREEN_WIDTH >> 8);
        screen_write_data(SCREEN_WIDTH & 0xFF);

        screen_write_command(SCREEN_MEMORY_WRITE);
        red = 0;
        for (char i = 0; i < SCREEN_WIDTH; i++)
        {
            screen_write_data((red << 3) + (green >> 5)); // 6 bits red, 5 bits green, 6 bits blue.
            screen_write_data((blue >> 3) + ((green << 3) & 0xFF));
            red++;
            if (red == 0x20){red = 0;}

            green = ~((r + i)) & 0x1F;
        }
        blue++;
        if (blue == 0x20){red = 0;}
    }
}


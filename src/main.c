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

#define TFT_PIN_START  9
#define TFT_RST  (TFT_PIN_START     )
#define TFT_RD   (TFT_PIN_START + 1 )
#define TFT_WR   (TFT_PIN_START + 2 )
#define TFT_CD   (TFT_PIN_START + 3 )
#define TFT_CS   (TFT_PIN_START + 4 )
#define TFT_DATA (TFT_PIN_START + 5 )

static void display_test();
static void set_tft_data(char data);
static void tft_write_command(char cmd);
static void tft_write_data(char data);

int main (void)
{
    uint32_t led_pin = PICO_DEFAULT_LED_PIN;
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

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
    for (int i = TFT_PIN_START; i < TFT_DATA + 8; i++)
    {
        gpio_init(i);
        gpio_set_dir(i, GPIO_OUT);
        gpio_put(i, 1);
    }

    gpio_put(TFT_CS, 0); // Chip select

    gpio_put(TFT_RST, 0);
    sleep_ms(120);
    gpio_put(TFT_RST, 1);
    sleep_ms(120);

    tft_write_command(0x29); // Display ON
    tft_write_command(0x13); // Normal display mode ON
    tft_write_command(0x2c); // Memory Write

    for (char i = 0; i < 200; i++)
    {
        tft_write_data(i);
    }
}

static void set_tft_data(char data)
{
    for (int i = 0; i < 8; i++)
    {
        gpio_put((TFT_DATA + i), ((data >> i)  & 0x01));
    }
}

static void tft_write_command(char cmd)
{
    gpio_put(TFT_CD, 0);
    set_tft_data(cmd);
    gpio_put(TFT_WR, 0);
    sleep_ms(5);
    gpio_put(TFT_WR, 1);
}

static void tft_write_data(char data)
{
    gpio_put(TFT_CD, 1);
    set_tft_data(data);
    gpio_put(TFT_WR, 0);
    sleep_ms(5);
    gpio_put(TFT_WR, 1);
}

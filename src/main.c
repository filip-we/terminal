/*
 * Terminal: A tiny VT100-inspired physical terminal for Linux.
 *
 */

#include "config.h"

#include "pico/stdlib.h"
#include "bsp/board.h"
#include "tusb.h"

#include "screen_interface.c"
#include "IBM_VGA_8x16.h"

static void start_communications();


static void start_communications()
{
    stdio_init_all();
    gpio_set_function(PICO_DEFAULT_UART_TX_PIN , GPIO_FUNC_UART);
    gpio_set_function(PICO_DEFAULT_UART_RX_PIN , GPIO_FUNC_UART);
    gpio_set_dir(PICO_DEFAULT_UART_TX_PIN, GPIO_OUT);
    gpio_set_dir(PICO_DEFAULT_UART_RX_PIN, GPIO_IN);

}


int main (void)
{
    uint32_t time = 0;
    uint32_t led_pin = PICO_DEFAULT_LED_PIN;

    struct RGB bg_color;
    bg_color.red = 0x01;
    bg_color.green = 0x10;
    bg_color.blue = 0x0F;

    start_communications();

    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    gpio_put(led_pin, 0);

    sleep_ms(100); // Allow the screen to wake up after power off.
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
        //printf("Host-task\r\n");
        tuh_task();

        //time ++;
        //if (time > 1000)
        //{
        //    printf("LED on!\r\n");
        //    time = 0;
        //    gpio_put(led_pin, true);
        //}
        //else if (time > 500)
        //{
        //    gpio_put(led_pin, false);
        //    printf("LED off!\r\n");
        //}
    }
    return 0;
}

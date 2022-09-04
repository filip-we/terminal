/*
 * Terminal: A tiny VT100-inspired physical terminal for Linux.
 *
 */

#include "config.h"
#include "hardware/usb_keyboard.h"

#include "pico/stdlib.h"
#include "bsp/board.h"
#include "tusb.h"
#include "screen.c"

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
    uint32_t led_pin = PICO_DEFAULT_LED_PIN;

    start_communications();
    screen_init();
    tusb_init();

    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    gpio_put(led_pin, true);

    while (true)
    {
        tuh_task();
        screen_update();

        if (kbd_buff_read != kbd_buff_write)
        {
            screen_write_char_at_cursor(kbd_buff[kbd_buff_read]);
            kbd_buff_read++;
        }
    }
    return 0;
}

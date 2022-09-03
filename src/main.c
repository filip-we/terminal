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
    uint32_t time = 0;
    uint32_t led_pin = PICO_DEFAULT_LED_PIN;

    start_communications();
    screen_init();

    screen_display_char('A', 0, 0);
    screen_display_char('B', 1, 0);
    screen_display_char('C', 2, 0);
    screen_display_char('D', 3, 0);
    screen_update();

    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    gpio_put(led_pin, 0);

    printf("TinyUSB-Init\r\n");
    tusb_init();
    gpio_put(led_pin, true);
    printf("Loop\r\n");
    while (true)
    {
        tuh_task();

        time ++;
        if (time == 200000)
        {
            printf("LED on!\r\n");
            gpio_put(led_pin, true);
        }
        else if (time == 300000)
        {
            time = 0;
            printf("LED off! %d, %d\r\n", kbd_buff_write, kbd_buff_read);
            gpio_put(led_pin, false);
        }

        if (kbd_buff_read != kbd_buff_write)
        {
            print_char(
                IBM_VGA_8x16,
                kbd_buff[kbd_buff_read],
                (kbd_buff_read % 8) * 16,
                18 * 16
            );
            kbd_buff_read++;
        }
    }
    return 0;
}

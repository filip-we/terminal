/*
 * Terminal: A tiny VT100-inspired physical terminal for Linux.
 *
 */

#include "config.h"
#include "usb_keyboard.h"
#include "screen.h"
#include "parser.h"

#include <stdio.h>
#include "pico/stdlib.h"
#include "bsp/board.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "tusb.h"


void on_uart_rx() {
    while (uart_is_readable(TERM_UART)) {
        uint8_t ch = uart_getc(TERM_UART);
        parse_byte(ch);
    }
}

static void start_communications()
{
    //stdio_init_all();
    //gpio_set_function(PICO_DEFAULT_UART_TX_PIN , GPIO_FUNC_UART);
    //gpio_set_function(PICO_DEFAULT_UART_RX_PIN , GPIO_FUNC_UART);
    //gpio_set_dir(PICO_DEFAULT_UART_TX_PIN, GPIO_OUT);
    //gpio_set_dir(PICO_DEFAULT_UART_RX_PIN, GPIO_IN);

    uart_init(TERM_UART, TERM_UART_BAUDRATE);
    gpio_set_function(TERM_UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(TERM_UART_RX_PIN, GPIO_FUNC_UART);
    gpio_set_dir(TERM_UART_TX_PIN, GPIO_OUT);
    gpio_set_dir(TERM_UART_RX_PIN, GPIO_IN);

    uart_set_hw_flow(TERM_UART, false, false);
    uart_set_format(TERM_UART, 8, 1, UART_PARITY_NONE);
    uart_set_fifo_enabled(TERM_UART, false);
}


int main ()
{
    uint32_t led_pin = PICO_DEFAULT_LED_PIN;

    start_communications();
    screen_init();
    parser_init();
    tusb_init();

    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    gpio_put(led_pin, true);

    while (true)
    {
        tuh_task();
        screen_update();
        on_uart_rx();

        if (kbd_buff_read != kbd_buff_write && uart_is_writable(TERM_UART))
        {
            uart_putc(TERM_UART, kbd_buff[kbd_buff_read]);
            kbd_buff_read++;
        }
    }
    return 0;
}

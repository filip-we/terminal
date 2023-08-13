/*
 * Terminal: A tiny VT100-inspired physical terminal for Linux.
 *
 */

#include "config.h"
#include "usb_keyboard.h"
#include "screen.h"
#include "screen_interface.h"
#include "parser.h"
#include "IBM_VGA_8x16.h"

#include <stdio.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "bsp/board.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "tusb.h"


void on_uart_rx()
{
    while (uart_is_readable(TERM_UART)) {
        uint8_t ch = uart_getc(TERM_UART);
        parse_byte(ch,
            (uint8_t *) cursor.row,
            (uint8_t *) cursor.col,
            (unsigned char*) screen_buffer);
        cursor.col ++;
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

static void uart_read_loop() {
    while (true) {
        on_uart_rx();

        if (kbd_buff_read != kbd_buff_write && uart_is_writable(TERM_UART))
        {
            uart_putc(TERM_UART, kbd_buff[kbd_buff_read]);
            kbd_buff_read++;
        }
    }
}

int main ()
{
    uint32_t led_pin = PICO_DEFAULT_LED_PIN;

    start_communications();

    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    gpio_put(led_pin, true);

    //screen_buff_scroll = 0;
    //parser_init();
    sleep_ms(100); // Allow the screen to wake up after power off.
    screen_hw_init();
    fill_display();
    tusb_init();
    //screen_display_test_image(IBM_VGA_8x16);
    screen_buffer[0][1] = 'A';
    screen_buffer[0][2] = 'B';
    screen_buffer[0][3] = 'C';
    screen_buffer[4][1] = 'a';
    screen_buffer[4][2] = 'b';
    screen_buffer[4][3] = 'c';
    //screen_update_text(
    //    (char*) screen_buffer,
    //    (uint8_t) SCREEN_ROWS,
    //    (uint8_t) SCREEN_COLUMNS,
    //    (unsigned char*) IBM_VGA_8x16,
    //    screen_buff_scroll);


    multicore_launch_core1(uart_read_loop);

    while (true)
    {
        tuh_task();
        screen_update_text(
            (char*) screen_buffer,
            (uint8_t) SCREEN_ROWS,
            (uint8_t) SCREEN_COLUMNS,
            (unsigned char*) IBM_VGA_8x16,
            screen_buff_scroll);

    }
    return 0;
}

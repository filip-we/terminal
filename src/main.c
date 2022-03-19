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

int main (void)
{
    uint32_t led_pin = PICO_DEFAULT_LED_PIN;
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    while (true)
    {
        gpio_put(led_pin, true);
        sleep_ms(500);
        gpio_put(led_pin, false);
        sleep_ms(500);
    }
    return 0;
}


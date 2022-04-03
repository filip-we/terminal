#include <stdio.h>

// TinyUSB imports
#include "bsp/board.h"
#include "tusb.h"

void tuh_hid_mount_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* desc_report, uint16_t desc_len)
{
}

void tuh_hid_unmount_cb(uint8_t dev_addr, uint8_t instance)
{
}

void tuh_hid_report_received_cb(uint8_t dev_addr, uint8_t instance,  uint8_t const* report, uint16_t len)
{
    char buf[32];
    hid_keyboard_report_t const* hid_report;
    hid_report = (hid_keyboard_report_t const*) report;
    for (uint8_t i = 0; i < 6; i++)
    {
        if (hid_report -> keycode[i])
        {
            sprintf(buf, "%b", hid_report -> keycode[i]);
        }
    }
    puts(buf);
}



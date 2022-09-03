/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2021, Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * Modified by filip-we 2022.
 */

#include "bsp/board.h"
#include "tusb.h"

#ifndef usb_keyboard_h
#include "usb_keyboard.h"
#endif

#define MAX_REPORT  4

static uint8_t const keycode2ascii[128][2] =  { HID_KEYCODE_TO_ASCII };

static struct
{
  uint8_t report_count;
  tuh_hid_report_info_t report_info[MAX_REPORT];
}hid_info[CFG_TUH_HID];

static void process_kbd_report(hid_keyboard_report_t const *report);

void hid_app_task(void)
{
    // nothing to do
}


void tuh_hid_mount_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* desc_report, uint16_t desc_len)
{
    printf("HID device address = %d, instance = %d is mounted\r\n", dev_addr, instance);

    kbd_buff_write = 0;
    kbd_buff_read = 0;

    const char* protocol_str[] = { "None", "Keyboard", "Mouse" };
    uint8_t const itf_protocol = tuh_hid_interface_protocol(dev_addr, instance);

    printf("HID Interface Protocol = %s\r\n", protocol_str[itf_protocol]);

    if ( itf_protocol == HID_ITF_PROTOCOL_NONE )
    {
      hid_info[instance].report_count = tuh_hid_parse_report_descriptor(hid_info[instance].report_info, MAX_REPORT, desc_report, desc_len);
      printf("HID has %u reports \r\n", hid_info[instance].report_count);
    }

    if ( !tuh_hid_receive_report(dev_addr, instance) )
    {
      printf("Error: cannot request to receive report\r\n");
    }
}


void tuh_hid_umount_cb(uint8_t dev_addr, uint8_t instance)
{
    printf("HID device address = %d, instance = %d is unmounted\r\n", dev_addr, instance);
}


void tuh_hid_report_received_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* report, uint16_t len)
{
    uint8_t const itf_protocol = tuh_hid_interface_protocol(dev_addr, instance);

    printf("HID receive boot keyboard report\r\n");
    process_kbd_report( (hid_keyboard_report_t const*) report );

    if ( !tuh_hid_receive_report(dev_addr, instance) )
    {
      printf("Error: cannot request to receive report\r\n");
    }
}


static inline bool find_key_in_report(hid_keyboard_report_t const *report, uint8_t keycode)
{
    for(uint8_t i=0; i<6; i++)
    {
      if (report->keycode[i] == keycode)  return true;
    }

    return false;
}


static void process_kbd_report(hid_keyboard_report_t const *report)
{
    static hid_keyboard_report_t prev_report = { 0, 0, {0} }; // previous report to check key released

    //------------- example code ignore control (non-printable) key affects -------------//
    for(uint8_t i=0; i<6; i++)
    {
        if ( report->keycode[i] )
        {
            if ( find_key_in_report(&prev_report, report->keycode[i]) )
            {
                // exist in previous report means the current key is holding
            }else
            {
                // not existed in previous report means the current key is pressed
                bool const is_shift = report->modifier & (KEYBOARD_MODIFIER_LEFTSHIFT | KEYBOARD_MODIFIER_RIGHTSHIFT);
                uint8_t ch = keycode2ascii[report->keycode[i]][is_shift ? 1 : 0];
                putchar(ch);
                if ( ch == '\r' ) putchar('\n'); // added new line for enter key

                fflush(stdout); // flush right away, else nanolib will wait for newline
                kbd_buff[kbd_buff_write] = ch;
                kbd_buff_write++;
            }
        }
        // TODO example skips key released
    }

    prev_report = *report;
}

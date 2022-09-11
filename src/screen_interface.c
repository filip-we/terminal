#include "screen_interface.h"

#include "bsp/board.h"

void fill_display(RGB *color)
{
    screen_write_command(SCREEN_ORIENTATION ? SCREEN_PAGE_ADDR_SET : SCREEN_COLUMN_ADDR_SET);
    screen_write_data(0);
    screen_write_data(0);
    screen_write_data(SCREEN_WIDTH >> 8);
    screen_write_data(SCREEN_WIDTH & 0xFF);

    screen_write_command(SCREEN_ORIENTATION ? SCREEN_COLUMN_ADDR_SET : SCREEN_PAGE_ADDR_SET);
    screen_write_data(0);
    screen_write_data(0);
    screen_write_data(SCREEN_HEIGHT >> 8);
    screen_write_data(SCREEN_HEIGHT & 0xFF);

    screen_write_command(SCREEN_MEMORY_WRITE);
    for (uint32_t y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (uint32_t x = 0; x < SCREEN_WIDTH; x++)
        {
            screen_write_color_data(color);
        }
    }
}


void print_char(unsigned char *font_map, unsigned char char_nr, uint16_t x_pos, uint16_t y_pos)
{
    screen_write_command(SCREEN_COLUMN_ADDR_SET);
    screen_write_data(x_pos >> 8);
    screen_write_data(x_pos & 0xFF);
    screen_write_data((x_pos + 7) >> 8);
    screen_write_data((x_pos + 7) & 0xFF);

    screen_write_command(SCREEN_PAGE_ADDR_SET);
    screen_write_data(y_pos >> 8);
    screen_write_data(y_pos & 0xFF);
    screen_write_data((y_pos + 31) >> 8);
    screen_write_data((y_pos + 31) & 0xFF);

    screen_write_command(SCREEN_MEMORY_WRITE);

    char row;
    for (uint16_t y = 0; y < 16 ; y++)
    {
        row = font_map[char_nr * 16 + y];
        for (uint16_t x = 0; x < 8; x++)
        {
            if (row & 128)
            {
                screen_write_color_data(&fg_color);
                //screen_write_data((fg_color.red << 3) + (fg_color.green >> 5));
                //screen_write_data(((bg_color.green << 5)) + (bg_color.blue & 0x1F));
                //screen_write_data((fg_color.blue >> 3) + ((fg_color.green << 3) & 0xFF));
            }
            else
            {
                screen_write_color_data(&bg_color);
            }
            row = row << 1;
        }
    }
}


void screen_hw_init()
{
    RGB bg_color = {
        .red = 0x00000,
        .green = 0b000000,
        .blue = 0b11111,
    };
    RGB fg_color = {
        .red = 0b11111,
        .green = 0b111111,
        .blue = 0b11111,
    };

    gpio_init(SCREEN_RST);
    gpio_set_dir(SCREEN_RST, GPIO_OUT);
    gpio_put(SCREEN_RST, 1);

    gpio_init(SCREEN_RD);
    gpio_set_dir(SCREEN_RD, GPIO_OUT);
    gpio_put(SCREEN_RD, 1);

    gpio_init(SCREEN_WR);
    gpio_set_dir(SCREEN_WR, GPIO_OUT);
    gpio_put(SCREEN_WR, 1);

    gpio_init(SCREEN_CD);
    gpio_set_dir(SCREEN_CD, GPIO_OUT);
    gpio_put(SCREEN_CD, 1);

    gpio_init(SCREEN_CS);
    gpio_set_dir(SCREEN_CS, GPIO_OUT);
    gpio_put(SCREEN_CS, 1);

    for (int i = SCREEN_DATA; i < SCREEN_DATA + 8; i++)
    {
        gpio_init(i);
        gpio_set_dir(i, GPIO_OUT);
        gpio_put(i, 1);
    }

    gpio_put(SCREEN_CS, 0); // Chip select

    gpio_put(SCREEN_RST, 0);
    sleep_ms(120);
    gpio_put(SCREEN_RST, 1);
    sleep_ms(120);

    screen_write_command(SCREEN_DISPLAY_OFF);
    screen_write_command(SCREEN_SLEEP_OUT);
    screen_write_data(0x00);

    screen_write_command(SCREEN_POWER_CTL_A);
    screen_write_data(0x39);
    screen_write_data(0x2C);
    screen_write_data(0x00);
    screen_write_data(0x34);
    screen_write_data(0x02);

    screen_write_command(SCREEN_POWER_CTL_B);
    screen_write_data(0x00);
    screen_write_data(0x81);
    screen_write_data(0x30);

    screen_write_command(SCREEN_DRIVER_TIMING_A);
    screen_write_data(0x85);
    screen_write_data(0x01);
    screen_write_data(0x79);

    screen_write_command(SCREEN_DRIVER_TIMING_B);
    screen_write_data(0x00);
    screen_write_data(0x00);

    screen_write_command(SCREEN_POWER_ON_SEQUENCE_CTL);
    screen_write_data(0x64);
    screen_write_data(0x03);
    screen_write_data(0x12);
    screen_write_data(0x81);

    screen_write_command(SCREEN_PUMP_RATIO_CTL);
    screen_write_data(0x64);

    screen_write_command(SCREEN_POWER_CTL_1);
    screen_write_data(0x26);

    screen_write_command(SCREEN_POWER_CTL_2);
    screen_write_data(0x11);

    screen_write_command(SCREEN_VCOM_CTL_1);
    screen_write_data(0x35);
    screen_write_data(0x3E);

    screen_write_command(SCREEN_VCOM_CTL_2);
    screen_write_data(0xBE);

    screen_write_command(SCREEN_VCOM_CTL_2);
    screen_write_data(0xBE);

    // RowDir, ColDir, Flip, VertRefrOrd, RGB-order, HoriRefrOrd, 00
    screen_write_command(SCREEN_MEMORY_ACCESS_CTL);
    screen_write_data(0b11011100);

    screen_write_command(SCREEN_FRAME_RATE_CTL);
    screen_write_data(0x00);
    screen_write_data(0x10);

    screen_write_command(SCREEN_DISPLAY_FUNCTION_CTL);
    screen_write_data(0x0A);
    screen_write_data(0xA2);

    screen_write_command(SCREEN_PIXEL_FORMAT_SET);
    screen_write_data(0x55);

    screen_write_command(SCREEN_ENABLE_3G);
    screen_write_data(0x02);

    screen_write_command(SCREEN_GAMMA_SET);
    screen_write_data(0x01);

    screen_write_command(SCREEN_COLUMN_ADDR_SET);
    screen_write_data(0x00);
    screen_write_data(0x00);
    screen_write_data(0x00);
    screen_write_data(0x00);
    screen_write_data(0xEF);

    screen_write_command(SCREEN_PAGE_ADDR_SET);
    screen_write_data(0x00);
    screen_write_data(0x00);
    screen_write_data(0x01);
    screen_write_data(0x3F);

    screen_write_command(SCREEN_DISPLAY_ON);
}


void set_screen_data(char data)
{
    for (int i = 0; i < 8; i++)
    {
        gpio_put((SCREEN_DATA + i), ((data >> i)  & 0x01));
    }
}


void screen_write_command(char cmd)
{
    gpio_put(SCREEN_CD, 0);
    set_screen_data(cmd);
    gpio_put(SCREEN_WR, 0);
    gpio_put(SCREEN_WR, 1);
}


void screen_write_data(char data)
{
    gpio_put(SCREEN_CD, 1);
    set_screen_data(data);
    gpio_put(SCREEN_WR, 0);
    gpio_put(SCREEN_WR, 1);
}


void screen_write_color_data(RGB *color)
{
    screen_write_data((color->red << 3) + (color->green >> 3));
    screen_write_data((color->green << 5) + color->blue);
}

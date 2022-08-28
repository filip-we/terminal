#include "screen_interface.h"

#define SCREEN_PIN_START  6
#define SCREEN_RST  (SCREEN_PIN_START     )
#define SCREEN_RD   (SCREEN_PIN_START + 1 )
#define SCREEN_WR   (SCREEN_PIN_START + 2 )
#define SCREEN_CD   (SCREEN_PIN_START + 3 )
#define SCREEN_CS   (SCREEN_PIN_START + 4 )
#define SCREEN_DATA 14

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_ORIENTATION 1

static void screen_init();
static void set_screen_data(char data);
static void screen_write_command(char cmd);
static void screen_write_data(char data);

static void screen_init()
{
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

static void set_screen_data(char data)
{
    for (int i = 0; i < 8; i++)
    {
        gpio_put((SCREEN_DATA + i), ((data >> i)  & 0x01));
    }
}

static void screen_write_command(char cmd)
{
    gpio_put(SCREEN_CD, 0);
    set_screen_data(cmd);
    gpio_put(SCREEN_WR, 0);
    gpio_put(SCREEN_WR, 1);
}

static void screen_write_data(char data)
{
    gpio_put(SCREEN_CD, 1);
    set_screen_data(data);
    gpio_put(SCREEN_WR, 0);
    gpio_put(SCREEN_WR, 1);
}

#include "parser.h"
#include <stdlib.h>
#include <stdio.h>

#define SET_CURSOR(cursor, r, c) {\
    cursor -> row = r;\
    cursor -> col = c;\
}


char esc_seq_buffer[256];
uint8_t esc_seq_buffer_write;
uint8_t esc_seq_buffer_read;
uint8_t esc_code_depth;
uint8_t code_group;
uint8_t state;

bool parse_csi_code()
{
    if (esc_code_depth > 3)
    {
        return false;
    }
    return true;
}


void parse_byte(char ch,
    struct Cursor * cursor,
    char* screen_buffer,
    uint8_t* scroll)
{
    // printf("starting parse bytes");
    if (state == NORMAL_STATE)
    {
        if (ch == ESC)
            state = ESC_STATE;
        else
            screen_write_char_at_cursor(ch, cursor, screen_buffer, scroll);
            increase_cursor(cursor, scroll);
    }
    else if (state == ESC_STATE)
    {
        if (ch == '[')
        {
            state = CSI_STATE;
            // printf("setting csi-state\n");
        }
        else if (ch == 'E')
        {
            cursor_down(cursor, scroll, 1);
            cursor -> col = 0;
            state = NORMAL_STATE;
        }
    }
    else if (state == CSI_STATE)
    {
        // printf("parsing csi-state for %c\n", ch);
        if (ch == ';' || (ch >= '0' && ch <= '9'))
        {
            // Parse parameter
            esc_seq_buffer[esc_seq_buffer_write] = ch;
            esc_seq_buffer_write ++;
        }
        else if (ch >= '?' && ch <= 'z')
        {
            // We got a complete CSI-code
            call_csi(ch, cursor, screen_buffer, scroll);
            state = NORMAL_STATE;
        }
        else
        {
            state = NORMAL_STATE;
        }
    }
    else
        // Other states go here...
        state = NORMAL_STATE;
    printf("buf-read and write is %d, %d\n", esc_seq_buffer_read, esc_seq_buffer_write);
}


void call_csi(char ch,
    struct Cursor * cursor,
    char* screen_buffer,
    uint8_t* scroll)
{
    uint8_t i = esc_seq_buffer_read;
    int p0;
    int p1;
    //uint8_t p = 0;
    //uint8_t params[2] = {0};
    //char c;
    printf("call_csi with char %c\n", ch);
    if (esc_seq_buffer_write - esc_seq_buffer_read >1)
    {
        while (true)
        {
            if (esc_seq_buffer[i] == ';')
                break;
            else if (esc_seq_buffer[i] == ch)
                break;
            if (i > 100)
            {
                printf("not good, %d\n", esc_seq_buffer_read);
                return;
            }
            i ++;
        }
        p0 = atoi(esc_seq_buffer + esc_seq_buffer_read);
        p1 = atoi(esc_seq_buffer + i + 1);
        esc_seq_buffer_read = esc_seq_buffer_write;
    }
    else
    {
        printf("else %c\n", ch);
        p0 = 0;
        p1 = 0;
    }

    // printf("got params %d, %d\n", p0, p1);

    if (ch = 'A')
        cursor_up(cursor, scroll, p0);
    else if (ch = 'B')
        cursor_down(cursor, scroll, p0);
    else if (ch = 'C')
        cursor_right(cursor, scroll, p0);
    else if (ch = 'D')
        cursor_left(cursor, scroll, p0);
    else if (ch == 'H' || ch == 'f')
    {
        // printf("Parsing ^[p;pH with p being %d, %d\n", p0, p1);
        SET_CURSOR(cursor, p0, p1);
    }
    else if (ch == 'J')
    {
        printf("char is J, p is %d\n", p0);
        clear_screen(cursor, p0);
    }
}


void parse_byte_internally(char ch,
    struct Cursor * cursor,
    char* screen_buffer,
    uint8_t* scroll)
{
    if (ch == LF) // Note that VT100 does not handle this characters normally I believe
        cursor -> row ++;
    else if (ch == CR)
        cursor -> col = 0;
    else if (ch == BS || ch == BSPC)
    {
        if (cursor -> col == 0)
        {
            cursor -> row --;
            cursor -> col = SCREEN_COLUMNS - 1;
        }
        else
            cursor -> col --;
        screen_write_char_at_cursor(0x00, cursor, screen_buffer, scroll);
    }
    else
    {
        if (ch <= US)
        {
            //screen_write_char_at_cursor('!');
        }
        screen_write_char_at_cursor(ch, cursor, screen_buffer, scroll);
        increase_cursor(cursor, scroll);
    }
}

void parser_init()
{
    esc_seq_buffer_write = 0;
    esc_seq_buffer_read = 0;
    esc_code_depth = 0;
    code_group = CODE_GROUP_NORMAL;
    state = NORMAL_STATE;
}

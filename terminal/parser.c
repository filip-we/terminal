#include "parser.h"
#include <stdlib.h>
// #include <stdio.h>


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
            cursor -> row ++;
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
}


void call_csi(char ch,
    struct Cursor * cursor,
    char* screen_buffer,
    uint8_t* scroll)
{
    uint8_t i = esc_seq_buffer_read;

    //uint8_t p = 0;
    //uint8_t params[2] = {0};
    //char c;
    // printf("call_csi\n");
    while (true)
    {
        if (esc_seq_buffer[i] == ';')
        {
            break;
        }
        if (i > 100)
            return;
        i ++;
    }
    int p0 = atoi(esc_seq_buffer + esc_seq_buffer_read);
    int p1 = atoi(esc_seq_buffer + i + 1);
    // printf("got params %d, %d\n", p0, p1);

    if (ch == 'H')
    {
        // printf("Parsing ^[p;pH with p being %d, %d\n", p0, p1);
        cursor -> row = p0;
        cursor -> col = p1;
        // printf("done settings curosr\n");
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

#include "parser.h"

#include "screen.h"

char esc_seq_buffer[256];
uint8_t esc_seq_buffer_write;
uint8_t esc_seq_buffer_read;


void parse_byte(char ch)
{
    //if (esc_seq_buffer_write != esc_seq_buffer_read)
    //{
    //    esc_seq_buffer[esc_seq_buffer_write] = ch;
    //    esc_seq_buffer_write ++;
    //}
    if (ch == BSPC)
    {
        cursor.col --;
        if (cursor.col == -1)
        {
            cursor.col = SCREEN_ROWS;
            cursor.row --;
        }
        screen_write_char(' ', cursor.row, cursor.col);
    }
    else if (ch == CR)
    {
        cursor.row ++;
        cursor.col = 0;
    }
    else if (ch == ESC)
    {
        esc_seq_buffer[esc_seq_buffer_write] = ch;
        esc_seq_buffer_write ++;
    }
    else
    {
        if (ch <= US)
        {
            screen_write_char_at_cursor('!');
        }
        screen_write_char_at_cursor(ch);
    }


    //if (esc_seq_buffer_write - esc_seq_buffer_read == 4)
    //{
    //    esc_seq_buffer_write = 0;
    //    esc_seq_buffer_read = 0;
    //}
}

void parser_init()
{
    esc_seq_buffer_write = 0;
    esc_seq_buffer_read = 0;
}

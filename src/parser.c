#include "parser.h"

#include "screen.h"

char esc_seq_buffer[256];
uint8_t esc_seq_buffer_write;
uint8_t esc_seq_buffer_read;
uint8_t escape_code_depth;

bool parse_escape_code()
{
    return false;
}


void parse_byte(char ch)
{
    if (escape_code_depth > 0)
    {
        esc_seq_buffer[esc_seq_buffer_write] = ch;
        esc_seq_buffer_write ++;
        escape_code_depth ++;
        if (parse_escape_code(ch))
        {
        }
        else
        {
            escape_code_depth = 0;
        }
    }
    else if (ch == ESC)
    {
        escape_code_depth = 1;
    }
    else if (ch == BSPC)
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
    escape_code_depth = 0;
}

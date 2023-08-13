#include "parser.h"

#include "screen.h"

char esc_seq_buffer[256];
uint8_t esc_seq_buffer_write;
uint8_t esc_seq_buffer_read;
uint8_t esc_code_depth;
uint8_t code_group;

bool parse_csi_code()
{
    if (esc_code_depth > 3)
    {
        return false;
    }
    return true;
}


void parse_byte(char ch)
{
    if (esc_code_depth == 1)
    {
        if (ch == '[')
        {
            esc_code_depth ++;
            esc_seq_buffer[esc_seq_buffer_write] = ch;
            esc_seq_buffer_write ++;
        }
        else
        {
            esc_code_depth = 0;
            screen_write_char_at_cursor(ch);
        }
    }
    else if (esc_code_depth == 2)
    {
        if (ch == '#' || ch == '(' || ch == ')' || ch == '[' || ch == '5' || ch == '6')
        {
            esc_code_depth ++;
            esc_seq_buffer[esc_seq_buffer_write] = ch;
            esc_seq_buffer_write ++;
        }
        else if (ch == '7')
        {
            // Save cursor.
            esc_code_depth = 0;
        }
        else if (ch == '8')
        {
            // Restore cursor.
            esc_code_depth = 0;
        }
        else if (ch == '=')
        {
            // Alternate keypad mode
            esc_code_depth = 0;
        }
        else if (ch == '>')
        {
            // Numeric keypad mode
            esc_code_depth = 0;
        }
        else if (ch == 'D' || ch == 'M')
        {
            // Move/ scroll window up one line.
            esc_code_depth = 0;
        }
        else if (ch == 'E')
        {
            // Move to next line.
            esc_code_depth = 0;
        }
        else if (ch == 'H')
        {
            // Set a tab at the current column.
            esc_code_depth = 0;
        }
        else if (ch == 'N')
        {
            // Set single shift 2.
            esc_code_depth = 0;
        }
        else if (ch == 'O')
        {
            // Set single shift 3.
            esc_code_depth = 0;
        }
        else if (ch == 'c')
        {
            screen_init();
            esc_code_depth = 0;
        }
        else
        {
            screen_write_char_at_cursor(ch);
            esc_code_depth = 0;
        }
    }
    else if (esc_code_depth == 3)
    {
        if (ch == '#') {
            // Screen related things. Only this char.
            esc_code_depth = 0;
        }
        else if (ch == '(' || ch == ')')
        {
            // Font related things. Only this char.
            esc_code_depth = 0;
        }
        else if (ch == '[')
        {
            if (!parse_csi_code())
            {
                esc_code_depth = 0;
            }
        }
        else
        {
            screen_write_char_at_cursor(ch);
            esc_code_depth = 0;
        }
    }
    else
    {
        if (ch == ESC)
        {
            esc_code_depth = 1;
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
        else
        {
            if (ch <= US)
            {
                screen_write_char_at_cursor('!');
            }
            screen_write_char_at_cursor(ch);
        }
    }
}

void parser_init()
{
    esc_seq_buffer_write = 0;
    esc_seq_buffer_read = 0;
    esc_code_depth = 0;
    code_group = CODE_GROUP_NORMAL;
}

#include "parser.h"


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


void parse_byte(char ch,
    struct Cursor * cursor,
    char* screen_buffer,
    uint8_t* scroll)
{
    //*(screen_buffer + 40) = '*';
    //*(screen_buffer + 41 + (*cursor).col) = '!';
    //(*cursor).col ++;
    //*(screen_buffer + 42 + (*cursor).col) = '2';


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
            //screen_write_char_at_cursor(ch);
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
        else if (ch == 'D')
        {
            advance_scrolling();
            esc_code_depth = 0;
        }
        else if (ch == 'M')
        {
            scroll --;
            esc_code_depth = 0;
        }
        else if (ch == 'E')
        {
            // Move to begining of next line.
            cursor -> row ++;
            cursor -> col = 0;
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
            //screen_init();
            esc_code_depth = 0;
        }
        else
        {
            //screen_write_char_at_cursor(ch);
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
            //screen_write_char_at_cursor(ch);
            esc_code_depth = 0;
        }
    }
    else
    {
        if (ch == ESC)
        {
            esc_code_depth = 1;
        }
        else if (ch == LF) // Note that VT100 does not handle this characters normally I believe
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
}

void parser_init()
{
    esc_seq_buffer_write = 0;
    esc_seq_buffer_read = 0;
    esc_code_depth = 0;
    code_group = CODE_GROUP_NORMAL;
}

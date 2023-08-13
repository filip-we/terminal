#ifndef parser_h
#define parser_h

#define BSPC 127

#include <stdint.h>

void parse_byte(
    char ch,
    uint8_t* cursor_row,
    uint8_t* cursor_col,
    char* screen_buffer);
void parser_init();

enum control_codes
{
    NUL,
    SOH,
    STX,
    ETX,
    EOT,
    ENQ,
    ACK,
    BEL,
    BS,
    HT,
    LF,
    VT,
    FF,
    CR,
    SO,
    SI,
    DLE,
    DC1,
    DC2,
    DC3,
    DC4,
    NAK,
    SYN,
    ETB,
    CAN,
    EM,
    SUB,
    ESC,
    FS,
    GS,
    RS,
    US,
};

enum states
{
    CODE_GROUP_NORMAL,
    CODE_GROUP_HASH,
    CODE_GROUP_G0,
    CODE_GROUP_G1,
    CODE_GROUP_CSI,
};

#endif

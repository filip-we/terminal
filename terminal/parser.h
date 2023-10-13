#ifndef parser_h
#define parser_h

#define BSPC 127

#include <stdint.h>
#include "screen.h"

void parse_byte(
    char ch,
    struct Cursor* cursor,
    char* screen_buffer,
    uint8_t* screen_buff_scroll);
void call_csi(
    char ch,
    struct Cursor* cursor,
    char* screen_buffer,
    uint8_t* screen_buff_scroll);
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

enum parser_states
{
    NORMAL_STATE, ESC_STATE, CSI_STATE, HASH_STATE, G0SET, G1SET,
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

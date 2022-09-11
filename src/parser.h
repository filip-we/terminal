#ifndef parser_h
#define parser_h

#define BSPC 127

#include "pico/stdlib.h"

void parse_byte(char ch);
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


#endif

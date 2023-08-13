/*
 *  Escape sequences for VT100.
 *
 */
cmd_dhtop               = "^[#3"             // Double-height letters, top half
cmd_dhbot               = "^[#4"             // Double-height letters, bottom half
cmd_swsh                = "^[#5"             // Single width, single height letters
cmd_dwsh                = "^[#6"             // Double width, single height letters
cmd_align               = "^[#8"             // Screen alignment display

cmd_setukg0             = "^[(A"             // Set  United Kingdom G0 character set
cmd_setusg0             = "^[(B"             // Set  United States G0 character set
cmd_setspecg0           = "^[(0"             // Set  0 special chars. & line set
cmd_setaltg0            = "^[(1"             // Set  0 alternate character  OM
cmd_setaltspecg0        = "^[(2"             // Set  0 alt char  OM and spec. graphics
cmd_setukg1             = "^[)A"             // Set  United Kingdom G1 character set
cmd_setusg1             = "^[)B"             // Set  United States G1 character set
cmd_setspecg1           = "^[)0"             // Set  1 special chars. & line set
cmd_setaltg1            = "^[)1"             // Set  1 alternate character  OM
cmd_setaltspecg1        = "^[)2"             // Set  1 alt char  OM and spec. graphics

cmd_devstat             = "^[5n"             // Device status report
cmd_getcursor           = "^[6n"             // Get cursor position
cmd_savecursor          = "^[7"              // Save cursor position and attributes
cmd_restorecursor       = "^[8"              // Restore cursor position and attributes

cmd_altkeypad           = "^[="              // Set alternate keypad mode
cmd_numkeypad           = "^[>"              // Set numeric keypad mode

cmd_index               = "^[D"              // Move/scroll window up one line
cmd_nextline            = "^[E"              // Move to next line
cmd_tabset              = "^[H"              // Set a tab at the current column
cmd_revindex            = "^[M"              // Move/scroll window down one line
cmd_setss2              = "^[N"              // Set single shift 2
cmd_setss3              = "^[O"              // Set single shift 3

cmd_reset               = "^[c"              // Reset terminal to initial state


cmd_modesoff            = "^[[0m"            // Turn off character attributes
cmd_bold                = "^[[1m"            // Turn bold mode on
cmd_lowint              = "^[[2m"            // Turn low intensity mode on
cmd_underline           = "^[[4m"            // Turn underline mode on
cmd_blink               = "^[[5m"            // Turn blinking mode on
cmd_reverse             = "^[[7m"            // Turn reverse video on
cmd_invisible           = "^[[8m"            // Turn invisible text mode on

cmd_setnl               = "^[[20h"           // Set new line mode
cmd_setlf               = "^[[20l"           // Set line feed mode

cmd_setappl             = "^[[?1h"           // Set cursor key to application
cmd_setcol              = "^[[?3h"           // Set number of columns to 132
cmd_setsmooth           = "^[[?4h"           // Set smooth scrolling
cmd_setrevscrn          = "^[[?5h"           // Set reverse video on screen
cmd_setorgrel           = "^[[?6h"           // Set origin to relative
cmd_setwrap             = "^[[?7h"           // Set auto-wrap mode
cmd_setrep              = "^[[?8h"           // Set auto-repeat mode
cmd_setinter            = "^[[?9h"           // Set interlacing mode

cmd_setcursor           = "^[[?1l"           // Set cursor key to cursor
cmd_setvt52             = "^[[?2l"           // Set VT52 (versus ANSI)
cmd_resetcol            = "^[[?3l"           // Set number of columns to 80
cmd_setjump             = "^[[?4l"           // Set jump scrolling
cmd_setnormscrn         = "^[[?5l"           // Set normal video on screen
cmd_setorgabs           = "^[[?6l"           // Set origin to absolute
cmd_resetwrap           = "^[[?7l"           // Reset auto-wrap mode
cmd_resetrep            = "^[[?8l"           // Reset auto-repeat mode
cmd_resetinter          = "^[[?9l"           // Reset interlacing mode

cmd_modesoff            = "^[[m"             // Turn off character attributes
cmd_setwin              = "^[[_;_r"         // Set top and bottom line#s of a window

cmd_cursorup_n          = "^[[_A"            // Move cursor up n lines
cmd_cursordn_n          = "^[[_B"            // Move cursor down n lines
cmd_cursorrt_n          = "^[[_C"            // Move cursor right n lines
cmd_cursorlf_n          = "^[[_D"            // Move cursor left n lines
cmd_cursorhome_1        = "^[[H"             // Move cursor to upper left corner
cmd_cursorhome_2        = "^[[;H"            // Move cursor to upper left corner
cmd_cursorpos_v_h       = "^[[_;_H"          // Move cursor to screen location v,h
cmd_hvhome_1            = "^[[f"             // Move cursor to upper left corner
cmd_hvhome_2            = "^[[;f"            // Move cursor to upper left corner
cmd_hvpos_v_h           = "^[[_;_f"          // Move cursor to screen location v,h
cmd_tabclr              = "^[[g"             // Clear a tab at the current column
cmd_tabclr              = "^[[0g"            // Clear a tab at the current column
cmd_tabclrall           = "^[[3g"            // Clear all tabs

cmd_cleareol            = "^[[K"             // Clear line from cursor right
cmd_cleareol            = "^[[0K"            // Clear line from cursor right
cmd_clearbol            = "^[[1K"            // Clear line from cursor left
cmd_clearline           = "^[[2K"            // Clear entire line

cmd_cleareos            = "^[[J"             // Clear screen from cursor down
cmd_cleareos            = "^[[0J"            // Clear screen from cursor down
cmd_clearbos            = "^[[1J"            // Clear screen from cursor up
cmd_clearscreen         = "^[[2J"            // Clear entire screen

cmd_ident               = "^[[c"             // Identify what terminal type
cmd_ident_other         = "^[[0c"            // Identify what terminal type (another)

cmd_testpu              = "^[[2;1y"          // Confidence power up test
cmd_testlb              = "^[[2;2y"          // Confidence loopback test
cmd_testpurep           = "^[[2;9y"          // Repeat power up test
cmd_testlbrep           = "^[[2;10y"         // Repeat loopback test

cmd_ledsoff             = "^[[0q"            // Turn off all four leds
cmd_led1                = "^[[1q"            // Turn on LED #1
cmd_led2                = "^[[2q"            // Turn on LED #2
cmd_led3                = "^[[3q"            // Turn on LED #3
cmd_led4                = "^[[4q"            // Turn on LED #4

// Responses
cmd_termok              = "^[0n"             // Response: terminal is OK
cmd_termnok             = "^[3n"             // Response: terminal is not OK
cmd_gettype             = "^[[?1;_0c"        // Response: terminal type code n
cmd_cursorpos           = "^[_;_R"           // Response: cursor is at v,h

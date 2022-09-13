/*
 *  Escape codes for VT100. All these start with "^[".
 *
 */

esc_setnl               = "[20h "         // Set new line mode
esc_setappl             = "[?1h "         // Set cursor key to application
esc_setcol              = "[?3h "         // Set number of columns to 132
esc_setsmooth           = "[?4h "         // Set smooth scrolling
esc_setrevscrn          = "[?5h "         // Set reverse video on screen
esc_setorgrel           = "[?6h "         // Set origin to relative
esc_setwrap             = "[?7h "         // Set auto-wrap mode
esc_setrep              = "[?8h "         // Set auto-repeat mode
esc_setinter            = "[?9h "         // Set interlacing mode

esc_setlf               = "[20l   "       // Set line feed mode
esc_setcursor           = "[?1l   "       // Set cursor key to cursor
esc_setvt52             = "[?2l   "       // Set VT52 (versus ANSI)
esc_resetcol            = "[?3l   "       // Set number of columns to 80
esc_setjump             = "[?4l   "       // Set jump scrolling
esc_setnormscrn         = "[?5l   "       // Set normal video on screen
esc_setorgabs           = "[?6l   "       // Set origin to absolute
esc_resetwrap           = "[?7l   "       // Reset auto-wrap mode
esc_resetrep            = "[?8l   "       // Reset auto-repeat mode
esc_resetinter          = "[?9l   "       // Reset interlacing mode

esc_altkeypad           = "=      "       // Set alternate keypad mode
esc_numkeypad           = ">      "       // Set numeric keypad mode

esc_setukg0             = "(A     "       // Set  United Kingdom G0 character set
esc_setukg1             = ")A     "       // Set  United Kingdom G1 character set
esc_setusg0             = "(B     "       // Set  United States G0 character set
esc_setusg1             = ")B     "       // Set  United States G1 character set
esc_setspecg0           = "(0     "       // Set  0 special chars. & line set
esc_setspecg1           = ")0     "       // Set  1 special chars. & line set
esc_setaltg0            = "(1     "       // Set  0 alternate character  OM
esc_setaltg1            = ")1     "       // Set  1 alternate character  OM
esc_setaltspecg0        = "(2     "       // Set  0 alt char  OM and spec. graphics
esc_setaltspecg1        = ")2     "       // Set  1 alt char  OM and spec. graphics

esc_setss2              = "N      "       // Set single shift 2
esc_setss3              = "O      "       // Set single shift 3

esc_modesoff            = "[m     "       // Turn off character attributes
esc_modesoff            = "[0m    "       // Turn off character attributes
esc_bold                = "[1m    "       // Turn bold mode on
esc_lowint              = "[2m    "       // Turn low intensity mode on
esc_underline           = "[4m    "       // Turn underline mode on
esc_blink               = "[5m    "       // Turn blinking mode on
esc_reverse             = "[7m    "       // Turn reverse video on
esc_invisible           = "[8m    "       // Turn invisible text mode on

esc_setwin              = "[-;-r  "       // Set top and bottom line#s of a window

esc_cursorup(n)         = "[-A    "       // Move cursor up n lines
esc_cursordn(n)         = "[-B    "       // Move cursor down n lines
esc_cursorrt(n)         = "[-C    "       // Move cursor right n lines
esc_cursorlf(n)         = "[-D    "       // Move cursor left n lines
esc_cursorhome          = "[H     "       // Move cursor to upper left corner
esc_cursorhome          = "[;H    "       // Move cursor to upper left corner
esc_cursorpos(v,h)      = "[-;-H  "       // Move cursor to screen location v,h
esc_hvhome              = "[f     "       // Move cursor to upper left corner
esc_hvhome              = "[;f    "       // Move cursor to upper left corner
esc_hvpos(v,h)          = "[-;-f  "       // Move cursor to screen location v,h
esc_index               = "D      "       // Move/scroll window up one line
esc_revindex            = "M      "       // Move/scroll window down one line
esc_nextline            = "E      "       // Move to next line
esc_savecursor          = "7      "       // Save cursor position and attributes
esc_restorecursor       = "8      "       // Restore cursor position and attributes

esc_tabset              = "H      "       // Set a tab at the current column
esc_tabclr              = "[g     "       // Clear a tab at the current column
esc_tabclr              = "[0g    "       // Clear a tab at the current column
esc_tabclrall           = "[3g    "       // Clear all tabs

esc_dhtop               = "#3     "       // Double-height letters, top half
esc_dhbot               = "#4     "       // Double-height letters, bottom half
esc_swsh                = "#5     "       // Single width, single height letters
esc_dwsh                = "#6     "       // Double width, single height letters

esc_cleareol            = "[K     "       // Clear line from cursor right
esc_cleareol            = "[0K    "       // Clear line from cursor right
esc_clearbol            = "[1K    "       // Clear line from cursor left
esc_clearline           = "[2K    "       // Clear entire line

esc_cleareos            = "[J     "       // Clear screen from cursor down
esc_cleareos            = "[0J    "       // Clear screen from cursor down
esc_clearbos            = "[1J    "       // Clear screen from cursor up
esc_clearscreen         = "[2J    "       // Clear entire screen

esc_devstat             = "5n     "       // Device status report
esc_termok              = "0n     "       // Response: terminal is OK
esc_termnok             = "3n     "       // Response: terminal is not OK

esc_getcursor           = "6n     "       // Get cursor position
esc_cursorpos           = "-;-R   "       // Response: cursor is at v,h

esc_ident               = "[c     "       // Identify what terminal type
esc_ident               = "[0c    "       // Identify what terminal type (another)
esc_gettype             = "[?1;-0c"       // Response: terminal type code n

esc_reset               = "c      "       // Reset terminal to initial state

esc_align               = "#8     "       // Screen alignment display
esc_testpu              = "[2;1y  "       // Confidence power up test
esc_testlb              = "[2;2y  "       // Confidence loopback test
esc_testpurep           = "[2;9y  "       // Repeat power up test
esc_testlbrep           = "[2;10y "       // Repeat loopback test

esc_ledsoff             = "[0q    "       // Turn off all four leds
esc_led1                = "[1q    "       // Turn on LED #1
esc_led2                = "[2q    "       // Turn on LED #2
esc_led3                = "[3q    "       // Turn on LED #3
esc_led4                = "[4q    "       // Turn on LED #4

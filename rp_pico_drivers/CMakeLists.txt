cmake_minimum_required(VERSION 3.13)

add_library(terminal_src
    screen_interface.c
    screen.c
    usb_keyboard.c
    parser.c)

target_include_directories(terminal_src PUBLIC .
    ${CMAKE_CURRENT_LIST_DIR}/../lib/romfont/font-headers/)

target_link_libraries(terminal_src PUBLIC
    pico_stdlib
    pico_multicore
    tinyusb_host
    tinyusb_board
)

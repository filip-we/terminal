cmake_minimum_required(VERSION 3.13)

add_library(rp_pico_drivers
    screen_interface.c
    screen.c
    usb_keyboard.c)

target_include_directories(rp_pico_drivers PUBLIC .
    ${CMAKE_CURRENT_LIST_DIR}/../lib/romfont/font-headers/)

target_link_libraries(rp_pico_drivers PUBLIC
    pico_stdlib
    pico_multicore
    tinyusb_host
    tinyusb_board
)

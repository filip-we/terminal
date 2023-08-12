cmake_minimum_required(VERSION 3.13)

set(PICO_PLATFORM rp2040)
set(FAMILY rp2040)
set(BOARD pico_sdk)
set(TINYUSB_FAMILY_PROJECT_NAME_PREFIX "tinyusb_host_")

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_library(terminal
    screen_interface.c
    screen.c
    usb_keyboard.c
    parser.c)


target_link_libraries(terminal PUBLIC .)

pico_sdk_init()
pico_enable_stdio_usb(terminal 0)
pico_enable_stdio_uart(terminal 0)
pico_add_extra_outputs(terminal)

target_include_directories(terminal PUBLIC .
    ${CMAKE_CURRENT_LIST_DIR}/../lib/romfont/font-headers/)

target_link_libraries(terminal PUBLIC
    pico_stdlib
    pico_multicore
    tinyusb_host
    tinyusb_board
)

#file(GLOB FILES *.c)
#
#target_sources(terminal PUBLIC
##        ${FILES}
#        ${CMAKE_CURRENT_LIST_DIR}/screen_interface.c
#        ${CMAKE_CURRENT_LIST_DIR}/screen.c
#        ${CMAKE_CURRENT_LIST_DIR}/usb_keyboard.c
#        ${CMAKE_CURRENT_LIST_DIR}/parser.c
#        )
#
## For TinyUSB to recoginze tusb_config.h
#target_include_directories(terminal PUBLIC
#        ${CMAKE_CURRENT_LIST_DIR}
#        ${CMAKE_CURRENT_LIST_DIR}/../lib/romfont/font-headers/
#        )
#
#target_link_libraries(terminal PUBLIC
#    pico_stdlib
#    pico_multicore
#    tinyusb_host
#    tinyusb_board
#)
#

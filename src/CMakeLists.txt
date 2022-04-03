cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

set(PICO_PLATFORM rp2040)
set(FAMILY rp2040)
set(BOARD pico_sdk)
set(TINYUSB_FAMILY_PROJECT_NAME_PREFIX "tinyusb_host_") # Needed?
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(terminal C CXX ASM)

add_executable(terminal)

target_sources(terminal PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/main.c
        ${CMAKE_CURRENT_LIST_DIR}/usb_keyboard.c
        )

target_include_directories(terminal PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/../lib/romfont/font-headers/
        )

target_link_libraries(terminal PUBLIC
    pico_stdlib
    tinyusb_host
    tinyusb_board
    )

pico_sdk_init()
pico_add_extra_outputs(terminal)
pico_enable_stdio_uart(terminal 1)
pico_enable_stdio_usb(terminal 0)

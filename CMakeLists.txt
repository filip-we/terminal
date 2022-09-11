cmake_minimum_required(VERSION 3.13)

set(PICO_PLATFORM rp2040)
set(FAMILY rp2040)
set(BOARD pico_sdk)
set(TINYUSB_FAMILY_PROJECT_NAME_PREFIX "tinyusb_host_")

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(terminal C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(terminal
  src/main.c
)

pico_sdk_init()

pico_enable_stdio_usb(terminal 0)
pico_enable_stdio_uart(terminal 0)
pico_add_extra_outputs(terminal)

add_subdirectory(src)

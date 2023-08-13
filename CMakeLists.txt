cmake_minimum_required(VERSION 3.13)

set(PICO_PLATFORM rp2040)
set(FAMILY rp2040)
set(BOARD pico_sdk)
set(TINYUSB_FAMILY_PROJECT_NAME_PREFIX "tinyusb_host_")

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(terminal C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_subdirectory(rp_pico_drivers)
add_subdirectory(terminal)
add_subdirectory(rp_pico_program)
#add_subdirectory(tests)

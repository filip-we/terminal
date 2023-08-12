cmake_minimum_required(VERSION 3.13)

set(PICO_PLATFORM rp2040)
set(FAMILY rp2040)
set(BOARD pico_sdk)
set(TINYUSB_FAMILY_PROJECT_NAME_PREFIX "tinyusb_host_")

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(rp_pico_program
  main.c
)

pico_sdk_init()

target_link_libraries(rp_pico_program PRIVATE src)

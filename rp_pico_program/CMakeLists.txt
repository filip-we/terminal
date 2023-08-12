cmake_minimum_required(VERSION 3.13)

add_executable(rp_pico_program
  main.c
)

target_link_libraries(rp_pico_program PRIVATE terminal_src
    pico_stdlib
    pico_multicore
    tinyusb_host
    tinyusb_board
)

pico_enable_stdio_usb(rp_pico_program 0)
pico_enable_stdio_uart(rp_pico_program 0)
pico_add_extra_outputs(rp_pico_program)

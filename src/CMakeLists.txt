add_executable(terminal
  main.c
)

pico_enable_stdio_usb(terminal 0)
pico_enable_stdio_uart(terminal 0)
pico_add_extra_outputs(terminal)

file(GLOB FILES *.c)

target_sources(terminal PUBLIC
#        ${FILES}
        ${CMAKE_CURRENT_LIST_DIR}/screen_interface.c
        ${CMAKE_CURRENT_LIST_DIR}/screen.c
        ${CMAKE_CURRENT_LIST_DIR}/usb_keyboard.c
        )

# For TinyUSB to recoginze tusb_config.h
target_include_directories(terminal PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/../lib/romfont/font-headers/
        )

target_link_libraries(terminal PUBLIC
    pico_stdlib
    tinyusb_host
    tinyusb_board
)


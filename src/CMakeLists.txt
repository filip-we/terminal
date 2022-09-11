
file(GLOB FILES *.c)

target_sources(terminal PUBLIC
#        ${FILES}
        ${CMAKE_CURRENT_LIST_DIR}/screen_interface.c
        ${CMAKE_CURRENT_LIST_DIR}/screen.c
        ${CMAKE_CURRENT_LIST_DIR}/usb_keyboard.c
        ${CMAKE_CURRENT_LIST_DIR}/parser.c
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


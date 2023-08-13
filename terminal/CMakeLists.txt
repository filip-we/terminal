cmake_minimum_required(VERSION 3.13)

add_library(terminal
    parser.c)

target_include_directories(terminal PUBLIC .)

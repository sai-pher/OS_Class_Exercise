cmake_minimum_required(VERSION 3.14)
project(Terminal_Project C)

set(CMAKE_C_STANDARD 11)

add_executable(Terminal terminal.c terminal.h)
add_executable(Terminal_test main.c terminal.h)
add_executable(test test.c)
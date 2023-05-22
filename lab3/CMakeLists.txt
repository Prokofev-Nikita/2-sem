cmake_minimum_required(VERSION 3.24)
project(untitled1 C)

set(CMAKE_C_STANDARD 23)

add_executable(untitled1 main.c bmp.cpp bmp.c)
target_link_libraries(untitled1 m)
cmake_minimum_required(VERSION 3.9)
project(sonar_scanner_laba1)
project(sonar_scanner_laba2)
project(sonar_scanner_laba3)
project(sonar_scanner_laba4)
set(CMAKE_C_STANDARD 99)


add_executable(sonar_scanner_laba1 lab1/main.c lab1/func.c)
add_executable(sonar_scanner_laba2 lab2/main.c)
add_executable(sonar_scanner_laba3 lab3/main.c lab3/bmp.c)
add_executable(sonar_scanner_laba4 lab4/main.c)
target_link_libraries(sonar_scanner_laba2 m)

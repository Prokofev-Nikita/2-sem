cmake_minimum_required(VERSION 3.9)
project(sonar_scanner_example)
project(sonar_scanner_example1)
project(sonar_scanner_example2)
project(sonar_scanner_example3)
set(CMAKE_C_STANDARD 99)


add_executable(sonar_scanner_example lab1/main.c lab1/func.c)
add_executable(sonar_scanner_example1 lab2/main.c)
add_executable(sonar_scanner_example2 lab3/main.c lab3/bmp.c)
add_executable(sonar_scanner_example1 lab4/main.c)
target_link_libraries(sonar_scanner_example1 m)

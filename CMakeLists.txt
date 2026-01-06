cmake_minimum_required(VERSION 3.20)
project(chip8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)

add_executable(chip8 
    src/main.cpp
    src/Chip8.cpp
    src/Display.cpp
    src/Keypad.cpp
)

target_link_libraries(chip8 PRIVATE SDL3::SDL3-shared)
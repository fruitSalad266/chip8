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

add_executable(test_display
    test/test_display.cpp
    src/Display.cpp
)

add_executable(test_keypad
    test/test_keypad.cpp
    src/Display.cpp
    src/Keypad.cpp
)

target_link_libraries(chip8 PRIVATE SDL3::SDL3-shared)
target_link_libraries(test_display PRIVATE SDL3::SDL3-shared)
target_link_libraries(test_keypad PRIVATE SDL3::SDL3-shared)

#imgui - debugger
include(FetchContent)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.6
)
FetchContent_MakeAvailable(imgui)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)

add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)

target_include_directories(imgui PUBLIC 
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(imgui PUBLIC SDL3::SDL3-shared)

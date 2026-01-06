#include "Chip8.hpp"
#include "Display.hpp"
#include "Keypad.hpp"

#include <chrono>
#include <thread>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: chip8 <ROM file>\n";
        return 1;
    }

    Chip8 chip8;
    Display display;
    Keypad keypad;

    if (!display.init()) {
        std::cerr << "No Display Initialized :(\n";
        return 1;
    }

    return 0;
}
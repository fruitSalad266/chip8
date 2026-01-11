#include "Chip8.hpp"
#include "Display.hpp"
#include "Keypad.hpp"

#include <chrono>
#include <thread>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: chip8 <ROM file> [-legacy]\n";
        return 1;
    }

    Chip8 chip8;
    Display display;
    Keypad keypad;
    
    if (argc > 2 && std::string(argv[2]) == "-legacy") {
        chip8.legacyShift = true;
    }

    if (!display.init()) {
        std::cerr << "No Display Initialized :(\n";
        return 1;
    }

    chip8.loadROM(argv[1]);

    const auto IPS = 700; //instructs/sec
    const auto timerInterval = std::chrono::microseconds(1000000 / IPS);

    while (!keypad.shouldQuit()) {
        auto cycleStart = std::chrono::high_resolution_clock::now();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            keypad.processInput(event, chip8.keypad);
        }

        chip8.cycle();

        if (chip8.drawFlag) {
            display.render(chip8.display);
            chip8.drawFlag = false;
        }
        auto cycleEnd = std::chrono::high_resolution_clock::now();
        auto elapsed = cycleEnd - cycleStart;
        if (elapsed < timerInterval) {
            std::this_thread::sleep_for(timerInterval - elapsed);
        }

    }
    return 0;
}
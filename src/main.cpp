#include "Chip8.hpp"
#include "Display.hpp"
#include "Keypad.hpp"
#include "Debugger.hpp"

#include <chrono>
#include <thread>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: chip8 <ROM file> [-legacy] [-debug]\n";
        return 1;
    }

    Chip8 chip8;
    Display display;
    Keypad keypad;
    Debugger debugger;

    bool debugMode = false;

    for (int i = 2; i < argc; i++) {
        if (std::string(argv[i]) == "-legacy") {
            chip8.legacyShift = true;
        }
        if (std::string(argv[i]) == "-debug") {
            debugMode = true;
        }
    }

    if (!display.init()) {
        std::cerr << "No Display Initialized :(\n";
        return 1;
    }

    if (debugMode && !debugger.init()) {
        std::cerr << "Debugger did not initialize :(, continuing. \n";
        debugMode = false;
    }

    chip8.loadROM(argv[1]);

    const auto IPS = 700; //instructs/sec
    const auto cycleInterval = std::chrono::microseconds(1000000 / IPS);
    const auto timerInterval = std::chrono::microseconds(1000000 / 60);

    auto lastTimerUpdate = std::chrono::high_resolution_clock::now();

    while (!keypad.shouldQuit()) {
        auto cycleStart = std::chrono::high_resolution_clock::now();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            keypad.processInput(event, chip8.keypad);
        }

        chip8.cycle();

        auto now = std::chrono::high_resolution_clock::now();
        if (now - lastTimerUpdate >= timerInterval) {
            chip8.updateTimers();
            lastTimerUpdate = now;
        }

        if (chip8.drawFlag) {
            display.render(chip8.display);
            chip8.drawFlag = false;
        }

        if (debugMode) debugger.render(chip8);

        auto cycleEnd = std::chrono::high_resolution_clock::now();
        auto elapsed = cycleEnd - cycleStart;

        if (elapsed < cycleInterval) std::this_thread::sleep_for(cycleInterval - elapsed);

    }
    return 0;
}
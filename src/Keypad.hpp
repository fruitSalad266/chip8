#pragma once
#include <SDL3/SDL.h>
#include <cstdint>
#include <array>

class Keypad {
public:
    void processInput(const SDL_Event& event, std::array<uint8_t,16>& keys);
    bool shouldQuit() const { return quit; }
private:
    bool quit = false;
};
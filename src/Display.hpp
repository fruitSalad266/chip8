#pragma once
#include <SDL3/SDL.h>
#include <cstdint>
#include <array>

class Display {
public:
    static constexpr int CHIP8_WIDTH = 64;
    static constexpr int CHIP8_HEIGHT = 32;
    static constexpr int PIXEL_SIZE = 10;
    
    Display();
    ~Display();

    bool init();
    void render(const std::array<uint8_t, CHIP8_WIDTH * CHIP8_HEIGHT>& display);
    void clear();

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};
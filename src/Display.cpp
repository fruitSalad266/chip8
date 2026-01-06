#include "Display.hpp"

Display::Display() = default;

Display::~Display() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Display::init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) { return false; }
    
    window = SDL_CreateWindow(
        "Matt's Chip8 Emulator (MC8E)",
        CHIP8_WIDTH, CHIP8_HEIGHT,
        0
    );

    return true;
}

void Display::render(const std::array<uint8_t, CHIP8_WIDTH * CHIP8_HEIGHT>& display) {
}

void Display::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
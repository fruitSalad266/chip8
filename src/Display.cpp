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
        CHIP8_WIDTH * PIXEL_SIZE, CHIP8_HEIGHT * PIXEL_SIZE,
        0
    );

    if (!window) { return false;}

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {return false;}

    return true;
}

void Display::render(const std::array<uint8_t, CHIP8_WIDTH * CHIP8_HEIGHT>& displayBuffer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int y = 0; y < CHIP8_HEIGHT; ++y) {
        for (int x = 0; x < CHIP8_WIDTH; ++x) {
            if (displayBuffer[y * CHIP8_WIDTH + x]) { //y * width for row, x for column
                //0,0 starts at top left.
                SDL_FRect rect = {
                    static_cast<float>(x * PIXEL_SIZE),
                    static_cast<float>(y * PIXEL_SIZE),
                    static_cast<float> (PIXEL_SIZE),
                    static_cast<float> (PIXEL_SIZE)
                };
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void Display::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
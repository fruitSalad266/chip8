#include "../src/Display.hpp"
#include <iostream>
#include <array>

int main() {
    Display display;

    if (!display.init()) {
        std::cerr << "Failed :( \n";
        return 1;
    }

    std::array<uint8_t, 64 * 32> testBuffer{}; //checkerboard
    std::array<uint8_t, 64 * 32> testBuffer2{}; //Rows

    for (int y = 0; y < 32; ++y) {
        for (int x = 0; x < 64; ++x) {
            if ((x + y) % 2 == 0) {
                testBuffer[y*64 + x] = 1; //64 rows here
            }
            if ( x % 2 == 0) {
                testBuffer2[y*64 + x] = 1;
            }
            //std::cout << "ROW " << x << "COL " << y << std::endl;
        }
    }

    std::cout << "Attempting window display 1" << std::endl;
    display.render(testBuffer);

    //fix for macos SDL -> aka event pumps
    SDL_Event event;
    Uint64 start = SDL_GetTicks();
    while (SDL_GetTicks() - start < 3000) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                return 0;
            }
        }
        SDL_Delay(16);  // ~60fps
    }

    display.clear();
    SDL_Delay(2000);

    std::cout << "Attempting window display 2" << std::endl;
    display.render(testBuffer2);
    SDL_Delay(3000);

    display.clear();
    SDL_Delay(1000);

    return 0;
}
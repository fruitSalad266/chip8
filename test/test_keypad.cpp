#include "../src/Keypad.hpp"
#include "../src/Display.hpp"
#include <iostream>
#include <array>

//This test is laid out so that it doesn't correspond to PHYSICAL keys, but rather
//hexadecimal order. E.g. if you press the key for "0" which is X on QWERTY, the top
//left square gets activated.
int main() {
    Display d;
    Keypad k;
    std::array<uint8_t, 16> keys;

    if (!d.init()) {
        std::cerr << "Failed display :(" << std::endl;
        return 1;
    }

    std::array<uint8_t, 64 * 32> res{};

    std::cout << "Starting test for keys, use left side of keyboard" << std::endl;
    while (!k.shouldQuit()) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            k.processInput(e, keys);
        }

        res.fill(0);
        for (int i  = 0; i < 16; ++i) {
            if (keys[i]) {
                int row = i / 4;
                int col = i % 4;

                for (int dy = 0; dy < 4; ++dy) {
                    for (int dx = 0; dx < 4; ++dx) {
                        int x = col * 8 + dx + 16;
                        int y = row * 8 + dy;
                        res[y * 64 + x] = 1;
                    }
                }
            }
        }
        d.render(res);
        SDL_Delay(16);
    }

    return 0;
}
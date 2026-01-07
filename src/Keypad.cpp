#include "Keypad.hpp"

void Keypad::processInput(const SDL_Event& event, std::array<uint8_t,16>& keys) {
    if (event.type == SDL_EVENT_QUIT) {
        quit = true;
        return;
    }
    if (event.type != SDL_EVENT_KEY_DOWN && event.type != SDL_EVENT_KEY_UP)
        return;

    uint8_t value = (event.type == SDL_EVENT_KEY_DOWN) ? 1 : 0;

    switch (event.key.scancode) {
        case SDL_SCANCODE_ESCAPE: quit = true; break;

            case SDL_SCANCODE_1: keys[0x1] = value; break;
            case SDL_SCANCODE_2: keys[0x2] = value; break;
            case SDL_SCANCODE_3: keys[0x3] = value; break;
            case SDL_SCANCODE_4: keys[0xC] = value; break;

            case SDL_SCANCODE_Q: keys[0x4] = value; break;
            case SDL_SCANCODE_W: keys[0x5] = value; break;
            case SDL_SCANCODE_E: keys[0x6] = value; break;
            case SDL_SCANCODE_R: keys[0xD] = value; break;

            case SDL_SCANCODE_A: keys[0x7] = value; break;
            case SDL_SCANCODE_S: keys[0x8] = value; break;
            case SDL_SCANCODE_D: keys[0x9] = value; break;
            case SDL_SCANCODE_F: keys[0xE] = value; break;

            case SDL_SCANCODE_Z: keys[0xA] = value; break;
            case SDL_SCANCODE_X: keys[0x0] = value; break;
            case SDL_SCANCODE_C: keys[0xB] = value; break;
            case SDL_SCANCODE_V: keys[0xF] = value; break;

        default: break;
    }

}

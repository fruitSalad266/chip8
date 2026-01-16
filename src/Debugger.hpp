#pragma once
#include <SDL3/SDL.h>
#include <cstdint>
#include <string>
#include <set>

class Chip8;

class Debugger {
public:
    Debugger();
    ~Debugger();

    bool init();
    void shutdown();
    void processEvent(SDL_Event& event);
    void render(Chip8& chip8);

    bool isPaused() const { return paused; }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    bool paused = false;

    std::string disassemble(uint16_t opcode);
    void renderInstructionWindow(const Chip8& chip8);
    void renderRegistersWindow(const Chip8& chip8);
    //void renderMemoryWindow(const Chip8& chip8);
    void renderStackWindow(const Chip8& chip8);
    void renderControlWindow();
};
#include "Chip8.hpp"
#include <fstream>
#include <chrono>
#include <cstring>

Chip8::Chip8()
    : randGen(std::chrono::system_clock::now().time_since_epoch().count()),
    randByte(0,255)
{ //copy fontset here
    std::copy(fontset.begin(), fontset.end(), memory.begin() + 0x50);
}

void Chip8::loadROM(const std::string& filename) {

}

void Chip8::cycle() {
    //Fetch
    uint16_t opcode = (memory[PC] << 8) | memory[PC + 1]; //need the two bytes
    PC += 2;
    //decode + execute
    executeOpcode(opcode);
}

void Chip8::updateTimers() {
    if (delayTimer > 0) {
        --delayTimer;
    }
    if (soundTimer > 0) {
        if (soundTimer == 1) {
            //play beep sound
        }
        --soundTimer;
    }
}

void Chip8::executeOpcode(uint16_t opcode) {
    //Put a giant swtich statement here

}
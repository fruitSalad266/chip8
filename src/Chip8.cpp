#include "Chip8.hpp"
#include <fstream>
#include <chrono>
#include <cstring>
#include <iostream>

Chip8::Chip8()
    : randGen(std::chrono::system_clock::now().time_since_epoch().count()),
    randByte(0,255)
{ //copy fontset here
    std::copy(fontset.begin(), fontset.end(), memory.begin() + 0x50);
}


//Chip8 expects programs to be loaded after address 0x200 (aka 512)
void Chip8::loadROM(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file" + filename);
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    if (size > 4096 - 512) {
        throw std::runtime_error("File too large");
    }

    file.read(reinterpret_cast<char*>(&memory[0x200]), size);
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
    uint16_t inst = opcode & 0xF000;
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;
    uint8_t n = opcode & 0x000F;
    uint8_t nn = opcode & 0x00FF;
    uint16_t nnn = opcode & 0x0FFF;

    switch (inst) {
        case 0x0000:
            switch (opcode) {
                case 0x00E0:
                    display.fill(0);
                    drawFlag = true;
                    break;
                case 0x00EE: //pop from stack
                    --SP;
                    PC = stack[SP];
                    break;
            }
            break;
        case 0x1000:
            PC = nnn;
            break;
        case 0x2000: //push to stack
            stack[SP] = PC;
            ++SP;
            PC = nnn;
            break;
        case 0x6000: //set register VX
            V[x] = nn;
            break;
        case 0x7000: //Add val to register VX
            V[x] += nn;
            break;
        case 0xA000: //set index register I
            I = nnn;
            break;
        case 0xD000: {
            //display/draw
            uint8_t x_coord = V[x] & 63; // = % 64
            uint8_t y_coord = V[y] & 31; // = % 32
            V[0xF] = 0; //aka v[f]

            for (unsigned int row = 0; row < n; ++row) {
                uint8_t spriteByte = memory[I + row]; //what should be drawn at that row
                if (y_coord + row >= 32) break;

                for (unsigned int col = 0; col < 8; ++col) {
                    if (x_coord + col >= 64) break;

                    uint8_t spritePixel = spriteByte & (0x80 >> col); //keep bit if exists
                    uint32_t screenIdx = (y_coord + row) * 64 + (x_coord + col);

                    if (spritePixel) {
                        if (display[screenIdx] == 1) {
                            V[0xF] = 1; //flag as collision
                        }
                        display[screenIdx] ^= 1; //toggle the index
                    }
                }
            }

            drawFlag = true;
            break;
        }
        default: std::cerr << "Unknown opcode: " << opcode << std::endl;
    }
}
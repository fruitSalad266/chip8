#pragma once
#include <cstdint>
#include <array>
#include <string>
#include <random>

class Chip8 {
public:
    Chip8();

    void loadROM(const std::string& filename);
    void cycle();
    void updateTimers();

    //Display buffer
    std::array<uint8_t, 64 * 32> display{};
    bool drawFlag = false;
    bool legacyShift = false; //Legacy behavior not used by default

    std::array<uint8_t, 16> keypad{};

private:
    //Memory 4kb aka 4096 bytes
    std::array<uint8_t, 4096> memory{};

    // V0-VF: 16 8 bit variable registers
    std::array<uint8_t, 16> V{};

    uint16_t I = 0; //16 bit register "I"
    uint16_t PC = 0x200; //program counter - starts in mem at 200

    //Stack + pointer
    std::array<uint16_t, 16> stack{};
    uint8_t SP = 0;

    uint8_t delayTimer = 0;
    uint8_t soundTimer = 0;

    std::default_random_engine randGen;
    std::uniform_int_distribution<uint8_t> randByte{0,255};

    static constexpr std::array<uint8_t, 80> fontset = { //works by turning bytes on,
        //characters take up 4x5 pixels. Each row/column goes downwards from L->R.
        0x60, 0x90, 0x90, 0x90, 0x60, // 0 - custom
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xE0, 0x10, 0xE0, 0x10, 0xE0, // 3 - custom
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0x60, 0x90, 0x60, 0x90, 0x60, // 8 - custom
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    void executeOpcode(uint16_t opcode);
};
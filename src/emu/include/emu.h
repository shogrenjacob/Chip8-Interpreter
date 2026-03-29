#include <cstdint>
#include <stack>
#include "memory.h"
using namespace std;

#ifndef EMU_H
#define EMU_H

class Chip8
{
    private:
        int PC; // Program counter
        uint8_t delay = 0;
        uint8_t sound = 0;

    public:
        uint16_t I = 0; // Index Register, point to location in memory
        stack<uint16_t>* ST; // Stack for 16-bit addresses
        Memory* RAM;
        uint16_t bus = 0;

        // General-Purpose Variable Registers
        uint8_t V0 = 0;
        uint8_t V1 = 0;
        uint8_t V2 = 0;
        uint8_t V3 = 0;
        uint8_t V4 = 0;
        uint8_t V5 = 0;
        uint8_t V6 = 0;
        uint8_t V7 = 0;
        uint8_t V8 = 0;
        uint8_t V9 = 0;
        uint8_t VA = 0;
        uint8_t VB = 0;
        uint8_t VC = 0;
        uint8_t VD = 0;
        uint8_t VE = 0;
        uint8_t VF = 0; // Also used as a flag register

        Chip8();

        void IncPC();
        void DecPC();

        void SetDelay(uint time);
        void SetSound(uint time);

        void RunDelay();
        void RunSound();

        uint8_t ReadByte();
        uint16_t ReadIns();

        void Fetch();
        void Decode();
        void Execute();
        // TODO: Keypad
        
};

#endif // EMU_H
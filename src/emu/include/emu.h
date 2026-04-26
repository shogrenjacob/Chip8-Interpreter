#include <cstdint>
#include <stack>
#include <unordered_map>
#include <functional>
#include "memory.h"
#include "../../include/ui.h"
using namespace std;

#ifndef EMU_H
#define EMU_H

class Chip8
{
    private:
        uint8_t delay = 0;
        uint8_t sound = 0;

    public:
        uint16_t I = 0; // Index Register, point to location in memory
        stack<uint16_t>* ST; // Stack for 16-bit addresses
        Memory* RAM;
        uint16_t bus = 0;
        Screen* screen;
        int PC; // Program counter

        // General-Purpose Variable Registers
        // uint8_t V0 = 0;
        // uint8_t V1 = 0;
        // uint8_t V2 = 0;
        // uint8_t V3 = 0;
        // uint8_t V4 = 0;
        // uint8_t V5 = 0;
        // uint8_t V6 = 0;
        // uint8_t V7 = 0;
        // uint8_t V8 = 0;
        // uint8_t V9 = 0;
        // uint8_t VA = 0;
        // uint8_t VB = 0;
        // uint8_t VC = 0;
        // uint8_t VD = 0;
        // uint8_t VE = 0;
        // uint8_t VF = 0; // Also used as a flag register

        uint8_t V[0xF];

        Chip8();

        void IncPC();
        void DecPC();

        void SetDelay(uint time);
        void SetSound(uint time);

        void RunDelay();
        void RunSound();

        uint8_t ReadByte();
        uint16_t ReadIns();

        uint16_t Fetch();
        void Decode();
        void Execute();
        // TODO: Keypad

        // Debug
        void PrintRegs();
        
        // Instructions
        void ClearScreen(uint16_t ins);
        void Jump(uint16_t ins);
        void SetReg(uint16_t ins);
        void AddToReg(uint16_t ins);
        void SetIR(uint16_t ins);
        void Draw(uint16_t ins);
        void Subroutine(uint16_t ins);
        void Return(uint16_t ins);
        void SkipIfNotEq(uint16_t ins);
        void SkipIfEq(uint16_t ins);
        void SkipIfRegNotEq(uint16_t ins);
        void SkipIfRegEq(uint16_t ins);
        void Or(uint16_t ins);
        void And(uint16_t ins);
        void Xor(uint16_t ins);
        void Set(uint16_t ins);
        void Add(uint16_t ins);
        void Sub(uint16_t ins);
        void SubInv(uint16_t ins);
        void ShiftLeft(uint16_t ins);
        void ShiftRight(uint16_t ins);
};

#endif // EMU_H
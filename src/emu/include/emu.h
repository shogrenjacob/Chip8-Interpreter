#include <cstdint>
#include <stack>
#include <unordered_map>
#include <functional>
#include <random>
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
        int keys[16] = { KEY_ONE, KEY_TWO, KEY_THREE, KEY_FOUR, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_A, KEY_S, KEY_D, KEY_F, KEY_Z, KEY_X, KEY_C, KEY_V };
        int PC; // Program counter

        uint8_t V[0xF];

        Chip8();

        void IncPC();
        void DecPC();

        void SetDelay(uint8_t time);
        void SetSound(uint8_t time);

        void RunDelay();
        void RunSound();

        uint8_t ReadByte();
        uint16_t ReadIns();

        uint16_t Fetch();
        void Decode();
        void Execute();
        void DecTimer(uint8_t timer);

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
        void SkipIfKey(uint16_t ins);
        void SkipIfNotKey(uint16_t ins);
        void JumpWithOffset(uint16_t ins);
        void Rand(uint16_t ins);
        void SetRegToDelay(uint16_t ins);
        void SetDelayToReg(uint16_t ins);
        void SetSoundToReg(uint16_t ins);
        void AddToIndex(uint16_t ins);
        void GetKey(uint16_t ins);
        void FontChar(uint16_t ins);
        void Bcdc(uint16_t ins);
        void Store(uint16_t ins);
        void Load(uint16_t ins);
};

#endif // EMU_H
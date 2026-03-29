#include "./include/emu.h"

Chip8::Chip8()
{
    this->PC = 0x200;
    this->RAM = new Memory();
    this->ST = new stack<uint16_t>();
}

void Chip8::IncPC() { this->PC++; }
void Chip8::DecPC() { this->PC--; }

void Chip8::SetDelay(uint time) { this->delay += time; }
void Chip8::SetSound(uint time) { this->sound += time; }

void Chip8::RunDelay()
{
    // Todo:
}

void Chip8::RunSound()
{
    // Todo:
}

uint8_t Chip8::ReadByte()
{
    Memory mem = *this->RAM;
    return mem.GetByte(this->PC);
}

uint16_t Chip8::ReadIns()
{
    uint16_t ins = 0;
    Memory mem = *this->RAM;
    uint8_t hi = mem.GetByte(this->PC);
    uint8_t lo = mem.GetByte(this->PC + 1); // Make sure to move PC in Fetch

    ins = ( hi << 8 ) | lo;
    return ins;
}
#include "./include/memory.h"

uint8_t Memory::GetByte(uint address)
{
    return this->Ram[address];
}

void Memory::LoadRAM(uint8_t ROM[])
{
    memcpy(this->Ram, ROM, sizeof(ROM)*4096);
}

void Memory::SetByte(uint address, uint8_t val)
{
    this->Ram[address] = val;
}

void Memory::LoadProgram(uint8_t *data, int dataSize)
{
    int iter = 0x200;
    while (iter != 0x200 + dataSize)
    {
        this->SetByte(iter, data[iter-0x200]);
        iter++;
    }
}

void Memory::ResetMemory()
{
    for (int i = 0; i < 4096; i++)
    {
        this->Ram[i] = 0;
    }
}

void Memory::LoadCharset(uint8_t charset[])
{
    uint16_t start = 0x0050;
    for (int i = 0; i < 80; i++)
    {
        this->SetByte(start + i, charset[i]);
    }
}
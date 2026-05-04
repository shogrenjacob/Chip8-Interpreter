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

void Memory::LoadProgram(string& f)
{
    ifstream file(f, ios::binary);

    char byte;
    int iter = 0x200;
    while (file.get(byte))
    {
        this->SetByte(iter, byte);
        iter++;
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
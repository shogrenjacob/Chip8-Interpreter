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

int Memory::LoadProgram(string& f)
{
    ifstream file(f, ios::binary);

    char byte;
    int iter = 0x200;
    while (file.get(byte))
    {
        this->Ram[iter] = byte;
        iter++;
    }
}
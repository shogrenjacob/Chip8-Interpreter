#include "./include/memory.h";

uint8_t Memory::GetByte(uint address)
{
    return this->Ram[address];
}

void Memory::LoadRAM(uint8_t ROM[])
{
    memcpy(this->Ram, ROM, sizeof(ROM)*4096);
}


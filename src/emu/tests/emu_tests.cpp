#include "../include/emu.h"
#include <string.h>

uint8_t TestROM[4096];
Chip8 c8 = Chip8();

void InitC8()
{
    TestROM[0x200] = 0x61;
    TestROM[0x201] = 0x01;
    TestROM[0x202] = 0x71;
    TestROM[0x203] = 0x02;
    TestROM[0x204] = 0xA1;
    TestROM[0x205] = 0x00;
    c8.RAM->LoadRAM(TestROM);
}

void TestReadByte(Chip8* c8)
{
    Chip8 chip = *c8;
    uint8_t byte = chip.ReadByte();

    if (!(byte == 0x11))
    {
        cout << "ReadByte wrong: " << chip.ReadByte() << endl;
        return;
    }

    chip.IncPC();
    byte = chip.ReadByte();

    if (!(byte == 0x22))
    {
        cout << "ReadByte wrong: " << chip.ReadByte() << endl;
        return;
    }

    cout << "--- ReadByte OK ---" << endl;
    cout << "--- ReadBytes = " << byte << endl;
}

void TestReadIns(Chip8* c8)
{
    Chip8 chip = *c8;
    uint16_t ins = chip.ReadIns();

    if (!(chip.ReadIns() == 0x1122))
    {
        cout << "ReadIns wrong: " << chip.ReadIns() << endl;
        return;
    }

    cout << "--- ReadIns OK ---" << endl;
    cout << "--- ReadIns = " << chip.ReadIns() << endl;
}

Chip8 TestFDEAndIns(Chip8* c8)
{
    Chip8 chip = *c8;
    chip.Decode();
    chip.Decode();
    chip.Decode();

    return chip;
}

int main()
{
    InitC8();
    // TestReadIns(&c8);
    // TestReadByte(&c8);
    c8 = TestFDEAndIns(&c8);

    cout << "V1 Again: " << (int)c8.V[0x1] << endl;
    cout << "IR: " << (int)c8.I << endl;
}
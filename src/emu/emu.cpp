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

uint16_t Chip8::Fetch()
{
    uint16_t ins = this->ReadIns();
    this->IncPC();
    this->IncPC();

    return ins;
}

void Chip8::Decode()
{
    uint16_t ins = this->Fetch();
    cout << "ins: " << hex << ins << endl;
    uint16_t ins_type = ins & 0xF000; // Single out the first nibble to determine instruction's type

    switch (ins_type)
    {
        case 0x0000:
            this->ClearScreen(ins);
            break;
        case 0x1000:
            this->Jump(ins);
            break;
        case 0x2000:
            break;
        case 0x3000:
            break;
        case 0x4000:
            break;
        case 0x5000:
            break;
        case 0x6000:
            this->SetReg(ins);
            break;
        case 0x7000:
            this->AddToReg(ins);
            break;
        case 0x8000:
            break;
        case 0x9000:
            break;
        case 0xA000:
            this->SetIR(ins);
            break;
        case 0xB000:
            break;
        case 0xC000:
            break;
        case 0xD000:
            break;
        case 0xE000:
            break;
        case 0xF000:
            break;
    }
}

void Chip8::Execute()
{

}

void Chip8::ClearScreen(uint16_t ins)
{
    cout << "Clear Screen works!: " << ins << endl;
}

void Chip8::Jump(uint16_t ins)
{
    cout << "PC Before Jump: " << this->PC << endl;
    uint16_t address = ins & 0x0FFF;
    this->PC = address;
    cout << "PC after Jump: " << this->PC << endl;
}

void Chip8::SetReg(uint16_t ins)
{
    uint16_t WhichReg = ins & 0x0F00;
    uint8_t data = ins & 0x00FF;

    switch (WhichReg)
    {
        case 0x0000:
            this->V0 = data;
            break;
        case 0x0100:
            this->V1 = data;
            break;
        case 0x0200:
            this->V2 = data;
            break;
        case 0x0300:
            this->V3 = data;
            break;
        case 0x0400:
            this->V4 = data;
            break;
        case 0x0500:
            this->V5 = data;
            break;
        case 0x0600:
            this->V6 = data;
            break;
        case 0x0700:
            this->V7 = data;
            break;
        case 0x0800:
            this->V8 = data;
            break;
        case 0x0900:
            this->V9 = data;
            break;
        case 0x0A00:
            this->VA = data;
            break;
        case 0x0B00:
            this->VB = data;
            break;
        case 0x0C00:
            this->VC = data;
            break;
        case 0x0D00:
            this->VD = data;
            break;
        case 0x0E00:
            this->VE = data;
            break;
        case 0x0F00:
            this->VF = data;
            break;
    }
}

void Chip8::AddToReg(uint16_t ins)
{
    uint16_t WhichReg = ins & 0x0F00;
    uint8_t data = ins & 0x00FF;

    switch (WhichReg)
    {
        case 0x0000:
            this->V0 += data;
            break;
        case 0x0100:
            this->V1 += data;
            break;
        case 0x0200:
            this->V2 += data;
            break;
        case 0x0300:
            this->V3 += data;
            break;
        case 0x0400:
            this->V4 += data;
            break;
        case 0x0500:
            this->V5 += data;
            break;
        case 0x0600:
            this->V6 += data;
            break;
        case 0x0700:
            this->V7 += data;
            break;
        case 0x0800:
            this->V8 += data;
            break;
        case 0x0900:
            this->V9 += data;
            break;
        case 0x0A00:
            this->VA += data;
            break;
        case 0x0B00:
            this->VB += data;
            break;
        case 0x0C00:
            this->VC += data;
            break;
        case 0x0D00:
            this->VD += data;
            break;
        case 0x0E00:
            this->VE += data;
            break;
        case 0x0F00:
            this->VF += data;
            break;
    }
}

void Chip8::SetIR(uint16_t ins)
{
    uint16_t address = ins & 0x0FFF;
    this->I = address;
    cout << "I after SetIR: " << this->I << endl;
}
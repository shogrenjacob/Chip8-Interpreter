#include "./include/emu.h"

Chip8::Chip8()
{
    this->PC = 0x200;
    this->RAM = new Memory();
    this->ST = new stack<uint16_t>();
    this->screen = new Screen();
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

    cout << "[ ins ]" << ins << endl;

    return ins;
}

void Chip8::Decode()
{
    uint16_t ins = this->Fetch();
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
            this->Draw(ins);
            break;
        case 0xE000:
            break;
        case 0xF000:
            break;
    }
}

void Chip8::Execute()
{
    // TODO:
}

void Chip8::ClearScreen(uint16_t ins)
{
    cout << "Cleared Screen" << endl;
}

void Chip8::Jump(uint16_t ins)
{
    uint16_t address = ins & 0x0FFF;
    this->PC = address;
}

void Chip8::SetReg(uint16_t ins)
{
    uint16_t WhichReg = ins & 0x0F00 >> 8;
    uint8_t data = ins & 0x00FF;

    this->V[WhichReg] = data;
}

void Chip8::AddToReg(uint16_t ins)
{
    uint16_t WhichReg = ins & 0x0F00 >> 8;
    uint8_t data = ins & 0x00FF;

    this->V[WhichReg] += data;
}

void Chip8::SetIR(uint16_t ins)
{
    uint16_t address = ins & 0x0FFF;
    this->I = address;
}

void Chip8::Draw(uint16_t ins)
{
    uint8_t xReg = (ins & 0x0F00) >> 8;
    uint8_t yReg = (ins & 0x00F0) >> 4;
    uint8_t N = ins & 0x000F;
    
    uint8_t X = this->V[xReg] % 64;
    uint8_t Y = this->V[yReg] % 32;

    Sprite* ns = new Sprite();
    
    ns->height = N;

    for (int i = 0; i < N; i++)
    {
        ns->lines.push_back(this->RAM->GetByte(this->I+i));
    }

    this->screen->DrawSprite(*ns, this->screen->GetScreen(), X, Y);
}
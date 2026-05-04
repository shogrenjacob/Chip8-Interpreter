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

    //cout << "[ins] - " << hex << ins << endl;

    return ins;
}

void Chip8::Decode()
{
    uint16_t ins = this->Fetch();
    uint16_t ins_type = ins & 0xF000; // Single out the first nibble to determine instruction's type

    cout << "[ins] " << dec << this->PC - 0x200 << "  " << hex << ins << endl;

    switch (ins_type)
    {
        case 0x0000:
            if (ins == 0x00E0) { this->ClearScreen(ins); }
            else if (ins == 0x00EE) { this->Return(ins); }
            break;
        case 0x1000:
            this->Jump(ins);
            break;
        case 0x2000:
            this->Subroutine(ins);
            break;
        case 0x3000:
            this->SkipIfEq(ins);
            break;
        case 0x4000:
            this->SkipIfNotEq(ins);
            break;
        case 0x5000:
            this->SkipIfRegEq(ins);
            break;
        case 0x6000:
            this->SetReg(ins);
            break;
        case 0x7000:
            this->AddToReg(ins);
            break;
        case 0x8000:
            if ((ins & 0x000F) == 0) { this->Set(ins); }
            else if ((ins & 0x000F) == 1) { this->Or(ins); }
            else if ((ins & 0x000F) == 2) { this->And(ins); }
            else if ((ins & 0x000F) == 3) { this->Xor(ins); }
            else if ((ins & 0x000F) == 4) { this->Add(ins); }
            else if ((ins & 0x000F) == 5) { this->Sub(ins); }
            else if ((ins & 0x000F) == 7) { this->SubInv(ins); }
            else if ((ins & 0x000F) == 6) { this->ShiftRight(ins); }
            else if ((ins & 0x000F) == 0xE) { this->ShiftLeft(ins); }
            break;
        case 0x9000:
            this->SkipIfRegNotEq(ins);
            break;
        case 0xA000:
            this->SetIR(ins);
            break;
        case 0xB000:
            this->JumpWithOffset(ins);
            break;
        case 0xC000:
            this->Rand(ins);
            break;
        case 0xD000:
            this->Draw(ins);
            break;
        case 0xE000:
            if (((ins & 0x00F0) >> 4) == 9) { this->SkipIfKey(ins); }
            else if (((ins & 0x00F0) >> 4) == 0xA) { this->SkipIfNotKey(ins); }
            break;
        case 0xF000:
            uint8_t which = ins & 0x00FF;
            switch(which)
            {
                case 0x07:
                    this->SetRegToDelay(ins);
                    break;
                case 0x15:
                    this->SetDelayToReg(ins);
                    break;
                case 0x18:
                    this->SetSoundToReg(ins);
                    break;
                case 0x1E:
                    this->AddToIndex(ins);
                    break;
                case 0x0A:
                    //this->GetKey(ins);
                    break;
                case 0x29:
                    //this->FontChar(ins);
                    break;
                case 0x33:
                    this->Bcdc(ins);
                    break;
                case 0x55:
                    this->Store(ins);
                    break;
                case 0x65:
                    this->Load(ins);
                    break;
                default:
                    break;
            }
            break;
        // default:
        //     break;
    }
}

void Chip8::ClearScreen(uint16_t ins)
{
    for (int i = 0; i < 32; i++)
    {
        this->screen->screen[i] = 0;
    }
}

void Chip8::Jump(uint16_t ins)
{
    uint16_t address = ins & 0x0FFF;
    this->PC = address;
}

void Chip8::SetReg(uint16_t ins)
{
    uint16_t WhichReg = (ins & 0x0F00) >> 8;
    uint8_t data = ins & 0x00FF;

    this->V[WhichReg] = data;
}

void Chip8::AddToReg(uint16_t ins)
{
    uint16_t WhichReg = (ins & 0x0F00) >> 8;
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
    
    uint8_t X = this->V[xReg]; //% 64;
    uint8_t Y = this->V[yReg]; //% 32;

    Sprite* ns = new Sprite(); 
    
    ns->height = N;

    for (int i = 0; i < N; i++)
    {
        ns->lines.push_back(this->RAM->GetByte(this->I+i));
    }

    this->screen->DrawSprite(*ns, this->screen->GetScreen(), X, Y);
}

void Chip8::PrintRegs()
{
    for (int i = 0; i < 16; i++)
    {
        cout << "V" << i << ": " << (int)this->V[i] << endl;
    }
}

void Chip8::Subroutine(uint16_t ins)
{
    uint16_t address = ins & 0x0FFF;
    this->ST->push(this->PC);
    this->PC = address;
}

void Chip8::Return(uint16_t ins)
{
    uint16_t address = this->ST->top();
    this->ST->pop();
    this->PC = address;
}

void Chip8::SkipIfEq(uint16_t ins)
{
    uint8_t reg = (ins & 0x0F00) >> 8;
    uint16_t val = ins & 0x00FF;

    if (this->V[reg] == val)
    {
        this->PC += 2;
    }
}

void Chip8::SkipIfNotEq(uint16_t ins)
{
    uint8_t reg = (ins & 0x0F00) >> 8;
    uint16_t val = ins & 0x00FF;

    if (this->V[reg] != val)
    {
        this->PC += 2;
    }
}

void Chip8::SkipIfRegEq(uint16_t ins)
{
    uint8_t xReg = (ins & 0x0F00) >> 8;
    uint8_t yReg = (ins & 0x00F0) >> 4;

    if (this->V[xReg] == this->V[yReg])
    {
        this->PC += 2;
    }
}

void Chip8::SkipIfRegNotEq(uint16_t ins)
{
    uint8_t xReg = (ins & 0x0F00) >> 8;
    uint8_t yReg = (ins & 0x00F0) >> 4;

    if (this->V[xReg] != this->V[yReg])
    {
        this->PC += 2;
    }
}

void Chip8::Set(uint16_t ins)
{
    uint8_t xReg = (ins & 0x0F00) >> 8;
    uint8_t yReg = (ins & 0x00F0) >> 4;

    this->V[xReg] = this->V[yReg];
}

void Chip8::Or(uint16_t ins)
{
    uint8_t xReg = (ins & 0x0F00) >> 8;
    uint8_t yReg = (ins & 0x00F0) >> 4;

    this->V[xReg] = this->V[xReg] | this->V[yReg];
}

void Chip8::And(uint16_t ins)
{
    uint8_t xReg = (ins & 0x0F00) >> 8;
    uint8_t yReg = (ins & 0x00F0) >> 4;

    this->V[xReg] = this->V[xReg] & this->V[yReg];
}

void Chip8::Xor(uint16_t ins)
{
    uint8_t xReg = (ins & 0x0F00) >> 8;
    uint8_t yReg = (ins & 0x00F0) >> 4;

    this->V[xReg] = this->V[xReg] ^ this->V[yReg];
}

void Chip8::Add(uint16_t ins)
{
    uint8_t xReg = (ins & 0x0F00) >> 8;
    uint8_t yReg = (ins & 0x00F0) >> 4;

    uint16_t checkOverflow = this->V[xReg] + this->V[yReg];

    if (checkOverflow > 255) { this->V[0xF] = 1; }
    else { this->V[0xF] = 0; }

    uint8_t result = this->V[xReg] + this->V[yReg];

    this->V[xReg] = result;
}

void Chip8::Sub(uint16_t ins)
{
    uint8_t xReg = (ins & 0x0F00) >> 8;
    uint8_t yReg = (ins & 0x00F0) >> 4;

    if (V[xReg] >= V[yReg]) { V[0xF] = 1; }
    else { V[0xF] = 0; }

    this->V[xReg] = this->V[xReg] - this->V[yReg];
}

void Chip8::SubInv(uint16_t ins)
{
    uint8_t xReg = (ins & 0x0F00) >> 8;
    uint8_t yReg = (ins & 0x00F0) >> 4;

    if (V[yReg] >= V[xReg]) { V[0xF] = 1; }
    else { V[0xF] = 0; }

    this->V[xReg] = this->V[yReg] - this->V[xReg];
}

void Chip8::ShiftLeft(uint16_t ins)
{
    uint8_t xReg = (ins & 0x0F00) >> 8;
    uint8_t yReg = (ins & 0x00F0) >> 4;

    this->V[xReg] = this->V[yReg];

    uint8_t shiftedOut = (this->V[xReg] & 0b10000000) >> 7;

    if (shiftedOut) { this->V[0xf] = 1; }
    else { this->V[0xf] = 0; }

    this->V[xReg] <<= 1;
}

void Chip8::ShiftRight(uint16_t ins)
{
    uint8_t xReg = (ins & 0x0F00) >> 8;
    uint8_t yReg = (ins & 0x00F0) >> 4;

    this->V[xReg] = this->V[yReg];

    uint8_t shiftedOut = (this->V[xReg] & 0b00000001);

    if (shiftedOut) { this->V[0xf] = 1; }
    else { this->V[0xf] = 0; }

    this->V[xReg] >>= 1;
}

void Chip8::SkipIfKey(uint16_t ins)
{
    uint8_t key = (ins & 0x0F00) >> 8;

    if (IsKeyDown(this->keys[key]))
    {
        this->PC += 2;
    }
}

void Chip8::SkipIfNotKey(uint16_t ins)
{
    uint8_t key = (ins & 0x0F00) >> 8;

    if (!IsKeyDown(this->keys[key]))
    {
        this->PC += 2;
    }
}

void Chip8::JumpWithOffset(uint16_t ins)
{
    uint16_t val = ins & 0x0FFF;
    uint16_t address = val + this->V[0x0];

    this->PC = address;
}

void Chip8::Rand(uint16_t ins)
{
    uint8_t mask = ins & 0x00FF;
    uint8_t reg = (ins & 0x0F00) >> 8;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 255); // 8 bit max

    uint8_t rand_num = dist(gen);
    uint8_t result = rand_num & mask;
    this->V[reg] = result;
}

void Chip8::SetRegToDelay(uint16_t ins)
{
    uint8_t reg = (ins & 0x0F00) >> 8;
    this->V[reg] = this->delay;
}

void Chip8::SetDelayToReg(uint16_t ins)
{
    uint8_t reg = (ins & 0x0F00) >> 8;
    this->delay = this->V[reg];
}

void Chip8::SetSoundToReg(uint16_t ins)
{
    uint8_t reg = (ins & 0x0F00) >> 8;
    this->sound = this->V[reg];
}

void Chip8::AddToIndex(uint16_t ins)
{
    uint8_t reg = (ins & 0x0F00) >> 8;
    this->I += this->V[reg];
}

void Chip8::Store(uint16_t ins)
{
    uint8_t reg = (ins & 0x0F00) >> 8;

    for (int i = 0; i <= reg; i++)
    {
        this->RAM->SetByte(this->I + i, this->V[i]);
    }
}

void Chip8::Load(uint16_t ins)
{
    uint8_t reg = (ins & 0x0F00) >> 8;

    for (int i = 0; i <= reg; i++)
    {
        this->V[i] = this->RAM->GetByte(this->I + i);
    }
}

void Chip8::Bcdc(uint16_t ins)
{
    uint8_t reg = (ins & 0x0F00) >> 8;
    uint8_t val = V[reg];
    string str_val = std::to_string(val);
    this->RAM->SetByte(this->I, str_val[0] - '0'); // - '0' because char num is '0' away from the int version in ascii
    this->RAM->SetByte(this->I + 1, str_val[1] - '0');
    this->RAM->SetByte(this->I + 2, str_val[2] - '0');
}
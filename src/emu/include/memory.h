#include <cstdint>
#include <iostream>
#include <fstream>
using namespace std;

#ifndef MEMORY_H
#define MEMORY_H

class Memory
{
    private:
        uint8_t Ram[4096];
    
    public:
        // Converts Chip-8 program to array of bytes and loads into RAM returns 0 for success and -1 for fail
        void LoadProgram(string& f);

        // Return byte of data held at given address
        uint8_t GetByte(uint address);

        // Set byte at given address in RAM to given value
        void SetByte(uint address, uint8_t val);

        void LoadRAM(uint8_t ROM[]);

        void LoadCharset(uint8_t charset[]);

        // Clears contents of program memory (Charset still remains)
        void Clear();

};

#endif // MEMORY_H
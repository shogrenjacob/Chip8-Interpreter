#include <stdio.h>
#include <iostream>
#include "emu.h"

using namespace std;

/* TODO: 
    - Insert data into memory
    - Run a mock program here
    - Integrate w graphics

*/

int main()
{
    Chip8* c8 = new Chip8;
    Chip8 chip8 = *c8;

    string filename;
    cout << "Enter path to ROM: " << endl;
    cin >> filename;

    chip8.RAM->LoadProgram(filename);

    for (int i = 0; i < 6; i++)
    {
        chip8.Decode();
    }

    cout << "V1 Again: " << (int)chip8.V1 << endl;
    cout << "IR: " << (int)chip8.I << endl;

    return 0;
}
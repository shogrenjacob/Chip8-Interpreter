#include "raylib.h"
#include "resource_dir.h"
#include <cstring>
#include <iostream>

using namespace std;

#ifndef UI_H
#define UI_H

class Screen
{
    private:
        uint64_t screen[32];
        int height;
        int width;
        int pixel_width;
        int pixel_height;
        
    public:
        Screen(int height, int width);
        void LoadScreen(uint64_t s[32]);
        uint64_t GetScreen();
        void RenderScreen();
        int GetHeight();
        int GetWidth();
        void DebugScreen();

};

struct Pixel
{
	int x;
	int y;
	int height;
	int width;
	Color color = { 255, 255, 255, 255 };
};

struct Font_C8
{
    uint64_t lines[5];
    int width = 4;
    int height = 5;
};

class Charset
{
    public:
        Font_C8 Zero = {{0xf0, 0x90, 0x90, 0x90, 0xf0}};
        Font_C8 One = {{0x20, 0x30, 0x20, 0x20, 0x70}};
};

#endif
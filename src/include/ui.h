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

#endif
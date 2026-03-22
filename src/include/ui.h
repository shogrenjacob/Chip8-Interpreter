#include "raylib.h"
#include "resource_dir.h"
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

#ifndef UI_H
#define UI_H

struct Sprite
{
    int width;
    int height;
    vector<uint64_t> lines;
};

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
        void DrawSprite(Sprite sprite, uint64_t s[32], uint ew_offset, uint ns_offset); //TODO: Might need to use a pointer to s
        int GetHeight();
        int GetWidth();
        void DebugScreen(uint64_t s[32]);

};

struct Pixel
{
	int x;
	int y;
	int height;
	int width;
	Color color = { 255, 255, 255, 255 };
};

class Charset
{
    public:
        Sprite Zero = {4, 5, {0xf0, 0x90, 0x90, 0x90, 0xf0}};
        Sprite One = {4, 5, {0x20, 0x30, 0x20, 0x20, 0x70}};
        Sprite Two = {4, 5, {0xf0, 0x80, 0xf0, 0x10, 0xf0}};
        Sprite Three = {4, 5, {0xf0, 0x80, 0xf0, 0x80, 0xf0}};
        Sprite Four = {4, 5, {0x90, 0x90, 0xf0, 0x80, 0x80}};
        Sprite Five = {4, 5, {0xf0, 0x10, 0xf0, 0x80, 0xf0}};
        Sprite Six = {4, 5, {0xf0, 0x10, 0xf0, 0x90, 0xf0}};
        Sprite Seven = {4, 5, {0xf0, 0x80, 0x40, 0x20, 0x20}};
        Sprite Eight = {4, 5, {0xf0, 0x90, 0xf0, 0x90, 0xf0}};
        Sprite Nine = {4, 5, {0xf0, 0x90, 0xf0, 0x80, 0xf0}};
        Sprite A = {4, 5, {0xf0, 0x90, 0xf0, 0x90, 0x90}};
        Sprite B = {4, 5, {0x70, 0x90, 0x70, 0x90, 0x70}}; 
        Sprite C = {4, 5, {0xf0, 0x10, 0x10, 0x10, 0xf0}};
        Sprite D = {4, 5, {0x70, 0x90, 0x90, 0x90, 0x70}}; 
        Sprite E = {4, 5, {0xf0, 0x10, 0xf0, 0x10, 0xf0}};
        Sprite F = {4, 5, {0xf0, 0x10, 0xf0, 0x10, 0x10}};
        Sprite Test = {4, 5, {0x1, 0x5, 0x10, 0xa0, 0x10}};
};

#endif
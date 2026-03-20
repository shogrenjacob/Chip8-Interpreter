#include "include/ui.h"

Screen::Screen(int height, int width)
{
    this->height = GetScreenHeight();
    this->width = GetScreenWidth();
    this->pixel_height = GetScreenHeight() / 32;
    this->pixel_width = GetScreenWidth() / 32;
}

void Screen::LoadScreen(uint64_t screen[32])
{
    memcpy(this->screen, screen, sizeof(screen)*32);    
}

uint64_t Screen::GetScreen() { return *this->screen; }

void Screen::RenderScreen()
{
    // Go through each int64 and l-and with each bit, if the result is 1 then render a pixel
    // Pixel should be rendered at y = index of int64 and x = bit position in int
    int64_t mask = 1;

    for (int i = 0; i < 32; i++)
    {
        int64_t row = this->screen[i];
        for (int j = 0; j < 64; j++)
        {
            if (row & mask)
            {
                DrawRectangle(j*pixel_width, i*pixel_height, pixel_width, pixel_height, WHITE);
            }

            row >>= 1;
        }
    }
}
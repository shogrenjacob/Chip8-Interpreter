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

void Screen::DrawSprite(Sprite sprite, uint64_t s[32], uint ew_offset, uint ns_offset)
{
    for (int i = 0; i < sprite.height; i++)
	{
		s[i + ns_offset] |= sprite.lines[i] << ew_offset >> 4;
	}
}

void Screen::DrawScreen(Sprite s[64], uint64_t screen[32])
{
    this->cursor = 0;
    uint line = 0;

    for (int i = 0; i < 64; i++)
    {
        if (this->cursor >= 30) // 56
        {
            this->cursor = 0;
            line += s[i].height + 1;
        }

        DrawSprite(s[i], screen, cursor, line);
        this->cursor += s[i].width + 1;
    }
}

void Screen::DebugScreen(uint64_t s[32])
{
    cout << endl;
    for (int i = 0; i < 32; i++)
    {
        cout << "[" << i << "]  " << s[i] << endl;
    }
}
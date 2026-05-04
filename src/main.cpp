#include "raylib.h"
#include <iostream>
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "./emu/include/emu.h"

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	Color GREENYELLOW = {157, 255, 112, 255};
	Color VGRAPE = {68, 30, 79, 255};
	Color bg = VGRAPE;
	Color pix = GREENYELLOW;

	// Create the window and OpenGL context
	InitWindow(1500, 700, "Chip-8");
	SetTargetFPS(60);
	Chip8* emu = new Chip8();

	uint8_t chars[] = {
		0xf0, 0x90, 0x90, 0x90, 0xf0,
		0x20, 0x30, 0x20, 0x20, 0x70,
		0xf0, 0x80, 0xf0, 0x10, 0xf0,
		0xf0, 0x80, 0xf0, 0x80, 0xf0,
		0x90, 0x90, 0xf0, 0x80, 0x80,
		0xf0, 0x10, 0xf0, 0x80, 0xf0,
		0xf0, 0x10, 0xf0, 0x90, 0xf0,
		0xf0, 0x80, 0x40, 0x20, 0x20,
		0xf0, 0x90, 0xf0, 0x90, 0xf0,
		0xf0, 0x90, 0xf0, 0x80, 0xf0,
		0xf0, 0x90, 0xf0, 0x90, 0x90,
		0x70, 0x90, 0x70, 0x90, 0x70,
		0xf0, 0x10, 0x10, 0x10, 0xf0,
		0x70, 0x90, 0x90, 0x90, 0x70,
		0xf0, 0x10, 0xf0, 0x10, 0xf0,
		0xf0, 0x10, 0xf0, 0x10, 0x10,
	};

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	uint64_t screen1[32] = {};
	uint64_t screen2[32] = {};
	
	string filename;
    cout << "Enter path to ROM: " << endl;
    cin >> filename;

    emu->RAM->LoadProgram(filename);
	emu->RAM->LoadCharset(chars);
	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		emu->Decode();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(bg);

		//emu->screen->LoadScreen(screen1);
		emu->screen->RenderScreen(pix);

		// if (i == 19)
		// {
		// 	emu->PrintRegs();
		// }

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}

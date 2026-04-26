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
	InitWindow(1600, 800, "Chip-8");
	Chip8* emu = new Chip8();
	Charset* cs = new Charset();
	Charset Charset = *cs;

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	uint64_t screen1[32] = {};
	uint64_t screen2[32] = {};
	Sprite sprites[64] = {
		Charset.One,
		Charset.Two,
		Charset.Three,
		Charset.Four,
		Charset.Five,
		Charset.Six,
		Charset.Seven,
		Charset.Eight,
		Charset.Nine,
		Charset.A,
		Charset.B,
		Charset.C,
		Charset.D,
		Charset.E,
		Charset.F,
		Charset.Seven,
		Charset.Eight,
		Charset.Nine,
		Charset.A,
		Charset.B,
		Charset.C,
		Charset.D,
		Charset.E,
		Charset.F,
		Charset.One,
		Charset.Two,
		Charset.Three,
		Charset.Four,
		Charset.Five,
		Charset.Six
	};

	Sprite testSprites[64]
	{
		Charset.One,
		Charset.Two,
		Charset.Three
	};

	// screen->DrawSprite(Charset.One, screen1, 0, 0);
	// screen->DrawSprite(Charset.Two, screen1, 5, 5);
	// screen->DrawSprite(Charset.Three, screen1, 10, 10);
	// screen->DrawSprite(Charset.Four, screen1, 15, 15);
	// screen->DrawSprite(Charset.Five, screen1, 20, 20);

	// screen->DrawSprite(Charset.A, screen2, 0, 0);
	// screen->DrawSprite(Charset.B, screen2, 5, 5);
	// screen->DrawSprite(Charset.C, screen2, 10, 10);
	// screen->DrawSprite(Charset.D, screen2, 15, 15);
	// screen->DrawSprite(Charset.E, screen2, 20, 20);

	//emu->screen->DrawScreen(sprites, screen1);
	//emu->screen->DebugScreen(screen1);

//	screen1[0] = 12297829382473034410;

	string filename;
    cout << "Enter path to ROM: " << endl;
    cin >> filename;

    emu->RAM->LoadProgram(filename);
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

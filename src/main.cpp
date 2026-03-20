/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include <iostream>
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "./include/ui.h"
using namespace std;

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Chip-8");
	Screen* screen = new Screen(GetScreenHeight(), GetScreenWidth());

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");

	uint64_t pixels[32] = {};

	for (int i = 0; i < 32; i++)
	{
		if (i % 2 == 0)
		{
			pixels[i] = 0xAAAAAAAAAAAAAAAA;
		}
		else
		{
			pixels[i] = 0x5555555555555555;
		}
	}

//	pixels[0] = 12297829382473034410;

	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		screen->LoadScreen(pixels);
		screen->RenderScreen();


		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}

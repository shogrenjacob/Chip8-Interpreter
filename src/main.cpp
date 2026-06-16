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
	emu->KeyMap[0x0] = KEY_X;
	emu->KeyMap[0x1] = KEY_ONE;
	emu->KeyMap[0x2] = KEY_TWO;
	emu->KeyMap[0x3] = KEY_THREE;
	emu->KeyMap[0x4] = KEY_Q;
	emu->KeyMap[0x5] = KEY_W;
	emu->KeyMap[0x6] = KEY_E;
	emu->KeyMap[0x7] = KEY_A;
	emu->KeyMap[0x8] = KEY_S;
	emu->KeyMap[0x9] = KEY_D;
	emu->KeyMap[0xA] = KEY_Z;
	emu->KeyMap[0xB] = KEY_C;
	emu->KeyMap[0xC] = KEY_FOUR;
	emu->KeyMap[0xD] = KEY_R;
	emu->KeyMap[0xE] = KEY_F;
	emu->KeyMap[0xF] = KEY_V;

	uint8_t chars[] = {
		0xf0, 0x90, 0x90, 0x90, 0xf0, // 0
		0x20, 0x30, 0x20, 0x20, 0x70, // 1
		0xf0, 0x80, 0xf0, 0x10, 0xf0, // 2
		0xf0, 0x80, 0xf0, 0x80, 0xf0, // 3
		0x90, 0x90, 0xf0, 0x80, 0x80, // 4
		0xf0, 0x10, 0xf0, 0x80, 0xf0, // 5
		0xf0, 0x10, 0xf0, 0x90, 0xf0, // 6
		0xf0, 0x80, 0x40, 0x20, 0x20, // 7
		0xf0, 0x90, 0xf0, 0x90, 0xf0, // 8
		0xf0, 0x90, 0xf0, 0x80, 0xf0, // 9
		0xf0, 0x90, 0xf0, 0x90, 0x90, // A
		0x70, 0x90, 0x70, 0x90, 0x70, // B
		0xf0, 0x10, 0x10, 0x10, 0xf0, // C
		0x70, 0x90, 0x90, 0x90, 0x70, // D
		0xf0, 0x10, 0xf0, 0x10, 0xf0, // E
		0xf0, 0x10, 0xf0, 0x10, 0x10, // F
	};

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	uint64_t screen1[32] = {};
	uint64_t screen2[32] = {};
	
	string filename;
	bool start = false;
    // cout << "Enter path to ROM: " << endl;
    // cin >> filename;
	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		if (IsFileDropped())
		{
			FilePathList files = LoadDroppedFiles();

			if (files.count > 0)
			{
				int dataSize = 0;
				uint8_t *fileData = LoadFileData(files.paths[0], &dataSize);

				if (fileData != NULL)
				{
					emu->RAM->LoadProgram(fileData, dataSize);
					emu->RAM->LoadCharset(chars);

					UnloadFileData(fileData);
				}
			}

			UnloadDroppedFiles(files);
			start = true;
		}

		// drawing
		BeginDrawing();

		if (start)
		{

			for (int i = 0; i < 10; i++)
			{
				emu->Decode();
			}
			// Setup the back buffer for drawing (clear color and depth buffers)
			ClearBackground(bg);

			//emu->screen->LoadScreen(screen1);
			emu->screen->RenderScreen(pix);
		}

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
		emu->RunDelay();
		emu->RunSound();
	}

	// cleanup
	

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}

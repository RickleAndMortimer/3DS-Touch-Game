#include <3ds.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	gfxInitDefault();

	//Initialize console on top screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
	consoleInit(GFX_TOP, NULL);

	time_t t;
	srand((unsigned)time(&t));

	printf("\x1b[0;0HPress Start to exit.");
	printf("\x1b[1;0HTouch Screen position:");
	u16 y_target = rand() % 300+5;
	u16 x_target = rand() % 240+5;
	u16 score = 0;
	// Main loop
	while (aptMainLoop())
	{
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START) break; // break in order to return to hbmenu

		touchPosition touch;

		//Read the touch screen coordinates
		hidTouchRead(&touch);

		//Print the touch screen coordinates
		printf("\x1b[2;0H%03d; %03d", touch.px, touch.py);
		printf("\x1b[3;0HTarget coordinates: %03d, %03d", x_target, y_target);
		if (touch.px == x_target && touch.py == y_target) {
			score++;
			x_target = rand() % 300;
			y_target = rand() % 240;
		}
		printf("\x1b[4;0HScore: %03d", score);
		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();
	}

	// Exit services
	gfxExit();
	return 0;
}

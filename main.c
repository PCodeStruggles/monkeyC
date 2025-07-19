//TODO: Load mono space font [x]
//TODO: Render a centered string to be typed in
//TODO: Cycle through different strings to be typed
//TODO: Implemet input loop
#include "raylib.h"
#include <stdlib.h>

int main(void) {
	const int screenWidth = 1600;
	const int screenHeight = 900;

	InitWindow(screenWidth, screenHeight, "Debug Version: MonkeyC");
	SetTargetFPS(60);

	Font font = LoadFontEx("./fonts/JetBrainsMono-Regular.ttf", 32,  NULL,  0);
	SetTextLineSpacing(16);

	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);
		DrawTextEx(font, "Hello, my name is Shady", (Vector2) {50 ,50},  30.0f, 2.0f, BLACK);
		EndDrawing();
	}
	UnloadFont(font);
	CloseWindow();
	return 0;
}

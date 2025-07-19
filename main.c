//TODO: Load mono space font [x]
//TODO: Render a centered string to be typed in [x]
//TODO: Mechanism to cycle through diff strings [x]
//TODO: Implemet input loop [x]
//TODO: render cursor
//TODO: end screen when there's no more strings to type [x]

#include "raylib.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define LINES_CAP 10

typedef struct {
	const char* data;
	size_t count;
} Line;

typedef struct {
	size_t count;
	Line lines[LINES_CAP];
} Lines;

typedef enum Screen {
	TYPING = 0,
	END = 1
} Screen;

int main(void) {
	const int screenWidth = 1600;
	const int screenHeight = 900;

	Lines lines = { .count = 0, .lines = {0} };

	Line line1 = { .data = "i use arch btw", .count = strlen(line1.data) };
	lines.lines[lines.count++] = line1;

	Line line2 = { .data = "and if i have ranged like him that travels i return again", .count = strlen(line2.data) };
	lines.lines[lines.count++] = line2;

	Line line3 = { .data = "Hello, my name is Giovanni Giorgio", .count = strlen(line3.data) };
	lines.lines[lines.count] = line3;

	InitWindow(screenWidth, screenHeight, "Debug Version: MonkeyC");
	SetTargetFPS(60);

	const char* fontPath = "./fonts/JetBrainsMono-Regular.ttf";
	const Font font = LoadFontEx(fontPath, 150,  NULL,  0);
	const float fontSize = 35.0f;
	const float fontSpacing = 5.0f;
	const int charHeight = font.baseSize;
	SetTextLineSpacing(16);

	printf("screenWidth: %d\nscreenHeight: %d\n", screenWidth, screenHeight);

	int i = 0;
	int stringIndex = 0;
	int cursorOffset = 0;

	const char* gameOverMsg = "GAME OVER!";

	Screen currentScreen = TYPING;

	while(!WindowShouldClose()) {

		switch (currentScreen) {
			case(TYPING): 
			{
			//Cycle through strings
			if(IsKeyPressed(KEY_ENTER) && i < lines.count ){
				i++;
				stringIndex = 0;
			} else if(IsKeyPressed(KEY_ENTER) && i >= lines.count)
						currentScreen = END;

			if(stringIndex > 0 && IsKeyPressed(KEY_BACKSPACE)) {
				stringIndex--;
			}

			//Get input char
			int charPressed;
			while((charPressed = GetCharPressed()) != 0) {
				if (stringIndex <= lines.lines[i].count && charPressed == lines.lines[i].data[stringIndex]) {
					stringIndex++;
				} 		
			}

			} break;

			case END: break;
				
		}

		Vector2 lineSize = MeasureTextEx(font, lines.lines[i].data, fontSize, fontSpacing);

		BeginDrawing();

		ClearBackground(WHITE);
		switch(currentScreen)
		{
			case TYPING:
			{				
				//Render text to be typed in
				DrawTextEx(font, TextFormat("%.*s", lines.lines[i].count, lines.lines[i].data),
					(Vector2) {(screenWidth / 2) - (lineSize.x / 2), screenHeight / 2},
					fontSize, fontSpacing, GRAY);

				//Reder input text
				DrawTextEx(font, TextFormat("%.*s", stringIndex, lines.lines[i].data),
					(Vector2) {(screenWidth / 2) - (lineSize.x / 2), screenHeight / 2},
					fontSize, fontSpacing, BLACK);
			} break;

			case END:
			{
				Vector2 endGamelineSize = MeasureTextEx(font, gameOverMsg, fontSize, fontSpacing);
				DrawTextEx(font, gameOverMsg,
				(Vector2) {(screenWidth / 2) - (endGamelineSize.x / 2), screenHeight / 2},
				fontSize, fontSpacing, BLACK);
			} break;

		}

		EndDrawing();
	}

	UnloadFont(font);
	CloseWindow();
	return 0;
}

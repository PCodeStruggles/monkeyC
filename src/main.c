#include "raylib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDS_CAP 15
#define textSize(text) MeasureText(text, fontSize) 

typedef struct {
	const char* data;
	size_t count;
} Word;

typedef struct {
	size_t count;
	Word words[WORDS_CAP];
} Words;

typedef enum {
	START = 0,
	TYPING,
	END,
} ScreeType;

int main(void) {
	const int screenWidth = 1600;
	const int screenHeight = 900;
	const int fontSize = 35;
	const char* startScreenText = "Press ENTER to play, DELETE to quit";
	const char* endScreenText = "Thanks for playing, press ENTER to play again";

	Words words = {0};

	Word word1 = { .data = "neat", .count = strlen(word1.data) };
	words.words[words.count++] = word1;

	Word word2 = { .data = "terrific", .count = strlen(word2.data) };
	words.words[words.count++] = word2;

	Word word3 = { .data = "outstanding", .count = strlen(word3.data) };
	words.words[words.count] = word3;

	size_t wordIndex = 0;
	size_t matchIndex = 0;
	size_t wordCount = 0;

	float centerX = screenWidth / 2;
	float centerY = screenHeight / 2;
	float circleRadius = 100.0f;

	ScreeType currentScreen = START;

	InitWindow(screenWidth, screenHeight, "Debug Version: Bubble");
	SetTargetFPS(60);

	while(!WindowShouldClose()) {
		switch (currentScreen) {

			case START:{
				if(IsKeyPressed(KEY_ENTER))
					currentScreen = TYPING;

				if(IsKeyPressed(KEY_DELETE))
					currentScreen = END;
			}break;
		
			case TYPING: {

			if(IsKeyPressed(KEY_DELETE))
				currentScreen = END;

			int charPressed;
			while((charPressed = GetCharPressed()) != 0) {
				if(matchIndex <= words.words[wordIndex].count &&
					charPressed == words.words[wordIndex].data[matchIndex]) {
					matchIndex++;
					if(matchIndex == words.words[wordIndex].count) {
						//Generate new circle with new word
						wordIndex = GetRandomValue(0, words.count);
						circleRadius = textSize(words.words[wordIndex].data) + 10;
						centerX = GetRandomValue(0 + circleRadius, screenWidth - circleRadius);
						centerY = GetRandomValue(0 + circleRadius, screenHeight - circleRadius);
						matchIndex = 0;
						wordCount++;
						if (wordCount == 5) currentScreen = END;
					} 
				}
			}
			} break;

			case END:{
				if(IsKeyPressed(KEY_ENTER)) {
					matchIndex = 0;
					wordCount = 0;
					currentScreen = TYPING;
				}
			}break;
		}

		BeginDrawing();

		ClearBackground(WHITE);

		switch (currentScreen) {

			case START: {
				DrawText(startScreenText, 
					(GetScreenWidth() / 2) - (textSize(startScreenText) / 2),
					GetScreenHeight() / 2,
					fontSize, 
					LIGHTGRAY);
			}break;

			case TYPING: {

				DrawText(TextFormat("%zu", wordCount), 
					GetScreenWidth() / 2,
					GetScreenHeight() / 2,
					fontSize + 50, 
					LIGHTGRAY);

				DrawCircle(centerX, centerY, circleRadius, RED);
				DrawText(TextFormat("%.*s", words.words[wordIndex].count, words.words[wordIndex].data), 
						centerX - (textSize(words.words[wordIndex].data) / 2), 
						centerY - (GetFontDefault().baseSize) / 2, 
						fontSize, 
						LIGHTGRAY);

				DrawText(TextFormat("%.*s", matchIndex, words.words[wordIndex].data),
						centerX - (textSize(words.words[wordIndex].data) / 2), 
						centerY - (GetFontDefault().baseSize) / 2, 
						fontSize, 
						WHITE);
				} break;

			case END: {
				DrawText(endScreenText, 
					(GetScreenWidth() / 2) - (textSize(endScreenText) / 2),
					GetScreenHeight() / 2,
					fontSize, 
					LIGHTGRAY);
			}break;
		}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}

#include "raylib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDS_CAP 15

typedef struct {
	const char* data;
	size_t count;
} Word;

typedef struct {
	size_t count;
	Word words[WORDS_CAP];
} Words;

int main(void) {
	const int screenWidth = 1600;
	const int screenHeight = 900;
	const int fontSize = 35;

	Words words = {0};

	Word word1 = { .data = "neat", .count = strlen(word1.data) };
	words.words[words.count++] = word1;

	Word word2 = { .data = "terrific", .count = strlen(word2.data) };
	words.words[words.count++] = word2;

	Word word3 = { .data = "outstanding", .count = strlen(word3.data) };
	words.words[words.count] = word3;

	size_t wordIndex = 0;
	size_t matchIndex = 0;

	float centerX = screenWidth / 2;
	float centerY = screenHeight / 2;
	float circleRadius = 100.0f;

	InitWindow(screenWidth, screenHeight, "Debug Version: Bubble");
	SetTargetFPS(60);

	while(!WindowShouldClose()) {

		int charPressed;
		while((charPressed = GetCharPressed()) != 0) {
			if(matchIndex <= words.words[wordIndex].count &&
				charPressed == words.words[wordIndex].data[matchIndex]) {
				matchIndex++;
				if(matchIndex == words.words[wordIndex].count) {
					//Generate new circle with new word
					wordIndex = GetRandomValue(0, words.count);
					circleRadius = MeasureText(words.words[wordIndex].data, fontSize) + 10;
					centerX = GetRandomValue(0 + circleRadius, screenWidth - circleRadius);
					centerY = GetRandomValue(0 + circleRadius, screenHeight - circleRadius);
					matchIndex = 0;
				} 
			}
		}

		BeginDrawing();

		ClearBackground(WHITE);

		DrawCircle(centerX, centerY, circleRadius, RED);
		DrawText(TextFormat("%.*s", words.words[wordIndex].count, words.words[wordIndex].data), 
				centerX - (MeasureText(words.words[wordIndex].data, fontSize) / 2), 
				centerY - (GetFontDefault().baseSize) / 2, 
				fontSize, 
				LIGHTGRAY);

		DrawText(TextFormat("%.*s", matchIndex, words.words[wordIndex].data),
				centerX - (MeasureText(words.words[wordIndex].data, fontSize) / 2), 
				centerY - (GetFontDefault().baseSize) / 2, 
				fontSize, 
				WHITE);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}

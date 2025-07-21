#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "utils.h"
#define SV_IMPLEMENTATION
#include "sv.h"

#define WORDS_CAP 100
#define getTextSize(text) MeasureText((text), fontSize) 

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

	const char* dictionaryFilePath = "./src/dictionary.txt";
	const char* dictionary = loadContentFromFile(dictionaryFilePath);
	String_View svDictionary = { .count = strlen(dictionary), .data = dictionary };

	Words words = {0};

	while(svDictionary.count > 0) {
		String_View svToken = sv_chop_by_delim(&svDictionary, '\n');
		words.words[words.count] = (Word) {.count = svToken.count, 
					           .data = (char*)malloc(svToken.count) };
		if(words.words[words.count].data == NULL){ 
			logErrorAndAbort();
		} else { 
			memcpy(words.words[words.count].data, svToken.data, svToken.count);
		}
		words.count++;
	}

	size_t wordIndex = 0;
	size_t matchIndex = 0;
	size_t wordCount = 0;

	float centerX = (float) screenWidth / 2;
	float centerY = (float) screenHeight / 2;
	float circleRadius = 100.0f;

	ScreeType currentScreen = START;

	InitWindow(screenWidth, screenHeight, "BubbleC");
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
						wordIndex = GetRandomValue(0, words.count - 1);
						circleRadius = getTextSize(TextFormat("%.*s", words.words[wordIndex].count,
											words.words[wordIndex].data)) + 10;
						centerX = GetRandomValue(0 + circleRadius, 
								screenWidth - circleRadius);
						centerY = GetRandomValue(0 + circleRadius, 
								screenHeight - circleRadius);
						matchIndex = 0;
						wordCount++;
						if (wordCount == 15) currentScreen = END;
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
					(GetScreenWidth() / 2) - (getTextSize(startScreenText) / 2),
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

				const char* wordToRender = TextFormat("%.*s", words.words[wordIndex].count, words.words[wordIndex].data);
				DrawText(wordToRender,
						centerX - ((float)getTextSize(wordToRender) / 2),
						centerY - (float)GetFontDefault().baseSize / 2, 
						fontSize, 
						LIGHTGRAY);

				DrawText(TextFormat("%.*s", matchIndex, words.words[wordIndex].data),
						centerX - ((float)getTextSize(wordToRender) / 2),
						centerY - (float)GetFontDefault().baseSize / 2, 
						fontSize, 
						WHITE);
				} break;

			case END: {
				DrawText(endScreenText, 
					(GetScreenWidth() / 2) - (getTextSize(endScreenText) / 2),
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

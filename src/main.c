#include "raylib.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SV_IMPLEMENTATION
#include "sv.h"

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

//Index of currently displayed word
size_t wordIndex = 0;
//Index of char to be typed in
size_t matchIndex = 0;
//Number of word typed
size_t wordCount = 0;

while(svDictionary.count > 0 && words.count < WORDS_CAP) {
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

ScreeType currentScreen = START;

Timer timer = {0};

InitWindow(screenWidth, screenHeight, "BubbleC");
SetTargetFPS(60);

float circleCenterX = (float) GetScreenWidth() / 2;
float circleCenterY = (float) GetScreenHeight() / 2;
float circleRadius = 100.0f;

while(!WindowShouldClose()) {
	switch (currentScreen) {

		case START:{
			if(IsKeyPressed(KEY_ENTER)) {
					currentScreen = TYPING;
					startTimer(&timer, TIMER_LIFETIME);
				};

			if(IsKeyPressed(KEY_DELETE)) currentScreen = END;
		}break;
	
		case TYPING: {

		if(IsKeyPressed(KEY_DELETE)) currentScreen = END;

		int charPressed;
		while((charPressed = GetCharPressed()) != 0) {
			if(matchIndex <= words.words[wordIndex].count &&
				charPressed == words.words[wordIndex].data[matchIndex]) {
				matchIndex++;
				if(matchIndex == words.words[wordIndex].count) {
					//Generate new circle with new word
					wordIndex = GetRandomValue(0, words.count - 1);
					//FIXME: REMOVE MAGIC NUMBER
					circleRadius = getTextSize(TextFormat("%.*s", words.words[wordIndex].count, words.words[wordIndex].data)) + 10;
					circleCenterX = GetRandomValue(0 + circleRadius, 
							screenWidth - circleRadius);
					circleCenterY = GetRandomValue(0 + circleRadius, 
							screenHeight - circleRadius);
					matchIndex = 0;
					wordCount++;
				} 
			}
		}
		} break;

		case END:{
			if(IsKeyPressed(KEY_ENTER)) {
				matchIndex = 0;
				wordCount = 0;
				currentScreen = TYPING;
				startTimer(&timer, TIMER_LIFETIME);
			}
		}break;
	}

	BeginDrawing();

	ClearBackground(WHITE);

	switch (currentScreen) {

		case START: {
			DrawText(startScreenText, 
				screenCenterX - (getTextSize(startScreenText) / 2),
				screenCenterY,
				fontSize, 
				LIGHTGRAY);
		}break;

		case TYPING: {
			DrawText(TextFormat("%.0lf\n", elapsedTime(&timer)), 10, 10, fontSize + 20, LIGHTGRAY);

			//FIXME: REMOVE MAGIC NUMBER
			DrawText(TextFormat("%zu", wordCount), 
				screenCenterX,
				screenCenterY,
				fontSize + 50, 
				LIGHTGRAY);

			DrawCircle(circleCenterX, circleCenterY, circleRadius, RED);

			const char* wordToRender = TextFormat("%.*s", words.words[wordIndex].count, 
								words.words[wordIndex].data);
			DrawText(wordToRender,
				circleCenterX - ((float)getTextSize(wordToRender) / 2),
				circleCenterY - (float)GetFontDefault().baseSize / 2, 
				fontSize, 
				LIGHTGRAY);

			DrawText(TextFormat("%.*s", matchIndex, words.words[wordIndex].data),
					circleCenterX - ((float)getTextSize(wordToRender) / 2),
					circleCenterY - (float)GetFontDefault().baseSize / 2, 
					fontSize, 
					WHITE);

			if (timerDone(&timer) || wordCount == 30) currentScreen = END;
			} break;

		case END: {
			DrawText(endScreenText, 
				screenCenterX - (getTextSize(endScreenText) / 2),
				screenCenterY,
				fontSize, 
				LIGHTGRAY);

			//Calculate WMP over 30 sec span
			//FIXME: REMOVE MAGIC NUMBER
			const char* wmp = TextFormat("WPM: %zu", wordCount * 2);
			DrawText(wmp,
				screenCenterX - getTextSize(wmp) /2,
				screenCenterY - 75,
				fontSize,
				LIGHTGRAY);
		}break;
	}

	EndDrawing();
}

CloseWindow();
return 0;
}

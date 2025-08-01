#ifndef UTILS_H
#define UTILS_H

#include <errno.h>
#include <stddef.h>

#define WORDS_CAP 1000
#define TIMER_LIFETIME 30.0
#define screenCenterX (GetScreenWidth() / 2) 
#define screenCenterY (GetScreenHeight() / 2) 
#define getTextSize(text) MeasureText((text), fontSize) 

#define logErrorAndAbort() do{                                                      \
				printf("ERROR: %d - %s\n", errno, strerror(errno)); \
				exit(EXIT_FAILURE);				    \
			   } while(0)                                               \

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

typedef struct Timer {
	double startTime;
	double lifeTime;
} Timer;

char* loadContentFromFile(const char* filePath);

void startTimer(Timer* timer, double lifetime);
int timerDone(Timer* timer);
double elapsedTime(Timer* timer);

#endif // UTILS_H

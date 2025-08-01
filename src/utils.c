#include "utils.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//TODO: Make it so it returns NULL if couldn't read file instead of aborting.
char* loadContentFromFile(const char* filePath) {

	FILE* fptr;
	if ((fptr = fopen(filePath, "r")) == NULL) {
		printf("ERROR: %d %s - %s\n", errno, filePath, strerror(errno));
		exit(EXIT_FAILURE);
	}
	if(!(fseek(fptr, 0, SEEK_END) == 0)){
		fclose(fptr);
		logErrorAndAbort();
	}
	long int fileSize = 0;
	if((fileSize = ftell(fptr)) == -1) {
		fclose(fptr);
		logErrorAndAbort();
	}
	fseek(fptr, 0, SEEK_SET);

	char* fileData;
	if((fileData = (char*)malloc(fileSize)) == NULL) {
		fclose(fptr);
		logErrorAndAbort();
	}

	size_t bytesRead = 0;
	if((bytesRead = fread(fileData, sizeof(char), fileSize, fptr)) != fileSize){
		fclose(fptr);
		logErrorAndAbort();
	}

	if((fclose(fptr)) != 0) logErrorAndAbort();

	printf("Input file: %s\nFile size: %ld\n", filePath, fileSize);
	printf("Number of bytes read into buffer: %zu\n", bytesRead);

	return fileData;
}

void startTimer(Timer* timer, double lifetime) {
	timer->startTime = GetTime();
	timer->lifeTime = lifetime;
}

int timerDone(Timer* timer) {
	return GetTime() - timer->startTime >= timer->lifeTime ? 1 : 0;
}

double elapsedTime(Timer* timer) {
	return GetTime() - timer->startTime;
}

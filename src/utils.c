#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char* loadContentFromFile(const char* filePath) {

	FILE* fptr;
	//Open file
	if ((fptr = fopen(filePath, "r")) == NULL) {
		printf("ERROR: %d %s - %s\n", errno, filePath, strerror(errno));
		exit(EXIT_FAILURE);
	}
	//Set cursor to file end to get file size in bytes
	if(!(fseek(fptr, 0, SEEK_END) == 0)){
		logErrorAndAbort();
	}
	//Read cursor position in bytes	
	long int fileSize = 0;
	if((fileSize = ftell(fptr)) == -1) {
		logErrorAndAbort();
	}
	//Reset cursor position to read file from the beginning
	fseek(fptr, 0, SEEK_SET);

	//Allocate the file content buffer on the heap
	char* fileData;
	if((fileData = (char*)malloc(fileSize)) == NULL) {
		logErrorAndAbort();
	}

	//Read content file into the buffer pointed to by fileData
	size_t bytesRead = 0;
	if((bytesRead = fread(fileData, sizeof(char), fileSize, fptr)) != fileSize){
		logErrorAndAbort();
	}

	//Log results
	printf("Input file: %s\nFile size: %ld\n", filePath, fileSize);
	printf("Number of bytes read into buffer: %zu\n", bytesRead);

	//Return pointer to buffer
	return fileData;
}

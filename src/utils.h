#ifndef UTILS_H
#define UTILS_H

#define logErrorAndAbort() do{                                                      \
				printf("ERROR: %d - %s\n", errno, strerror(errno)); \
				exit(EXIT_FAILURE);				    \
			   } while(0)                                               \

char* loadContentFromFile(const char* filePath);

#endif // UTILS_H

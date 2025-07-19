CC = gcc

main: main.c
	$(CC) main.c -o main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

clean:
	rm main

CC = gcc

main: ./src/main.c
	$(CC) ./src/main.c -o ./bin/main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

clean:
	rm main

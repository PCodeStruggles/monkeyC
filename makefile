CC = gcc

all: monkeyc

./bin/utils.o: ./src/utils.c ./src/utils.h
	mkdir -p ./bin
	$(CC) -c ./src/utils.c -o ./bin/utils.o

monkeyc: ./bin/utils.o ./src/main.c
	$(CC) ./src/main.c ./bin/utils.o -o ./bin/monkeyc -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

clean:
	rm ./bin/utils.o
	rm ./bin/monkeyc
	rm -r ./bin

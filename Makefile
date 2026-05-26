CC = gcc
CFLAGS = -g -Wall

all: final

final: main.o board.o tetromino.o renderer.o input.o game.o
	echo "Linking..."
	$(CC) $(CFLAGS) main.o board.o tetromino.o renderer.o input.o game.o -o final -lncursesw
	chmod +x final

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

board.o: board.c
	$(CC) $(CFLAGS) -c board.c -o board.o

tetromino.o: tetromino.c
	$(CC) $(CFLAGS) -c tetromino.c -o tetromino.o

renderer.o: renderer.c
	$(CC) $(CFLAGS) -c renderer.c -o renderer.o

input.o: input.c
	$(CC) $(CFLAGS) -c input.c -o input.o

game.o: game.c
	$(CC) $(CFLAGS) -c game.c -o game.o

clean:
	rm -f *.o final

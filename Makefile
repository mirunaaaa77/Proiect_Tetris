CC = gcc
CFLAGS =-g -Wall -pedantic

all: final	

final: main.o board.o tetromino.o renderer.o
	echo "Linking and producing the final application:"
	$(CC) $(CFLAGS) main.o board.o tetromino.o renderer.o -o final -lncurses
	chmod +x final

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

board.o: board.c
	$(CC) $(CFLAGS) -c board.c -o board.o

tetromino.o: tetromino.c
	$(CC) $(CFLAGS) -c tetromino.c -o tetromino.o
	
renderer.o: renderer.c
	$(CC) $(CFLAGS) -c renderer.c -o renderer.o

clean:
	rm main.o board.o tetromino.o renderer.o final
CFLAGS = gcc -g -Wall -pedantic

all: final	

final: main.o board.o
	echo "Linking and producing the final application:"
	$(CFLAGS) main.o board.o -o final
	chmod +x final

main.o: main.c
	$(CFLAGS) -c main.c -o main.o

board.o: board.c
	$(CFLAGS) -c board.c -o board.o

clean:
	rm main.o board.o final
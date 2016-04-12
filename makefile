all: programa limpa

programa: tetris.o 
	gcc tetris.o -o tretas

tetris.o: tetris.c 
	gcc -c tetris.c

limpa:
	rm *.o 
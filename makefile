all: programa limpa

programa: ntetris.o campo.o bloco.o engine.o  
	gcc ntetris.o campo.o bloco.o engine.o -lncurses -o programa

ntetris.o: ntetris.c campo.c Campo.h bloco.c Bloco.h engine.c Engine.h
	gcc -c ntetris.c -lncurses

campo.o: campo.c Estruturas.h Campo.h
	gcc -c campo.c -lncurses

bloco.o: bloco.c Estruturas.h Bloco.h
	gcc -c bloco.c -lncurses

engine.o: engine.c Estruturas.h Engine.h
	gcc -c engine.c -lncurses

limpa:
	rm *.o 
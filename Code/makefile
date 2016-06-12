all: programa limpa

programa: ntetris.o campo.o bloco.o engine.o rank.o
	gcc ntetris.o campo.o bloco.o engine.o rank.o -lncurses -o tetris

ntetris.o: ntetris.c campo.c campo.h bloco.c bloco.h engine.c engine.h rank.c rank.h estruturas.h 
	gcc -c ntetris.c -lncurses # -o teste
	# ./teste

campo.o: campo.c campo.h estruturas.h
	gcc -c campo.c -lncurses

bloco.o: bloco.c bloco.h estruturas.h 
	gcc -c bloco.c -lncurses # -lcunit -I./CUnit -L./CUnit -o teste_bloco
	# ./teste_bloco

engine.o: engine.c engine.h estruturas.h
	gcc -c engine.c -lncurses # -I./CUnit -L./CUnit -lcunit -o teste_engine
	# ./teste_engine

rank.o: rank.c rank.h estruturas.h
	gcc -c rank.c -lncurses # -I./CUnit -L./CUnit -lcunit -o teste_rank
	# ./teste_rank

limpa:
	rm *.o 

# Para checar erros usamos o codigo abaixo no terminal
# splint *.c *.h -weak +infloops +compdef +sysdirerrors

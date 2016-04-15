all: programa testebloco testeengine limpa

programa: ntetris.o campo.o bloco.o engine.o  
	gcc ntetris.o campo.o bloco.o engine.o -lncurses -o tetris

ntetris.o: ntetris.c campo.c Campo.h bloco.c Bloco.h engine.c Engine.h
	gcc -c ntetris.c -lncurses # -o teste
	# ./teste

campo.o: campo.c Estruturas.h Campo.h
	gcc -c campo.c -lncurses

bloco.o: bloco.c Estruturas.h Bloco.h
	gcc -c bloco.c -lncurses # -lcunit -I./CUnit -L./CUnit -o teste_bloco
	# ./teste_bloco

engine.o: engine.c Estruturas.h Engine.h
	gcc -c engine.c -lncurses # -I./CUnit -L./CUnit -lcunit -o teste_engine
	# ./teste_engine

testebloco: bloco_teste.c
	gcc bloco_teste.c -lncurses -lcunit -o testebloco

testeengine: engine_teste.c
	gcc engine_teste.c -lncurses -lcunit -o testeengine

limpa:
	rm *.o 
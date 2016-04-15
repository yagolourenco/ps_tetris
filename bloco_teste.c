#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ncurses.h>
#include <unistd.h> /* para a funcao getch_char e getch*/ 
#include <termios.h> 

#include "Estruturas.h"

/* BLOCO.C ----------------------------------------------------------------------------------------------------------------------------- */

int put_block(int newX, int newY) {

	/* Condiçoes de entrada, o bloco nao pode passar o tamanho da matriz */

	if(newY >= ALTURA || newY < 0){
		return FALSO;
	}

	if(newX >= LARGURA || newX < 0){
		return FALSO;
	}

	int i, dirX, dirY;
	
	if(currentBlock.direction == HORIZONTAL) {
		dirX = 1;
		dirY = 0;
	}
	else if(currentBlock.direction == VERTICAL) {
		dirX = 0;
		dirY = 1;
	}
	
	for(i = 0; i < currentBlock.size; i++)
		game.field[currentBlock.x + (dirX * i)][currentBlock.y + (dirY * i)] = VAZIO; /* Caso seja horizontal, começa construindo da esquerda para direita / caso seja vertical, começa de cima pra baixo. Nos dois casos preenchendo a matriz com 0*/
		
	for(i = 0; i < currentBlock.size; i++)
		game.field[newX + (dirX * i)][newY + (dirY * i)] = currentBlock.color; /* Colore a matriz com a cor do bloco */

	/* Os dois laços são iguais, o primeiro preenche a matriz logicamente e o segundo visulamente */

	return 0;
}

void new_block(){

	int c = 1 + rand() % 5;

	while(c == currentBlock.color) c = 1 + rand() % 5; /* Mudar a cor do bloco em relação ao anterior */

	currentBlock.color = c;	

	currentBlock.direction = rand() % 2;  /* Varia de horizontal para vertical */

	currentBlock.size = (rand() % 3) + 3; /* tamanho da peca */
	
	currentBlock.y = 0; /* A peça começa sempre no topo do campo */
	
	currentBlock.x = rand()%(LARGURA-(currentBlock.direction?0:currentBlock.size-1)); 
	
	/*printw("x=%d\n", currentBlock.x);*/ /* Funcao comentada para nao imprimir na tela e atrapalhar a demonstracao (evitar seg fault) */

	put_block(currentBlock.x, currentBlock.y);
}

int collision(int deslocX, int deslocY) {
	int i, j, origX, origY, dirX, dirY, x, y, check;
	
	origX = currentBlock.x;
	origY = currentBlock.y;

	if(currentBlock.direction == HORIZONTAL) {
		dirX = 1;
		dirY = 0;
	}
	else if(currentBlock.direction == VERTICAL) {
		dirX = 0;
		dirY = 1;
	}

	for(i = 0 ; i < currentBlock.size ; i++) {
		x = origX + (dirX * i) + deslocX;
		y = origY + (dirY * i) + deslocY;
		if(x >= 0 && x < LARGURA && y >= 0 && y < ALTURA) {
			if(game.field[x][y] != VAZIO) {
				check = 0;
				for(j = 0 ; j < currentBlock.size ; j++) {
					if(x == origX + (dirX * j) && y == origY + (dirY * j))
						check = 1;
				}
				if(check == 0)
					return 1;
			}
		}
		else 
			return 1;
	}

	return 0;
}

int move_block(int opt){

	int newX = currentBlock.x, newY = currentBlock.y;
	
	if(opt == KEY_DOWN){ /* move para baixo */ 
		while(!collision(0, 1)) {
			newY++;
			put_block(newX, newY);
			currentBlock.x = newX;
			currentBlock.y = newY;	
			usleep(5000);
		}
	}
	else if(opt == KEY_RIGHT){ /* move para direita */ 
		if(!collision(1, 0))
			newX++;	
	}
	else if(opt == KEY_LEFT){ /* move para esquerda */ 
		if(!collision(-1, 0))
			newX--;	
	}
	else{
		return FALSO;
	}
	
	if(newX != currentBlock.x || newY != currentBlock.y) {
		put_block(newX, newY);
		currentBlock.x = newX;
		currentBlock.y = newY;	
	}

	return 0;
}

int cut_this_line(int y){

	if(y < 5 || y > ALTURA){ /* Nao tem como o y ser menor que 5 ja que os bloco nao chegam até essa altura */
		return FALSO;
	}

	int x;
	for(x=0;x<LARGURA;x++)
		game.field[x][y] = 7; /* atribuiu a linha que sera cortada o valor 7, para que a proxima funcao "show_field" preencha-a de cor diferente indicando para o usuario que ela sera cortada */
	usleep(500000);
	for(;y>=1;y--)
		for(x=0;x<LARGURA;x++)
			game.field[x][y]=game.field[x][y-1]; /* Desce os blocos acima da linha cortada */

	return 0;
}

void any_complete_line(){
	int x, y, cnt;
	for(y = LIMITE; y < ALTURA; y++){
		cnt = 0;
		for(x = 0; x < LARGURA; x++)
			if(game.field[x][y] != VAZIO) cnt += 1;
		if(cnt == LARGURA) {	/* confere se o contador tem o tamanho da linha maxima */
			cut_this_line(y);
			game.points += 100;
		}
	}
}


/* TESTES ---------------------------------------------------------------------------------------------------------------------------------------- */

void teste_DT_LimiteInferiorTamanhoBloco(void){
	int resultado;
	new_block();
	resultado = currentBlock.size;
	CU_ASSERT(resultado > 0);
}

void teste_DT_LimiteSuperiorTamanhoBloco(void){
	int resultado;
	new_block();
	resultado = currentBlock.size;
	CU_ASSERT(resultado < 6);
}

void teste_DT_DirecaoBloco(void){
	int resultado;
	new_block();
	resultado = currentBlock.direction;
	CU_ASSERT(resultado == HORIZONTAL || resultado == VERTICAL);
}

void teste_DT_ColocarBlocoPassandoHorizontal(void){
	int resultado;
	resultado = put_block(LARGURA,0); /* O bloco nao pode passar da largura da matriz */
	CU_ASSERT(resultado == FALSO);
}

void teste_DT_ColocarBlocoPassandoVertical(void){
	int resultado;
	resultado = put_block(0,ALTURA); /* O bloco nao pode passar da altura da matriz */
	CU_ASSERT(resultado == FALSO);
}

void teste_DT_MoverBloco(void){
	int resultado;
	resultado = move_block('A'); /* 'A' não é uma tecla válida para mover o bloco */ 
	CU_ASSERT(resultado == FALSO);
}

void teste_DT_CortarLinha(void){
	int resultado;
	resultado = cut_this_line(4); /* Não existe linha para se cortar na altura 4 */ 
	CU_ASSERT(resultado == FALSO);
}

int main(){

	srand(time(NULL));
	
	CU_pSuite pSuite = NULL;

   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   pSuite = CU_add_suite("Testar funcoes do bloco", NULL, NULL);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   
   if ((NULL == CU_add_test(pSuite, "teste limite inferior", teste_DT_LimiteInferiorTamanhoBloco)) ||
       (NULL == CU_add_test(pSuite, "teste limite superior", teste_DT_LimiteSuperiorTamanhoBloco)) ||
       (NULL == CU_add_test(pSuite, "teste direcao do bloco", teste_DT_DirecaoBloco)) ||
       (NULL == CU_add_test(pSuite, "teste coloca bloco", teste_DT_ColocarBlocoPassandoHorizontal)) ||
       (NULL == CU_add_test(pSuite, "teste coloca bloco", teste_DT_ColocarBlocoPassandoVertical)) ||
       (NULL == CU_add_test(pSuite, "teste move bloco", teste_DT_MoverBloco)) ||
       (NULL == CU_add_test(pSuite, "teste corta linha", teste_DT_CortarLinha)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }


	CU_basic_set_mode(CU_BRM_VERBOSE);

	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();

}
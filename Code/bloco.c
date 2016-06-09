#include <ncurses.h>
#include <stdlib.h> 

#include "estruturas.h"	

int put_block(int newX, int newY) {
	int i;

	/* Condiçoes de entrada, o bloco nao pode passar o tamanho da matriz */

	if(newY > ALTURA || newY < 0){
		return FALSO;
	}

	if(newX > LARGURA || newX < 0){
		return FALSO;
	}

	/* Fim das condiçoes de entrada */

	for(i = 0; i < 4; i++)
		game.field[currentBlock.x + currentBlock.dot[i].x][currentBlock.y + currentBlock.dot[i].y] = VAZIO; /* Esvazia todas as posições na matriz que formam o bloco na sua posição atual */
		
	for(i = 0; i < 4; i++)
		game.field[newX + currentBlock.dot[i].x][newY + currentBlock.dot[i].y] = currentBlock.color; /*  Preenche todas as posições na matriz que formam o bloco na sua nova posição */

	return 0;
}

void new_block(){

	int c = 1 + rand() % 5, type = rand() % 7;

	while(c == currentBlock.color) c = 1 + rand() % 5; /* Mudar a cor do bloco em relação ao anterior */
	
	currentBlock.color = c;
	
	}
	switch(type) {
		case 0:	currentBlock.dot[i].x = 0;
				currentBlock.dot[i].y = 0;
				currentBlock.dot[i].x = 1;
				currentBlock.dot[i].y = 0;
				currentBlock.dot[i].x = 0;
				currentBlock.dot[i].y = 1;
				currentBlock.dot[i].x = 1;
				currentBlock.dot[i].y = 1;
				currentBlock.size = 2;
				break;
		case 1:	currentBlock.dot[i].x = 0;
				currentBlock.dot[i].y = 1;
				currentBlock.dot[i].x = 1;
				currentBlock.dot[i].y = 1;
				currentBlock.dot[i].x = 2;
				currentBlock.dot[i].y = 1;
				currentBlock.dot[i].x = 1;
				currentBlock.dot[i].y = 2;
				currentBlock.size = 3;
				break;
		case 2:	currentBlock.dot[i].x = 0;
				currentBlock.dot[i].y = 1;
				currentBlock.dot[i].x = 1;
				currentBlock.dot[i].y = 1;
				currentBlock.dot[i].x = 1;
				currentBlock.dot[i].y = 2;
				currentBlock.dot[i].x = 2;
				currentBlock.dot[i].y = 2;
				currentBlock.size = 3;
				break;
		case 3:	currentBlock.dot[i].x = 1;
				currentBlock.dot[i].y = 1;
				currentBlock.dot[i].x = 2;
				currentBlock.dot[i].y = 1;
				currentBlock.dot[i].x = 0;
				currentBlock.dot[i].y = 2;
				currentBlock.dot[i].x = 1;
				currentBlock.dot[i].y = 2;
				currentBlock.size = 3;
				break;
		case 4:	currentBlock.dot[i].x = 0;
				currentBlock.dot[i].y = 0;
				currentBlock.dot[i].x = 0;
				currentBlock.dot[i].y = 1;
				currentBlock.dot[i].x = 1;
				currentBlock.dot[i].y = 1;
				currentBlock.dot[i].x = 2;
				currentBlock.dot[i].y = 1;
				currentBlock.size = 2;
				break;
		case 5:	currentBlock.dot[i].x = 2;
				currentBlock.dot[i].y = 0;
				currentBlock.dot[i].x = 0;
				currentBlock.dot[i].y = 1;
				currentBlock.dot[i].x = 1;
				currentBlock.dot[i].y = 1;
				currentBlock.dot[i].x = 2;
				currentBlock.dot[i].y = 1;
				currentBlock.size = 2;
				break;
		case 6:	currentBlock.dot[i].x = 0;
				currentBlock.dot[i].y = 1;
				currentBlock.dot[i].x = 1;
				currentBlock.dot[i].y = 1;
				currentBlock.dot[i].x = 2;
				currentBlock.dot[i].y = 1;
				currentBlock.dot[i].x = 3;
				currentBlock.dot[i].y = 1;
				currentBlock.size = 4;
	}
	
	currentBlock.y = 0; /* A peça começa sempre no topo do campo */
	
	currentBlock.x = rand()%(LARGURA-currentBlock.size-1); /* A peça começa em uma posicao aletario em relaçao ao eixo x dependendo se ela é horizontal ou vertical */
	/* Na funcao acima verifica se a peça é vertical por que se for ela poderia entrar em qualquer posicao x, porem se ela for horizontal dependerá do tamanho para ela nao bater na parede */
	
	printw("x=%d\n", currentBlock.x); 
	put_block(currentBlock.x, currentBlock.y);
}

int collision(int deslocX, int deslocY) {
	int i, j, origX, origY, dirX, dirY, x, y, check;
	
	origX = currentBlock.x;
	origY = currentBlock.y;

	for(i = 0 ; i < 4 ; i++) {
		x = origX + currentBlock.dot[i].x + deslocX;
		y = origY + currentBlock.dot[i].y + deslocY;
		if(x >= 0 && x < LARGURA && y >= 0 && y < ALTURA) {
			if(game.field[x][y] != VAZIO) {
				check = 0;
				for(j = 0 ; j < 4 ; j++) {
					if((x == origX + currentBlock.dot[j].x) && (y == origY + currentBlock.dot[j].y))
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
		newY++;
		put_block(newX, newY);
		currentBlock.x = newX;
		currentBlock.y = newY;	
		show_field();
		usleep(5000);
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

int spin_block() {
	block aux1 = currentBlock, aux2;
	int i, j, check;

	for(i=0;i<4;i++) {
		aux1.dot[i].x = currentBlock.dot[i].y;
		aux1.dot[i].y = currentBlock.dot[i].x;
	}
	aux2 = aux1;
	for(i=0;i<4;i++)
		aux2.dot[i].x = currentBlock.size-1-aux2.dot.x;

	for(i=0;i<4;i++) {
		if(aux2.x + aux2.dot[i].x >= 0 && aux2.x + aux2.dot[i].x < LARGURA && aux2.y + aux2.dot[i].y >= 0 && aux2.y + aux2.dot[i].y < ALTURA)
			if(game.field[aux2.x + aux2.dot[i].x][aux2.y + aux2.dot[i].y] != VAZIO) {
				check = 0;
				for(j = 0 ; j < 4 ; j++)
					if((aux2.dot[i].x == currentBlock.dot[j].x) && (aux2.dot[i].y == currentBlock.dot[j].y))
						check = 1;
				if(check == 0)
					return 1;
			}
		else
			return 1;
	}

	currentBlock = aux2;

	return 0;
}

int cut_this_line(int y){

	if(y < 5 || y > ALTURA){ /* Nao tem como o y ser menor que 5 ja que os bloco nao chegam até essa altura */
		return FALSO;
	}

	int x;
	for(x=0;x<LARGURA;x++)
		game.field[x][y] = 7; /* atribuiu a linha que sera cortada o valor 7, para que a proxima funcao "show_field" preencha-a de cor diferente indicando para o usuario que ela sera cortada */
	show_field();
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
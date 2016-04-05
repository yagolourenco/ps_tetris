//	Trabalho Pratica 1                            |
//	Genaina - Programacao Sistematica             |
//	André Luiz de Moura Ramos Bittencourt         |
//	Claudio Segala Rodrigues Silva Filho          |
//	Anne Caroline de Assis Pereira                |
//	Hector Rocha Margittay                        |
// _______________________________________________|


// Bibliotecas --------------------------------------------------------------------------------------------------------------------------------------

#include<time.h> /* calcular o tempo */
#include<stdio.h> /* para entrada e saida padroes*/
#include<stdlib.h> 
#include<unistd.h> /* para a funcao getch_char e getch*/
#include<string.h> 
#include<termios.h> /* para a funcao getch_char e getch*/

// Defines ------------------------------------------------------------------------------------------------------------------------------------------

#define RESET "\x1b[0m"
#define KNRM  "\x1b[0m"
#define KRED  "\x1b[31m"
#define KGRN  "\x1b[32m"
#define KYEL  "\x1b[33m"
#define KBLU  "\x1b[34m"
#define KMAG  "\x1b[35m"
#define KCYN  "\x1b[36m"
#define KWHT  "\x1b[37m"
#define LARGURA 15
#define ALTURA 25
#define LIMITE 5
#define HORIZONTAL 0
#define VERTICAL 1
#define VAZIO 0

// Structs -------------------------------------------------------------------------------------------------------------------------------------------

typedef struct{
	int field[LARGURA][ALTURA], points;
	double duration;
} tetris;

typedef struct{
	int color, direction, size, x, y;
} block;

// Variaveis Globais ---------------------------------------------------------------------------------------------------------------------------------

tetris game;
block currentBlock;
int next_round = 1;

// Funcoes -------------------------------------------------------------------------------------------------------------------------------------------

void limpa_tela_legal(){
	system("clear || cls");
}

void limpa_buffer(){
  while(getchar()!='\n');
}

int getch(void) {
  int ch;
  struct termios oldt;
  struct termios newt;
  tcgetattr(STDIN_FILENO, &oldt); /*store old settings */
  newt = oldt; /* copy old settings to new settings */
  newt.c_lflag &= ~(ICANON | ECHO); /* make one change to old settings in new settings */
  tcsetattr(STDIN_FILENO, TCSANOW, &newt); /*apply the new settings immediatly */
  ch = getchar(); /* standard getchar call */
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt); /*reapply the old settings */
  return ch; /*return received char */
}

char getch_char(void) {
  int ch = getch();
  if(ch >= 0 && ch < 128)
	  return (char) ch;
  return 0;
}

void enter(){
  printf(" Aperte [enter] para ir ao MENU ");
  limpa_buffer();
  limpa_tela_legal();
}

int valido(char opt){
  if(opt == 'a' || opt == 'A' || opt == 's' || opt == 'S' || opt == 'd' || opt == 'D') return 0;
  return 1;
}

void tela_inicio(){
	limpa_tela_legal();
	printf(KBLU "______________  ______________  ______________  ___________    __________  ______________ \n" RESET);
	printf(KBLU "      |         |                     |         |          \\       ||      |              \n" RESET);
	printf(KBLU "      |         |                     |         |           |      ||      |              \n" RESET);
	printf(KBLU "      |         |_____________        |         |__________/       ||      |_____________ \n" RESET);
	printf(KBLU "      |         |                     |         |         \\        ||                   | \n" RESET);
	printf(KBLU "      |         |                     |         |          \\       ||                   | \n" RESET);
	printf(KBLU "      |         |_____________        |         |           \\  ____||____   ____________| \n" RESET);
	printf("\n\n");
	usleep(1500000);
}

void tela_fim(){
	limpa_tela_legal();
	printf(KRED "Vc pontuou %d em %lf\n"  RESET, game.points, game.duration);
	printf(KGRN "Parabens por ter chegado tao longe jovem padawan\n" RESET);
	printf(KGRN "Todo seu progresso foi inutil pois nao guardamos ranking ainda\n" RESET);
	printf(KGRN "Sinta-se livre de baixar um app de tetris decente\n" RESET);
	printf(KGRN "Feito por: programadores escravos da bolivia\n" RESET);
	printf(KGRN "Fazer o que?\n" RESET);
	printf(KGRN " ¯\\_(ツ)_/¯\n");
	usleep(500000);
}

void show_instructions(){
	limpa_tela_legal();
	printf(" Use as teclas a, s e d (pode usar CapsLock) para mover as pecas\n");
	usleep(4000000);
}
 
//MODULO BLOCO___________________________________________________________________________________________
int obstaculo(int dx, int dy) {
	int i;
	
	for(i = 0 ; i < currentBlock.size ; i++) {
		if(currentBlock.x + dx >= 0 &&
		   currentBlock.x + dx < LARGURA &&
		   currentBlock.y + dy >= 0 &&
		   currentBlock.y + dy < ALTURA 0) {
			if(game.field[currentBlock.x+dx][currentBlock.y + dy] != VAZIO) {
		
			}
		}
		else 
			return 0;
	}

	return 1;
}

void move(char opt){
	if(opt == 's' || opt == 'S'){ /* move para baixo */ 
		
	}
	else if(opt == 'd' || opt == 'D'){ /* move para direita */ 
		
	}
	else if(opt == 'a' || opt == 'S'){ /* move para esquerda */ 

	}
}

void cut_this_line(int y){
	int x;
	for(;y>=LIMITE;y--)
		for(x=0;x<LARGURA;x++)
			game.field[x][y]=game.field[x][y-1];
}


int any_complete_line(){
	int x, y, p = 0, cnt;
	for(y = LIMITE; y < ALTURA; y++){
		cnt = 0;
		for(x = 0; x < LARGURA; x++)
			if(game.field[x][y] == '1') cnt += 1;
		if(cnt == LARGURA){	/* confere se o contador tem o tamanho da linha maxima*/
			cut_this_line(y);
			p += 100;
		}
	}
	fall('s');
	return p;
}

//MODULO TELA________________________________________________________________________________________

void show_field(){
	int x, y, i;
	limpa_tela_legal();
    printf(" Pontuacao: %d\n\n", game.points++);
    for(y = 0; y < ALTURA; y++){
    	if(i == LIMITE)	printf(KRED "-------------------------------------------------------------\n" RESET);
        else 		printf(KYEL "-------------------------------------------------------------\n" RESET);
        for(x = 0; x < LARGURA; x++){
        	if(game.field[x][y] == 0)
            	printf(KYEL "|" RESET KCYN "   " RESET);
            else
            	printf(KYEL "|" RESET KCYN " * " RESET);
        }
        printf(KYEL "|\n");
    }
    printf("-------------------------------------------------------------\n" RESET);
    usleep(10000);
}

// MODULO ENGINE_________________________________________________________________________________

void prepare_field(){
	memset(game.field, 0, sizeof(int)*LARGURA*ALTURA);
	game.points = 0;
}

int gameOver(){
	if(currentBlock.y < LIMITE) return 0;
	return 1;
}

void putBlock(){
	currentBlock.color = rand()%4;
	currentBlock.direction = rand() % 2;
	currentBlock.size = rand() % 3 + 3;
	currentBlock.y = 0;
	currentBlock.x = rand()%LARGURA-(currentBlock.position?0:currentBlock.size);
	/* implementar desenha na matriz */
}

char input() {
	char opt;
	do { opt = getch_char(); }
	while( valido(opt) );
	return opt;
}

void game_on(){
	clock_t t_begin = clock() / CLOCKS_PER_SEC, t_end;
	prepare_field();
	show_instructions();
	do{
		if(next_round == 1){
			putBlock(); 
			next_round = 0;
		}
		limpa_tela_legal();
		show_field();
		move(input());
		usleep(800000);
		game.points += any_complete_line();
	}while(gameOver(););
	t_end = clock() / CLOCKS_PER_SEC;
	/* De acordo com o dito pelo IME em uma de suas apostilas, esse metodo so consegue guardar ate 35 minutos*/
	game.duration = t_end - t_begin;
}

int main(){
	srand( time(NULL) );
	tela_inicio();
	char a;
	printf(KBLU "1 - Jogar\n" RESET);
	printf(KBLU "2 - Sair\n" RESET);
	do { 
		a = getch_char(); 
		if(a == '1' || a == '2') break;
	}while(1);
	if(a == '1') {
	 	game_on();
		tela_fim();
	}
	return 0;
}

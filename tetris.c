//	Trabalho Pratica 1
//	Genaina - Programacao Sistematica
//	Claudio Segala Rodrigues Silva Filho
//	Anne Caroline de Assis Pereira
//	Andre Bittencourt? (eu esqueci seu sobrenome)
//	Hector Marggitay
//


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

// Structs -------------------------------------------------------------------------------------------------------------------------------------------

typedef struct{
	int field[25][15], points, over;
	double duration;
} tetris;

typedef struct{
	int position, size, x, y;
} block;

// Variaveis Globais ---------------------------------------------------------------------------------------------------------------------------------

tetris game;
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
  int ch = getch;
  if(ch >= 0 && ch < 128)
	  return (char) ch;
  retunr 0;
}

void enter(){
  printf(" Aperte [enter] para ir ao MENU ");
  limpa_buffer();
  limpa_tela_legal();
}

int valido(char x){
  if(x == 'a' || x == 'A' || x == 's' || x == 'S' || x == 'd' || x == 'D') return 0;
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

void fall(char opt){
	if(opt == 's'){ /* move para baixo */ 
		if( obstaculo() ){
			if(currentBlock.position == VERTICAL){ /*  */
				
			}
			else{
				
			}
		}
		else{
			next_round = 1;
		}
	}
	else if(opt == 'd'){ /* move para direita */ 
		if( obstaculo() ){
			if(currentBlock.position == VERTICAL){ /*  */
				
			}
			else{
				
			}
		}
	}
	else if(opt == 'a'){ /* move para esquerda */ 
		if( obstaculo() ){
			if(currentBlock.position == VERTICAL){ /*  */
				
			}
			else{
				
			}
		}
	}
}

void cut_this_line(int x){
	for (int i = 0; i < 15; ++i){
		game.field[x][i] = 0;
	}
	for (int i = x; i >= 0; --i){
		for (int j = 0; j < 25; ++j){
			game.field[i][j] = game.field[i+1][j];
		}
	}


}

/* verifica se existe alguma linha completa */
int any_complete_line(){
	int i, j, p = 0, cnt;
	for(i = 0; i < 25; i++){
		cnt = 0;
		for(j = 0; j < 15; j++)
			if(game.field[i][j] == '1') cnt += 1;
		if(cnt == 15){	/* confere se o contador tem o tamanho da linha maxima*/
			cut_this_line(i);
			p += 100;
		}
	}
	fall('s');
	return p;
}

void show_table(){
	int i, j;
	limpa_tela_legal();
    printf(" Pontuacao: %d\n\n", game.points++);
    for(i = 0; i < 25; i++){
    	if(i == 5)	printf(KRED "-------------------------------------------------------------\n" RESET);
        else 		printf(KYEL "-------------------------------------------------------------\n" RESET);
        for(j = 0; j < 15; j++){
        	if(game.field[i][j] == 0)
            	printf(KYEL "|" RESET KCYN "   " RESET);
            else
            	printf(KYEL "|" RESET KCYN " * " RESET);
        }
        printf(KYEL "|\n");
    }
    printf("-------------------------------------------------------------\n" RESET);
    usleep(10000);
}

void start(){
	char opt;
	block currentBlock;
	do{
		if(next_round == 1){
			currentBlock.position = rand() % 2;
			currentBlock.size = rand() % 3 + 3;
			putBlock(currentBlock); /* chama a primeira peca */
			next_round = 0;
		}
		limpa_tela_legal();
		show_table();
		do{ opt = getch_char(); }
		while( valido(opt) );
		fall(opt);
		usleep(800000);
		game.points += any_complete_line();
	}while(game.over);
}

void prepare_field(){
	memset(game.field, 0, sizeof(int)*15*25);
	game.over = 1;
	game.points = 0;
}

void game_on(){
	clock_t t_begin = clock() / CLOCKS_PER_SEC, t_end;
	prepare_field();
	show_instructions();
	start();
	t_end = clock() / CLOCKS_PER_SEC;
	/* De acordo com o dito pelo IME em uma de suas apostilas, esse metodo so consegue guardar ate 35 minutos*/
	game.duration = t_end - t_begin;
	tela_fim();
}

/*Hector faz essa parte*/
void menu(){
	char a;
	printf(KBLU "1 - Jogar\n" RESET);
	printf(KBLU "2 - Sair\n" RESET);
	do { 
		a = getch_char(); 
		if(a == '1' || a == '2') break;
	}while(1);
	if(a == '1')	game_on();
}

int main(){
	srand( time(NULL) );
	tela_inicio();
	menu();
	return 0;
}
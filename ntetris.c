//	Programacao Sistematica	                          |
//	Trabalho Pratico 1                                |
//	Professor(a): Genaina                             |
//	Alunos:                                           |
//	  André Luiz de Moura Ramos Bittencourt           |
//	  Claudio Segala Rodrigues Silva Filho            |
//	  Anne Caroline de Assis Pereira                  |
//	  Hector Rocha Margittay                          |
// _______________________________________________________|


// Bibliotecas --------------------------------------------------------------------------------------------------------------------------------------

#include<ncurses.h>
#include<time.h> /* calcular o tempo */
#include<stdlib.h> 
#include<unistd.h> /* para a funcao getch_char e getch*/
#include<string.h> 
#include<termios.h> /* para a funcao getch_char e getch*/

// Defines ------------------------------------------------------------------------------------------------------------------------------------------

#define LARGURA 15
#define ALTURA 25
#define LIMITE 5
#define HORIZONTAL 0
#define VERTICAL 1
#define VAZIO 0

// Structs -------------------------------------------------------------------------------------------------------------------------------------------

typedef struct{
	int field[LARGURA][ALTURA], points;
	struct timespec t_start, t_stop;
	double duration;
} tetris;

typedef struct{
	int color, direction, size, x, y;
} block;

// Variaveis Globais ---------------------------------------------------------------------------------------------------------------------------------

tetris game;
block currentBlock;

// Funcoes -------------------------------------------------------------------------------------------------------------------------------------------

// MODULO TELA________________________________________________________________________________________________________________________________________

void set_color() {
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);


void show_title(){
	clear();
	move(0,0);
	printw(" _____   _____   _____   _____   _   _____ \n");
	printw("|_|_|_| |_|_|_| |_|_|_| |_|_|_| |_| |_|_|_|\n");
	printw("  |_|   |_|___    |_|   |_|     |_| |_|___ \n");
	printw("  |_|   |_|_|_|   |_|   |_|     |_| |_|_|_|\n");
	printw("  |_|   |_|___    |_|   |_|     |_|  ___|_|\n");
	printw("  |_|   |_|_|_|   |_|   |_|     |_| |_|_|_|\n");
	refresh();
}

void show_menu() {
	printw(" ________________\n");
	printw("|                |\n");
	printw("| [1][  Jogar  ] |\n");
	printw("|________________|\n");
	printw(" ________________\n");
	printw("|                |\n");
	printw("| [2][  Sair   ] |\n");
	printw("|________________|\n");
}

void show_instructions(){
	printw(" Use as teclas [A], [S] e [D] (pode usar CapsLock) para mover as pecas\n\n");
	printw("                   Aperte [ENTER] para continuar\n");
}

void show_field(){
	int x, y;
    printw(KBLC BGWHT" Pontuacao: %d                    \n" RESET, game.points);
    for(x = 0; x < LARGURA+2; x++)
    	printw(BGWHT "  ");
    printw(RESET "\n");
    for(y = 0; y < ALTURA; y++){
    	printw(BGWHT "  ");
		for(x = 0; x < LARGURA; x++) {
			if(game.field[x][y] == VAZIO) {
				if(y == LIMITE)	
					printw(KWHT BGBLC "--");
				else 
					printw(BGBLC "  ");
			}
			else {
				attr_set(A_BOLD | COLOR_SET(game.field[x][y])));
				printw("[]");
			}
		}
		printw(BGWHT "  \n" RESET);
    }
    for(x = 0; x < LARGURA+2; x++)
    	printw(BGWHT "  ");
    printw(RESET "\n");
}

void show_end(){
	attrset(COLOR_SET(1));
	printw("Voce fez %d pontos em %d minutos e %d segundos\n"  RESET, game.points, (int)(game.duration/60), (int)(game.duration-(game.duration/60)));
	usleep(2000000);
	attrset(COLOR_SET(2));
	printw("Parabens por ter chegado tao longe jovem padawan\n");
	usleep(2000000);
	printw("Todo seu progresso foi inutil pois nao guardamos ranking ainda\n" );
	usleep(2000000);
	printw("Sinta-se livre de baixar um app de tetris decente\n");
	usleep(2000000);
	printw("Feito por: programadores escravos da bolivia\n");
	usleep(2000000);
	printw("Fazer o que?\n");
	printw(" ¯\\_(ツ)_/¯\n");
}

// MODULO BLOCO_______________________________________________________________________________________________________________________________________

void put_block(int newX, int newY) {
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
		game.field[currentBlock.x + (dirX * i)][currentBlock.y + (dirY * i)] = VAZIO;
		
	for(i = 0; i < currentBlock.size; i++)
		game.field[newX + (dirX * i)][newY + (dirY * i)] = currentBlock.color;
}

void new_block(){
	int c = 1 + rand() % 5;

	while(c == currentBlock.color) c = 1 + rand() % 5;
	currentBlock.color = c;
	currentBlock.direction =rand() % 2;
	currentBlock.size = rand() % 3 + 3;
	currentBlock.y = 0;
	currentBlock.x = rand()%(LARGURA-(currentBlock.direction?0:currentBlock.size-1)); printw("x=%d\n", currentBlock.x);
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

void move_block(char opt){
	int newX = currentBlock.x, newY = currentBlock.y;
	
	if(opt == KEY_DOWN){ /* move para baixo */ 
		while(!collision(0, 1)) {
			newY++;
			put_block(newX, newY);
			currentBlock.x = newX;
			currentBlock.y = newY;	
			show_field();
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
	
	if(newX != currentBlock.x || newY != currentBlock.y) {
		put_block(newX, newY);
		currentBlock.x = newX;
		currentBlock.y = newY;	
	}
}

void cut_this_line(int y){
	int x;
	for(x=0;x<LARGURA;x++)
		game.field[x][y] = 7;
	show_field();
	usleep(500000);
	for(;y>=1;y--)
		for(x=0;x<LARGURA;x++)
			game.field[x][y]=game.field[x][y-1];
}

void any_complete_line(){
	int x, y, cnt;
	for(y = LIMITE; y < ALTURA; y++){
		cnt = 0;
		for(x = 0; x < LARGURA; x++)
			if(game.field[x][y] != VAZIO) cnt += 1;
		if(cnt == LARGURA) {	/* confere se o contador tem o tamanho da linha maxima*/
			cut_this_line(y);
			game.points += 100;
		}
	}
}

// MODULO ENGINE______________________________________________________________________________________________________________________________________

void init_ncurses() {
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	set_color();
	keypad(stdscr, TRUE);
}

void start() {
	show_title();
	usleep(2000000);
}

void get_enter() {
	while(getch()!='\n');
}

void start_clock() {
	clock_gettime(CLOCK_REALTIME, &(game.t_start));
}

void set_game(){
	srand(time(NULL));
	memset(game.field, VAZIO, sizeof(int)*LARGURA*ALTURA);
	game.points = 0;
}

int game_over(){
	if(currentBlock.y < LIMITE) return 1;
	return 0;
}

void stop_clock() {
	clock_gettime(CLOCK_REALTIME, &(game.t_stop));
}

void get_duration() {
	stop_clock();
	game.duration = (game.t_stop.tv_sec - game.t_start.tv_sec) +
					((game.t_stop.tv_nsec - game.t_start.tv_nsec)/1E9);
}

void game_on(){
	set_game();
	show_instructions();
	get_enter();
	start_clock();
	do{
		new_block();
		do {
			show_field();
			move_block(getch());
		} while(!collision(0,1));
		show_field();
		any_complete_line();
	} while(!game_over());
	get_duration();
	show_end();
	get_enter();
}

int main() {
	char opt;
	
	init_ncurses();
	start();
	get_enter();
	do {
		show_menu();
		do { 
			opt = getch();
		}while(opt != '1' && opt != '2');
		if(opt == '1') {
		 	game_on();
		}
	} while(opt != '2');
	endwin();
	
	return 0;
}
#include<ncurses.h>
#include<time.h> /* calcular o tempo */
#include<stdlib.h> 
#include<unistd.h> /* para a funcao getch_char e getch*/
#include<string.h> 
#include<termios.h> 

#include "Estruturas.h"

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

void set_game(){
	srand(time(NULL));
	memset(game.field, VAZIO, sizeof(int)*LARGURA*ALTURA);
	game.points = 0;
}

void start_clock() {
	clock_gettime(CLOCK_REALTIME, &(game.t_start));
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
	create_border();
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

int main(){
	return 0;
}
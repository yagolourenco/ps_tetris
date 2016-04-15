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

/* ENGINE.C ------------------------------------------------------------------------------------------------------------------------------- */

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

/* TESTES ---------------------------------------------------------------------------------------------------------------------------------------- */



void teste_DT_FimdeJogo(void){
	currentBlock.y = 4;          /* Jogo so acaba quando uma peça passa do limite superior do campo, no caso 5 */
	int resultado;
	resultado = game_over();
	CU_ASSERT(resultado == 1);
}









int main(){

	srand(time(NULL));
	
	CU_pSuite pSuite = NULL;

   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   pSuite = CU_add_suite("Testar funcoes da engine", NULL, NULL);
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
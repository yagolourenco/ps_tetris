#include "estruturas.h"

/* RANK.C ----------------------------------------------------------------------------------------------------------------------------- */

void sortRank(){
	int cnt;
	do{
		cnt = 0;
		int i;
		for(i = 0; i < 5; i++)
			if(ranked[i].points < ranked[i+1].points || (ranked[i].points == ranked[i+1].points && ranked[i].time < ranked[i+1].time) ){
				player aux;
				aux = ranked[i];
				ranked[i] = ranked[i+1];
				ranked[i+1] = aux;
				cnt++;
			}	
	}while(cnt);
}

void newRankFile(){
	int i;
	FILE *Rank = fopen("ranking.txt", "w+");

	if(Rank == NULL){
		printw("Falha ao criar arquivo\n");
		return;
	}

	for(i = 0; i < 5; i++)
		fprintf(Rank, "%4s %d %lf\n", ranked[i].name, ranked[i].points, ranked[i].time);
}

bool isItRanked(){
	int i = 0;
	player aux = ranked[5];
	FILE *Rank = fopen("ranking.txt", "r"); 	// r é para leitura

	if(Rank == NULL){
		Rank = fopen("ranking.txt", "w+");		//cria arquivo
		fprintf(Rank, "%4s %d %lf\n", "Hect", 100, 10.0);
		fprintf(Rank, "%4s %d %lf\n", "Cris", 100, 9.0);
		fprintf(Rank, "%4s %d %lf\n", "Cdio", 100, 8.0);
		fprintf(Rank, "%4s %d %lf\n", "Bugr", 100, 7.0);
		fprintf(Rank, "%4s %d %lf\n", "adre", 0, 500.0);
		fprintf(Rank, "%4s %d %lf\n", ranked[5].name, ranked[5].points, ranked[5].time);
	}

	while(!feof(Rank)){
		fscanf(Rank, "%4s %d %lf\n", ranked[i].name, &ranked[i].points, &ranked[i].time); // le enquanto nao for fim de arquivo
		i++;
	}

	sortRank();

	// Verifica se o último player continuar o mesmo
	if(strcmp(ranked[5].name, aux.name) == 0  &&
			  ranked[5].points == aux.points  &&
			  ranked[5].time == aux.time )
		return false;
	return true;
}

void show_rank(){
	clear();
	printw("Ranking:\n");
	int i;
	for(i = 0; i < 5; i++)	printw("%d. %10s - %10d - %.0lf\n", i+1, ranked[i].name, ranked[i].points, ranked[i].time);
	printw("\n\n Press [enter] to leave.");
	refresh();
	while(getch() != '\n'); // loop até pegar um [enter]
}

void rank(){

	char a;

	clear();

	printw("Diga vos seu nome!\nConsigo ler um nome de até 3 caracteres.\n >");
	
	scanw("%4s",ranked[5].name);

	ranked[5].points = game.points;

	ranked[5].time = game.duration;

	if(isItRanked()) // pontuação for maior que a do ultimo rankeado no txt
		show_rank();
	else {
		clear();
		printw("Me desculpe %s, mas sua pontuação não foi alta o suficiente : ", ranked[5].name);
		refresh();
	}
}

/* TESTES ---------------------------------------------------------------------------------------------------------------------------------------- */

// esses testes ainda nao estao implementados

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

void teste_DT_TamanhoPeca(void){
	new_block();
	int resultado;
	resultado = currentBlock.size; 
	CU_ASSERT(resultado <=5 && resultado >= 3);
}

void teste_DT_LimitesLaterais(void){
	new_block();
	int resultado;
	resultado = currentBlock.x; 
	CU_ASSERT(resultado < 15 && resultado >= 0);
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
       (NULL == CU_add_test(pSuite, "teste corta linha", teste_DT_CortarLinha)) ||
       (NULL == CU_add_test(pSuite, "teste tamanho da peca", teste_DT_TamanhoPeca)) ||
       (NULL == CU_add_test(pSuite, "teste limite lateral", teste_DT_LimitesLaterais)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }


	CU_basic_set_mode(CU_BRM_VERBOSE);

	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();

}
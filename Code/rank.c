// RESOLVE 5
#include "estruturas.h"

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
	
	FILE *arq = fopen("ranking.txt", "w+");

	if(arq == NULL){
		printw("Falha ao criar arquivo\n");
		return;
	}

	int i;

	for(i = 0; i < 5; i++){
		fprintf(arq , "%s\n", ranked[i].name);
		fprintf(arq , "%d\n", ranked[i].points);
		fprintf(arq , "%lf\n", ranked[i].time);
	}
}

bool isItRanked(){
	
	FILE *Rank = fopen("ranking.txt", "r"); 	// r é para leitura

	if(Rank == NULL){
		Rank = fopen("ranking.txt", "w+");		//cria arquivo
		fprintf(Rank, "%s\n",ranked[5].name);
		fprintf(Rank , "%d\n", ranked[5].points);
		fprintf(Rank , "%lf\n", ranked[5].time);
		
		return true;
	}
	
	int i;

	i = 0;

	while(fscanf(Rank, "%[^\n] ", ranked[i].name)){ // le enquanto nao for fim de arquivo
				
		fscanf(Rank, "%d ", &ranked[i].points);

		fscanf(Rank, "%lf ", &ranked[i].time);

		i++;
	}

	player aux;

	aux = ranked[5];

	sortRank();

	if(strcmp(ranked[5].name,aux.name) == 0    &&
				ranked[5].points == aux.points &&
				ranked[5].time == aux.time ) // se o ultimo player continuar la em baixo
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
	
	scanw("%s",ranked[5].name);

	ranked[5].points = game.points;

	ranked[5].time = game.duration;

	if(isItRanked()){ // pontuação for maior que a do ultimo rankeado no txt
		show_rank();
	}
	else {
		clear();
		printw("Me desculpe %s, mas sua pontuação não foi alta o suficiente : ", ranked[5].name);
		refresh();
	}
}

#include "estruturas.h"

// Bubblesort 
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

// Atualiza o arquivo ranking.txt
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
		fprintf(Rank, "%4s %d %lf\n", "Hect", 0, 0.0);
		fprintf(Rank, "%4s %d %lf\n", "Cris", 0, 0.0);
		fprintf(Rank, "%4s %d %lf\n", "Cdio", 0, 0.0);
		fprintf(Rank, "%4s %d %lf\n", "Bugr", 0, 0.0);
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
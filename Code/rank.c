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

	fclose(Rank);
	Rank = NULL;
}

void readFile(FILE* Rank){
	int i = 0;
	while(!feof(Rank)){
		fscanf(Rank, "%4s %d %lf\n", ranked[i].name, &ranked[i].points, &ranked[i].time); // le enquanto nao for fim de arquivo
		i++;
	}
}

void fillFile(FILE* Rank){
	fprintf(Rank, "%4s %d %lf\n", "Hect", 0, 0.0);
	fprintf(Rank, "%4s %d %lf\n", "Cris", 0, 0.0);
	fprintf(Rank, "%4s %d %lf\n", "Cdio", 0, 0.0);
	fprintf(Rank, "%4s %d %lf\n", "Bugr", 0, 0.0);
	fprintf(Rank, "%4s %d %lf\n", ranked[5].name, ranked[5].points, ranked[5].time);

	strcpy(ranked[0].name,"Hect");
	ranked[0].points = 0;
	ranked[0].time = 0.0;

	strcpy(ranked[1].name,"Cris");
	ranked[1].points = 0;
	ranked[1].time = 0.0;

	strcpy(ranked[2].name,"Cdio");
	ranked[2].points = 0;
	ranked[2].time = 0.0;

	strcpy(ranked[3].name,"Bugr");
	ranked[3].points = 0;
	ranked[3].time = 0.0;

	strcpy(ranked[4].name, ranked[5].name);
	ranked[4].points = ranked[5].points;
	ranked[4].time = ranked[5].time;


}

bool isItRanked(){
	player aux = ranked[5];
	FILE *Rank = fopen("ranking.txt", "r"); 	// r é para leitura

	if(Rank == NULL){
		Rank = fopen("ranking.txt", "w+");		//cria arquivo
		fillFile(Rank);
	}

	readFile(Rank);
	sortRank();
	fclose(Rank);
	Rank = NULL;

	// Verifica se o último player continuar o mesmo
	if(strcmp(ranked[5].name, aux.name) == 0  &&
			  ranked[5].points == aux.points  &&
			  ranked[5].time == aux.time )
		return false;
	return true;
}

void show_rank(){
	FILE *Rank = fopen("ranking.txt", "r");
	if(Rank == NULL){
		Rank = fopen("ranking.txt", "w+");		//cria arquivo
		fillFile(Rank);
	}
	readFile(Rank);
	fclose(Rank);
	Rank = NULL;
	clear();
	printw("Ranking:\n");
	int i;
	for(i = 0; i < 5; i++)	printw("%d. %4s - %10d - %.0lf\n", i+1, ranked[i].name, ranked[i].points, ranked[i].time);
	printw("\n\n Press [enter] to GO TO HELL.");
	refresh();
	while(getch() != '\n'); // loop até pegar um [enter]
}

void rank(){
	char a;

	clear();
	printw("Diga vos seu nome!\nConsigo ler um nome de até 4 caracteres.\n >");
	scanw("%4s",ranked[5].name);
	ranked[5].points = game.points;
	ranked[5].time = game.duration;

	if(isItRanked()) // pontuação do jogador atual for maior que a do ultimo rankeado no txt
		show_rank();
	else {
		clear();
		printw("Me desculpe %s, mas sua pontuação não foi alta o suficiente : ", ranked[5].name);
		refresh();
	}
}
// RESOLVE 5
#include "estruturas.h"

void sortRank(){
	int cnt;
	do{
		cnt = 0;
		for(int i = 0; i < 5; i++)
			if(ranked[i].points < ranked[i+1].points || (ranked[i].points == ranked[i+1].points && ranked[i].time > ranked[i+1].time) ){
				player aux;
				aux = ranked[i];
				ranked[i] = ranked[i+1];
				ranked[i+1] = aux;
				cnt++;
			}	
	}while(cnt);
}

void newRankFile(){
	
	FILE *arq = fopen("ranking.txt", "wb+");

	if(arq == NULL){
		printf("Falha ao criar arquivo\n");
		return 0;
	}

	for(int i = 0; i < 5; i++){
		fprintf(arq , "%s\n", v[i].name);
		fprintf(arq , "%d\n", v[i].points);
		fprintf(arq , "%lf\n", v[i].time);
	}

}

bool isItRanked(){
	FILE *Rank = fopen("ranking.txt", "r"); 	// r é para leitura
	if(Rank == NULL){
		Rank = fopen("ranking.txt", "w");		//cria arquivo
		for(int i = 0; i < 6; i++){
			if(i == 0)		ranked[i].name = "QUEM";
			else if(i == 1)	ranked[i].name = "SERA";
			else if(i == 2)	ranked[i].name = "O   ";
			else if(i == 3)	ranked[i].name = "PRIMEIRO";
			else if(i == 4)	ranked[i].name = "MITO?";
			else 			ranked[i].name = "hehehehehe";
			ranked[i].points = 0;
			ranked[i].time = 0;
		}
		newRankFile();
	}
	for(int i = 0; i < 5, i++){
		
		fscanf(Rank, "%[^\n] ", &v[i].name);
		
		fscanf(Rank, "%d ", &v[i].points);

		fscanf(Rank, "%lf ", &v[i].time);

	}

	ranked[6].name = currentPlayer.name;
	ranked[6].points = currentPlayer.points;
	ranked[6].time = currentPlayer.time;
	sortRank();
	if( strcomp(ranked[6].name == currentPlayer.name)    &&
				ranked[6].points == currentPlayer.points &&
				ranked[6].time == currentPlayer.time ) // se o ultimo player continuar la em baixo
		return False;
	return True;
}

void show(){
	printf("Ranking:\n");
	for(int i = 0, i < 5; i++)	printf("%d. %10s - %10d - %.0lf\n", i+1, ranked[i].name, ranked[i].points, ranked[i].time);
	printf("\n\n Press [enter] to leave.");
	while(getchar() != '\n'); // loop até pegar um [enter]
}

void rank(){
	char a;
	if(isItRanked()){ // pontuação for maior que a do ultimo rankeado no txt
		do{
			printf("Diga vos seu nome!\nConsigo ler um nome de até 10 caracteres.\n >");
			scanf("%4s", currentPlayer.name);
			limpa_tela();
			printf("Seu nome é %s?\n", currentPlayer.name);
			printf("Aperte [Y/y] para confirmar.\n");
			a = getchar();
			limpa_tela();
		}while(a != 'Y' || a != 'y');
		newRankFile(); // modifica o rank atual para o novo
	}
	show_rank();
}
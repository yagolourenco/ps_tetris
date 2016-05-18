//	Programacao Sistematica	                          |
//	Trabalho Pratico 1                                |
//	Professor(a): Genaina                             |
//	Alunos:                                           |
//	  André Luiz de Moura Ramos Bittencourt           |
//	  Claudio Segala Rodrigues Silva Filho            |
//	  Anne Caroline de Assis Pereira                  |
//	  Hector Rocha Margittay                          |
// ___________________________________________________|

/* Ranking */

typedef struct{
	char name[4]; // máximo de caracteres para o nome do player é 3
	int points;
	double time;
} player;

void rank(){
	int invalido = 1;
	char a;
	player currentPlayer;
	limpa_tela(); // a ser substituido por alguma função do Ncurses
	if() // pontuação for maior que a do ultimo rankeado no txt
		do{
			printf("Diga a nos seu nome\nSo é possível ter um nome de até 3 caracteres.\n >");
			scanf("%3s", currentPlayer.name);
			limpa_tela();
			printf("Seu nome é %s?\n", currentPlayer.name);
			printf("Aperte [Y/y] para confirmar.\n");
			a = getchar();
			if(a == 'Y' || a == 'y')
				invalido--;
		}while(invalido);
		
}


/* -o- */

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
	rank();
	return 0;
}

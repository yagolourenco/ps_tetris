#define LARGURA 15
#define ALTURA 25
#define LIMITE 5
#define HORIZONTAL 0
#define VERTICAL 1
#define VAZIO 0
#define FALSO 2

typedef struct{
	int field[LARGURA][ALTURA], points;
	struct timespec t_start, t_stop;
	double duration;
} tetris;

typedef struct{
	int color, direction, size, x, y;
} block;

typedef struct{
	char name[11]; 	// máximo de caracteres para o nome do player é 10
	int points;		// RESOLVE 1
	double time;
} player;

tetris game;			// grava as informações do jogo atual
block currentBlock;		// bloco atual
player 	currentPlayer, 	// jogador atual
		ranked[6]; 		// os 5 rankeados + o atual
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

tetris game;
block currentBlock;

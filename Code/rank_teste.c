#include "estruturas.h"

/* RANK.C ----------------------------------------------------------------------------------------------------------------------------- */



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
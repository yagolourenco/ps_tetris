#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Bloco.h"
#include "Estruturas.h"


void teste_DT_LimiteInferiorTamanhoBloco(void){
	int resultado;
	void new_block();
	resultado = currentBlock.size;
	CU_ASSERT(resultado > 0);
}

void teste_DT_LimiteSuperiorTamanhoBloco(void){
	int resultado;
	void new_block();
	resultado = currentBlock.size;
	CU_ASSERT(resultado < 6);
}

void teste_DT_DirecaoBloco(void){
	int resultado;
	void new_block();
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


void Add_Suit_Testes(void){
	
	CU_pSuite pSuite = NULL;

	pSuite = CU_add_suite ("Testar funcoes do bloco", NULL, NULL);

	CU_ADD_TEST(pSuite, "teste_DT_LimiteInferiorTamanhoBloco");
	CU_ADD_TEST(pSuite, "teste_DT_LimiteSuperiorTamanhoBloco");
	CU_ADD_TEST(pSuite, "teste_DT_ColocarBlocoPassandoHorizontal");
	CU_ADD_TEST(pSuite, "teste_DT_ColocarBlocoPassandoVertical");
	CU_ADD_TEST(pSuite, "teste_DT_MoverBloco");
	CU_ADD_TEST(pSuite, "teste_DT_CortarLinha");

	return;

}

main(){
	
	if(CUE_SUCESS != CU_initialize_registry()){
		return CU_get_error();
	}

	Add_Suite_Teste();
	CU_basic_set_mode(CU_BRM_VERBOSE);

	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();

}
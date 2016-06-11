

```
========================================================================================================
                            _____   _____   _____   _____   _   _____
                           |_|_|_| |_|_|_| |_|_|_| |_|_|_| |_| |_|_|_|
                             |_|   |_|___    |_|   |_|     |_| |_|___
                             |_|   |_|_|_|   |_|   |_|     |_| |_|_|_|
                             |_|   |_|___    |_|   |_|     |_|  ___|_|
                             |_|   |_|_|_|   |_|   |_|     |_| |_|_|_|  versão 2.0

========================================================================================================
```


## Descrição
	
Trabalho da matéria de Programação Sistemática. Nele seria necessário construir uma versão simples do famoso jogo Tetris com a utilização de ncurses, makefile e usar frameworks para criação da documentação e dos testes.  
Requerimentos:   

+ Sistema operacional baseado em Linux (este programa foi testado no Ubuntu).
+ Biblioteca Ncurses (use o comando ```sudo apt-get install libncurses5-dev``` caso ainda não tenha instalado).
+ Splint para confirmar a não existência de erros no programa.

## Execução

Execute o comando ```make``` no terminal para instalar o programa.
Execute o comando ```./tetris``` para iniciar o programa.

## Comandos Do Jogo

```
	[^] --------> gira a peça
 [<][v][>]------> move a peça para a direita
  |  '----------> move a peça para baixo
  '-------------> move a peça para a esquerda
```

## Execução dos Testes

Dado que na execução do programa o comando ```make``` foi executado basta executar o comando ```./testebloco``` para iniciar o teste no módulo bloco e o comando ```./testeengine``` para iniciar o teste do módulo engine
Requerimentos CUnit 2.1.2 (Siga as instrições nesse [site](https://netbeans.org/kb/docs/cnd/c-unit-test.html?print=yes#linux) caso não tenha instalado).  


## Membros

+ André Luiz de Moura Ramos Bittencourt
+ Claudio Segala Rodrigues Silva Filho
+ Hector Rocha Margittay
+ Yago Pablo Lourenço Vaz

> Written with [StackEdit](https://stackedit.io/).
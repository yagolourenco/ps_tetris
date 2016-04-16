#TETRIS (versão 1.0)

Primeiro trabalho da matéria de Programação Sistemática. Nele seria necessário construir uma versão simples do famoso jogo Tetris com a utilização de Ncurses, implementar casos testes e usar Makefile.  
Requerimentos:   

+ Sistema operacional baseado em Linux (este programa foi testado no Ubuntu).
+  Biblioteca Ncurses (use o comando ```sudo apt-get install libncurses5-dev``` caso ainda não tenha instalado).

## Execução do Programa

Execute o comando ```make``` no terminal para instalar o programa.
Execute o comando ```./tetris``` para iniciar o programa.

## Comandos do Jogo

```
 [<][v][>]------> move a peça para a direita
  |  '----------> move a peça para baixo
  '-------------> move a peça para a esquerda
```

## Testes

Requerimentos CUnit 2.1.2 (Siga as instrições nesse [site](https://netbeans.org/kb/docs/cnd/c-unit-test.html?print=yes#linux) caso não tenha instalado).  

### Execução dos Testes

Execute o comando ```gcc bloco_teste.c -lncurses -lcunit -o teste``` no terminal para compilar o módulo de testes.  
Execute o comando ```./teste``` para iniciar os testes.  

## Membros

+ André Luiz de Moura Ramos Bittencourt
+ Anne Caroline de Assis Pereira
+ Claudio Segala Rodrigues Silva Filho
+ Hector Rocha Margittay

> Written with [StackEdit](https://stackedit.io/).
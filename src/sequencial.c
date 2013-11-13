/* Disciplina: Sistemas Operacionais I */
/* Prof.: Antonio Thomé */
/* Trabalho: Nr 2 */
/* Autores: João Paulo Ramirez, Jonas Tomaz e Mateus Gregório */

/* Descrição: Programa responsável por gerar uma matriz quadrada conforme o tamanho informado durante a execução */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
  int dim, i, j;

  scanf("%d", &dim);      //le da entrada o numero de quadrantes da matriz
  printf("%d\n", dim);    //imprime no arquivo de saida a dimensao da matriz, considerando o quadrante de tamanho 8x8

  //inicia o gerador de numeros aleatorios
  srand(time(NULL));



  return 0;
}

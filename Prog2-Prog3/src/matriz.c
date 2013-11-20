/* Disciplina: Sistemas Operacionais I */
/* Prof.: Antonio Thomé */
/* Trabalho: Nr 2 */
/* Autores: João Paulo Ramirez, Jonas Tomaz e Mateus Gregório */

/* Descrição: Programa responsável por gerar uma matriz quadrada conforme o parâmetro informado em tempo de execução. */


#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0


int** alocaMatriz(int dimensao) {
   int **mat;
   int i;

   mat = (int**) calloc(dimensao, sizeof(int *));
   if (mat == NULL) {
       printf ("Erro de alocacao de memoria.");
       return NULL;
   }

   for (i=0; i<dimensao; i++) {
      mat[i] = (int*) calloc(dimensao, sizeof(int));
      if (mat[i] == NULL) {
         printf ("Erro de alocacao de memoria.");
         return NULL;
      }
   }

   return mat;
}

void printMatriz(int **matriz, int dimensao) {
  int i, j;

	for (i=0; i<dimensao; i++) {
	    for (j=0; j<dimensao; j++) {
	    	printf("%d ", matriz[i][j]);
	    }
	    printf("\n");
	}
}

int** geraMatriz(int dimensao) {

  int **matriz = alocaMatriz(dimensao);
  int i, j;

  srand(time(NULL));  //inicia o gerador de numeros aleatorios

  for (i=0; i<dimensao; i++) {
    for (j=0; j<dimensao; j++) {
      matriz[i][j] = ((rand()%1000));  //gera numero inteiro entre 0 e 1000
    }
  }

  if (DEBUG) printMatriz(matriz, dimensao);

  return matriz;
}

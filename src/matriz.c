/* Disciplina: Sistemas Operacionais I */
/* Prof.: Antonio Thomé */
/* Trabalho: Nr 2 */
/* Autores: João Paulo Ramirez, Jonas Tomaz e Mateus Gregório */

/* Descrição: Programa responsável por gerar uma matriz quadrada conforme o parâmetro informado em tempo de execução */


#include <stdio.h>
#include <stdlib.h>


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
  int i;

	for (i=0; i<dimensao; i++) {
	    for (int j=0; j<dimensao; j++) {
	    	cout << matriz[i][j] << " ";
	    }
	    cout << endl;
	}
}

int** geraMatriz(int dimensao) {

  int **matriz = alocaMatriz(dimensao);
  srand(time(NULL));  //inicia o gerador de numeros aleatorios

  for (int i=0; i<dimensao; i++) {
    for (int j=0; j<dimensao; j++) {
      matriz[i][j] = ((rand()%100)-50);  //gera numero inteiro entre -50 e 50
    }
  }

  //DEGUG:
  printMatriz(matriz, dimensao);

  return matriz;
}

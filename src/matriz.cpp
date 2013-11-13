/* Disciplina: Sistemas Operacionais I */
/* Prof.: Antonio Thomé */
/* Trabalho: Nr 2 */
/* Autores: João Paulo Ramirez, Jonas Tomaz e Mateus Gregório */

/* Descrição: Programa responsável por gerar uma matriz quadrada conforme o parâmetro informado em tempo de execução */


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int **alocaMatriz(int d) {
   int **mat;  //matriz que sera retornada
   int i;      //variavel auxiliar

   //aloca espaco em memoria para a matriz de inteiros de dimensao dxd
   mat = (int**) calloc(d, sizeof(int *));
   if (mat == NULL) {
       printf ("Erro de alocacao de memoria");
       return NULL;
   }

   for (i=0; i<d; i++) {
      mat[i] = (int*) calloc(d, sizeof(int));
      if (mat[i] == NULL) {
         printf ("Erro de alocacao de memoria");
         return NULL;
      }
   }

   return mat;  //retorna o ponteiro para a matriz
}

void printMatriz(int **matriz, int k) {
	for (int i=0; i<k; i++) {
	    for (int j=0; j<k; j++) {
	    	cout << matriz[i][j] << " ";
	    }
	    cout << endl;
	}
}

int** geraMatriz(int k) {

  int **matriz = alocaMatriz(k);
  srand(time(NULL));  //inicia o gerador de numeros aleatorios

  for (int i=0; i<k; i++) {
    for (int j=0; j<k; j++) {
      matriz[i][j] = ((rand()%100)-50);  //gera numero inteiro entre -50 e 50
    }
  }

  printMatriz(matriz, k);

  return matriz;
}

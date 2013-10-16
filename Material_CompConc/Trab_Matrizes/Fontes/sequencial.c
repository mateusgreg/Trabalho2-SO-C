/* Disciplina: Computação Concorrente */
/* Prof.: Silvana Rossetto */
/* Trabalho: 1 */
/* Autores: Juan Baptista e Mateus Gregório */

/* Descrição: Módulo do programa responsável pela resolução do problema proposto de forma sequencial */

#include <stdio.h>
#include <stdlib.h>
#include "sequencial.h"


//aloca espaco em memoria para um vetore de n inteiros
int *alocaVetorInteirosSeq(int n){
  int *vet;

  vet = calloc(n, sizeof(int));
  if (vet == NULL) {
       printf ("Erro de alocacao de memoria do vetor de inteiros.");
       return NULL;
  }

  return vet;  //retorna o ponteiro para o vetor
}


//Executa o processamento da matriz de entrada: soma todos os elementos, verifica quem eh o maior e o menor deles
int *processaMatrizSeq(int **mat, int dim){
  int i,j;
  int *res;

  //aloca memoria para o vetor que ira retornar o resultado final
  res = alocaVetorInteirosSeq(3);

  for(i=0;i<dim;i++){
    for(j=0;j<dim;j++){
      //calcula a soma dos elementos da matriz
      if(res[0]==NULL) res[0] = mat[i][j];
      else res[0] += mat[i][j];

      //verifica quem eh o maior e o menor elemento da matriz
      if(res[1]==NULL || mat[i][j]>res[1])res[1]=mat[i][j];
      else if(res[2]==NULL || mat[i][j]<res[2])res[2]=mat[i][j];
    }
  }

  return res;  //retorna o resultado final: soma, maior e menor
}

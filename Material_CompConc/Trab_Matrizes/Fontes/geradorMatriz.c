#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main(){
  int dim, i, j;

  scanf("%d", &dim);      //le da entrada o numero de quadrantes da matriz
  printf("%d\n", dim*8);  //imprime no arquivo de saida a dimensao da matriz, considerando o quadrante de tamanho 8x8

  //inicia o gerador de numeros aleatorios
  srand(time(NULL));

  //imprime a matriz de numeros aleatorios
  for(i=0; i<8*dim; i++){
    for(j=0; j<8*dim; j++){
      printf("%d ", (rand()%100)-50);  //gera numero entre -50 e 50
    }
    printf("\n");
  }
}

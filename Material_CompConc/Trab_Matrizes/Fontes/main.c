/* Disciplina: Computação Concorrente */
/* Prof.: Silvana Rossetto */
/* Trabalho: 1 */
/* Autores: Juan Baptista e Mateus Gregório */

/* Descrição: Módulo principal do programa, responsável pela escolha da solução a ser executada e apresentação dos resultados ao usuário */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//variáveis globais
int **matriz;  //matriz de entrada
int dim;  //dimensao da matriz de entrada


//aloca espaco em memoria para uma matriz quadrada
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


//libera espaco em memoria da matriz
void liberaMatriz(int **mat, int d) {
   int i;
   for (i=0; i<d; i++) free(mat[i]);
   free(mat);
}


//le do arquivo de entrada os elementos da matriz de dimensao d
int **carregaMatriz(int d) {
   int **mat;  //matriz que sera retornada
   int i, j;   //variaveis auxiliares

   //aloca espaco em memoria para a matriz de entrada
   mat = alocaMatriz(d);

   //le a matriz de inteiros do arquivo de entrada padrao
   for (i=0; i<d; i++) {
      for (j=0; j<d; j++) {
         scanf("%d", &mat[i][j]);
      }
   }

   return mat;  //retorna o ponteiro para a matriz
}


void main(int argc, char *argv[]){

  int *resultado;

  //variaveis utilizadas na contagem de tempo
  struct timeval startTime, endTime;
  unsigned int totalUsecs;

  //faz a leitura da dimensao da matriz e de seus elementos do arquivo de entrada
  scanf("%d", &dim);
  matriz = carregaMatriz(dim);

  //verifica qual versao do programa sera executada de acordo com o parametro de execucao
  if(strcmp(argv[1], "sequencial") == 0){

    gettimeofday(&startTime, NULL);  //inicia o contador de tempo
    resultado = processaMatrizSeq(matriz, dim);
	gettimeofday(&endTime, NULL);    //encerra o contador de tempo

	//calcula a diferenca entre o tempo final e tempo inicial
    totalUsecs = (unsigned long long) (endTime.tv_sec - startTime.tv_sec) * 1000000 +
                 (unsigned long long) (endTime.tv_usec - startTime.tv_usec);
  }
  else if(strcmp(argv[1],"concorrente") == 0){

    gettimeofday(&startTime, NULL);  //inicia o contador de tempo
    resultado = programaConcorrente(matriz, dim);
	gettimeofday(&endTime, NULL);    //encerra o contador de tempo

	//calcula a diferenca entre o tempo final e tempo inicial
    totalUsecs = (unsigned long long) (endTime.tv_sec - startTime.tv_sec) * 1000000 +
                 (unsigned long long) (endTime.tv_usec - startTime.tv_usec);
  }
  else{
    printf("\nERRO: Argumento inválido! O programa será encerrado...\n");
    exit(-1);
  }

  //impressao dos resultados
  printf("Soma: %d\n", resultado[0]);
  printf("Maior: %d\n", resultado[1]);
  printf("Menor: %d\n", resultado[2]);
  printf("%s%g ms\n\n", "Tempo de processamento: ", (double) totalUsecs);

  //libera espaco em memoria
  free(resultado);
  liberaMatriz(matriz, dim);
}

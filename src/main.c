
#include "tarefa.h"
#include "subprocessos.h"
#include "stdlib.h"
#include "stdio.h"

int k = 16;
int **matrizGerada;
int *PI;

int main (){
	//globais variaveis
	//int* indices = (int*)calloc(sizeof(int), k);

	//subprocessos variaveis
	int nsubprocessos = 4;
	Resultado* resultado;

	//loop variaveis
	int l;
	int j;


	matrizGerada = (int**)calloc(sizeof(int*), k);
	PI = (int*)calloc(sizeof(int), k);

	for(l = 0; l < k; l++){
		//indices[l] = l;
		matrizGerada[l] = (int *)calloc(sizeof(int), k);
	}

	for(l = 0; l < k; l++){
		for(j = 0; j < k; j++){
			matrizGerada[l][j] = 1;
			printf("%d ", matrizGerada[l][j]);
		}
		printf("\n");
	}

	//executaTarefa(indices, k, &mediaPI, &mediaQuadradoPI, &maiorElem, &menorElem, &maiorPI, &menorPI);

	resultado = executaSubprocessos(nsubprocessos);

	printf("mediaPI = %.4f\n",resultado-> mediaPI);
	printf("mediaQuadradoPI = %.4f\n", resultado->mediaQuadradoPI);
	printf("menorPI = %d\n", resultado->menorPI);
	printf("maiorPI = %d\n", resultado->maiorPI);
	printf("menorElem = %d\n", resultado->menorElem);
	printf("maiorElem = %d\n", resultado->maiorElem);
	printf("desvio padrao = %.4f\n", (resultado->mediaQuadradoPI - resultado->mediaPI * resultado->mediaPI));

	printf("PI\n");
	for(l = 0; l < k; l++){
		printf("%d ", PI[l]);
	}
	printf("\n");

	free(resultado);
}

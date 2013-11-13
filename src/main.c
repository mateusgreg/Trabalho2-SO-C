
#include "tarefa.h"
#include "stdlib.h"
#include "stdio.h"

int k = 4;
int **matrizGerada;
int *PI;

int main (){
	int* indices = (int*)calloc(sizeof(int), k);
	float mediaPI;
	float mediaQuadradoPI;
	int maiorElem;
	int menorElem;
	int maiorPI;
	int menorPI;
	int l;
	int j;
	matrizGerada = (int**)calloc(sizeof(int*), k);
	PI = (int*)calloc(sizeof(int), k);

	for(l = 0; l < k; l++){
		indices[l] = l;
		matrizGerada[l] = (int *)calloc(sizeof(int), k);
	}

	for(l = 0; l < k; l++){
		for(j = 0; j < k; j++){
			matrizGerada[l][j] = 1;
			printf("%d ", matrizGerada[l][j]);
		}
		printf("\n");
	}

	executaTarefa(indices, k, &mediaPI, &mediaQuadradoPI, &maiorElem, &menorElem, &maiorPI, &menorPI);

	printf("mediaPI = %.4f\n", mediaPI);
	printf("mediaQuadradoPI = %.4f\n", mediaQuadradoPI);
	printf("menorPI = %d\n", menorPI);
	printf("maiorPI = %d\n", maiorPI);
	printf("menorElem = %d\n", menorElem);
	printf("maiorElem = %d\n", maiorElem);
	printf("desvio padrao = %.4f\n", (mediaQuadradoPI - mediaPI * mediaPI));

	printf("PI\n");
	for(l = 0; l < k; l++){
		printf("%d ", PI[l]);
	}
	printf("\n");
}

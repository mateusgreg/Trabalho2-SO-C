
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
	float mediaPI;
	float mediaQuadradoPI;
	int maiorElem;
	int menorElem;
	int maiorPI;
	int menorPI;

	//subprocessos variaveis
	int nsubprocessos = 4;
	float* mediasPI;
	float* mediasQuadradoPI;
	int* maioresPI;
	int* menoresPI;
	int* maioresElem;
	int* menoresElem;

	//loop variaveis
	int l;
	int j;

	mediasPI = (float*) calloc(sizeof(float), nsubprocessos);
	mediasQuadradoPI = (float*) calloc(sizeof(float), nsubprocessos);;
	maioresPI = (int*) calloc(sizeof(int), nsubprocessos);
	menoresPI = (int*) calloc(sizeof(int), nsubprocessos);
	maioresElem = (int*) calloc(sizeof(int), nsubprocessos);
	menoresElem = (int*) calloc(sizeof(int), nsubprocessos);


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

	executaSubprocessos(nsubprocessos, mediasPI, mediasQuadradoPI, maioresPI, menoresPI, maioresElem, menoresElem);

	mediaPI = 0;
	mediaQuadradoPI = 0;
	maiorElem = matrizGerada[0][0];
	menorElem = matrizGerada[0][0];
	maiorPI = maioresPI[0];
	menorPI = maioresPI[0];

	for(l = 0; l < nsubprocessos; l++){
		mediaPI += mediasPI[l];
		mediaQuadradoPI += mediasQuadradoPI[l];
		maiorPI = (maiorPI > maioresPI[l]) ? maiorPI : maioresPI[l];
		menorPI = (menorPI < menoresPI[l]) ? menorPI : menoresPI[l];
		maiorElem = (maiorElem > maioresElem[l]) ? maiorElem : maioresElem[l];
		menorElem = (menorElem < menoresElem[l]) ? menorElem : menoresElem[l];
	}

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

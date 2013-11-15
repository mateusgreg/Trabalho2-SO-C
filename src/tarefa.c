
#include "tarefa.h"
#include "stdlib.h"

extern int k;
extern int* PI;
extern int** matrizGerada;


tarefas* divideTarefas(int k, int undExecucao){
	tarefas* t = (tarefa*)calloc(sizeof(tarefa), undExecucao);
	
	return t;
}

/*
lembrando que k, PI e matrizGerada sao globais
*/
void executaTarefa(int* indices, int tamVetorIndices, float* mediaPI, float* mediaQuadradoPI, int* maiorElem, int* menorElem, int* maiorPI, int* menorPI ){
	int j;
	*mediaPI = 0;
	*mediaQuadradoPI = 0;
	*maiorElem = matrizGerada[indices[0]][0];
	*menorElem = matrizGerada[indices[0]][0];

	for (j = 0; j < tamVetorIndices; j++){
		PI[indices[j]] = produtoInternoEMaiorMenorElementoParcial(indices[j], maiorElem, menorElem);
		*mediaPI += (PI[indices[j]] / k);
		*mediaQuadradoPI += (PI[indices[j]] * PI[indices[j]]) / k;
		*maiorPI = (PI[indices[j]] > *maiorPI || j == 0) ? PI[indices[j]] : *maiorPI; //como nao foi inicializado, inicializo com o primeiro PI calculado
		*menorPI = (PI[indices[j]] < *menorPI || j == 0) ? PI[indices[j]] : *menorPI; //como nao foi inicializado, inicializo com o primeiro PI calculado
	}
}

int produtoInternoEMaiorMenorElementoParcial(int i, int* maiorElem, int* menorElem){
	int j;
	int PI = 0;
	int auxMaiorMenor;

	for(j = 0; j < k; j++){
		PI += matrizGerada[i][j] * matrizGerada[j][i];
		auxMaiorMenor = (matrizGerada[i][j] > matrizGerada[j][i]) ? matrizGerada[i][j] : matrizGerada[j][i];
		*maiorElem = (*maiorElem > auxMaiorMenor) ? *maiorElem : auxMaiorMenor;
		auxMaiorMenor = (matrizGerada[i][j] < matrizGerada[j][i]) ? matrizGerada[i][j] : matrizGerada[j][i];
		*menorElem = (*menorElem < auxMaiorMenor) ? *menorElem : auxMaiorMenor;
	}

	return PI;
}

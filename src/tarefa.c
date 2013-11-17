
#include "tarefa.h"
#include "stdlib.h"
#include "utilidades.h"

extern int k;
extern int* PI;
extern int** matrizGerada;


tarefas* divideTarefas(int k, int undExecucao){
	tarefas* t = (tarefas*)calloc(sizeof(tarefas), undExecucao);
	
	return t;
}

/*
lembrando que k, PI e matrizGerada sao globais
*/
Resultado* executaTarefa(int* indices, int tamVetorIndices){
	int j;
	Resultado* resultado = (Resultado*)malloc(sizeof(Resultado));
	resultado->mediaPI = 0.0;
	resultado->mediaQuadradoPI = 0.0;
	resultado->maiorElem = getMinimumInt();
	resultado->menorElem = getMaximumInt();
	resultado->maiorPI = getMinimumInt();
	resultado->menorPI = getMaximumInt();

	for (j = 0; j < tamVetorIndices; j++){
		PI[indices[j]] = produtoInternoEMaiorMenorElementoParcial(indices[j], &(resultado->maiorElem), &(resultado->menorElem));
		resultado->mediaPI += (PI[indices[j]] / k);
		resultado->mediaQuadradoPI += (PI[indices[j]] * PI[indices[j]]) / k;
		resultado->maiorPI = (PI[indices[j]] > resultado->maiorPI) ? PI[indices[j]] : resultado->maiorPI;
		resultado->menorPI = (PI[indices[j]] < resultado->menorPI) ? PI[indices[j]] : resultado->menorPI;
	}

	return resultado;
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

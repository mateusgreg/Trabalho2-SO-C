/* Disciplina: Sistemas Operacionais I */
/* Prof.: Antonio Thomé */
/* Trabalho: Nr 2 */
/* Autores: João Paulo Ramirez, Jonas Tomaz e Mateus Gregório */

/* Descrição: Código-fonte genérico, utilizado pelos 3 módulos do programa. Auxilia na divisão e execução das tarefas entre as unidades de execução. */


#include "tarefa.h"
#include "stdlib.h"
#include "utilidades.h"

extern int k;
extern Resultado* resultadoFinal;
extern int** matrizGerada;


Tarefas* divideTarefas(int k, int undExecucao){
	Tarefas* tarefas = (Tarefas*)malloc(undExecucao * sizeof(Tarefas));
	int i, indice = 0, resto = k % undExecucao, quociente = k/undExecucao;

	for (i=0; i<undExecucao; i++) {
		if (resto) {
			tarefas[i].inicio = indice;
			tarefas[i].fim = indice + quociente;
			indice += quociente + 1;
			resto--;
		} else{
			tarefas[i].inicio = indice;
			tarefas[i].fim = indice + quociente - 1;
			indice += quociente;						
		}
	}

	return tarefas;
}

/*
lembrando que k e matrizGerada sao globais
*/
Resultado* executaTarefa(int* indices, int tamVetorIndices){
	int j;
	Resultado* resultado = (Resultado*)malloc(sizeof(Resultado));
	resultado->PI = NULL;
	resultado->mediaPI = 0.0;
	resultado->mediaQuadradoPI = 0.0;
	resultado->maiorElem = getMinimumInt();
	resultado->menorElem = getMaximumInt();
	resultado->maiorPI = getMinimumInt();
	resultado->menorPI = getMaximumInt();

	for (j = 0; j < tamVetorIndices; j++){
		resultadoFinal->PI[indices[j]] = produtoInternoEMaiorMenorElementoParcial(indices[j], &(resultado->maiorElem), &(resultado->menorElem));
		resultado->mediaPI += (resultadoFinal->PI[indices[j]] / k);
		resultado->mediaQuadradoPI += (resultadoFinal->PI[indices[j]] * resultadoFinal->PI[indices[j]]) / k;
		resultado->maiorPI = (resultadoFinal->PI[indices[j]] > resultado->maiorPI) ? resultadoFinal->PI[indices[j]] : resultado->maiorPI;
		resultado->menorPI = (resultadoFinal->PI[indices[j]] < resultado->menorPI) ? resultadoFinal->PI[indices[j]] : resultado->menorPI;
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

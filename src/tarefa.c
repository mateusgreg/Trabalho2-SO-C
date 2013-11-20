/* Disciplina: Sistemas Operacionais I */
/* Prof.: Antonio Thomé */
/* Trabalho: Nr 2 */
/* Autores: João Paulo Ramirez, Jonas Tomaz e Mateus Gregório */

/* Descrição: Código-fonte genérico, utilizado pelos 3 módulos do programa. Auxilia na divisão e execução das tarefas entre as unidades de execução. */


#include <stdio.h>
#include "tarefa.h"
#include "stdlib.h"
#include "utilidades.h"

#define DEBUG 0


extern int k;
extern int** matrizGerada;
extern Resultado* resultadoFinal;


Tarefas* divideTarefas(int undExecucao){
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

	if (DEBUG) printf("\nAloquei Vetor de Tarefas...\n");

	return tarefas;
}

Resultado* executaTarefa(Tarefas* tarefas) {
	int i;
	Resultado* resultado = (Resultado*)malloc(sizeof(Resultado));
	resultado->PI = NULL;
	resultado->mediaPI = 0.0;
	resultado->mediaQuadradoPI = 0.0;
	resultado->maiorElem = getMinimumInt();
	resultado->menorElem = getMaximumInt();
	resultado->maiorPI = getMinimumInt();
	resultado->menorPI = getMaximumInt();

	for (i = tarefas->inicio; i <= tarefas->fim; i++){
		resultadoFinal->PI[i] = produtoInternoEMaiorMenorElementoParcial(i, &(resultado->maiorElem), &(resultado->menorElem));
		resultado->mediaPI += (resultadoFinal->PI[i] / k);
		resultado->mediaQuadradoPI += (resultadoFinal->PI[i] * resultadoFinal->PI[i]) / k;
		resultado->maiorPI = (resultadoFinal->PI[i] > resultado->maiorPI) ? resultadoFinal->PI[i] : resultado->maiorPI;
		resultado->menorPI = (resultadoFinal->PI[i] < resultado->menorPI) ? resultadoFinal->PI[i] : resultado->menorPI;
	}

	return resultado;
}

unsigned long long int produtoInternoEMaiorMenorElementoParcial(int i, int* maiorElem, int* menorElem){
	int j, auxMaiorMenorElem;
	unsigned long long int PI = 0;

	for(j = 0; j < k; j++){
		PI += matrizGerada[i][j] * matrizGerada[j][i];
		auxMaiorMenorElem = (matrizGerada[i][j] > matrizGerada[j][i]) ? matrizGerada[i][j] : matrizGerada[j][i];
		*maiorElem = (*maiorElem > auxMaiorMenorElem) ? *maiorElem : auxMaiorMenorElem;
		auxMaiorMenorElem = (matrizGerada[i][j] < matrizGerada[j][i]) ? matrizGerada[i][j] : matrizGerada[j][i];
		*menorElem = (*menorElem < auxMaiorMenorElem) ? *menorElem : auxMaiorMenorElem;
	}

	return PI;
}
